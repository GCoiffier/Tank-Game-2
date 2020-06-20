import tkinter as tk
from tkinter import messagebox
import math
import sys
import os

from level import Level
from tk_utils import *
from common import *

class Editor:

    def __init__(self):

        self.level = Level()
        self.repr_level = [[None for _ in range(Level.HEIGHT)] for _ in range(Level.WIDTH)]

        self.window = tk.Tk()
        self.window.title("Tank Game Level Editor")

        self.load_templates()

        # ACtion buttons initialization
        self.act_window = tk.LabelFrame(self.window ,text="Options")
        self.act_window.pack(side=tk.RIGHT)
        tk.Button(self.act_window, text = "Export", command=self.export).pack()
        tk.Button(self.act_window, text = "Clear" , command = self.clear).pack()
        tk.Button(self.act_window, text = "Exit", command=self.window.destroy).pack()

        # Painting Button selection / Template selection
        self.selected = None

        self.tool_window = tk.Frame(self.window)
        self.tool_window.pack(side=tk.LEFT)
        
        self.template_buttons = dict()
        for ic, category in enumerate(self.templates.keys()):
            self.template_buttons[category] = []
            tool_zone = tk.LabelFrame(self.tool_window, text=category)
            tool_cv = tk.Canvas(tool_zone, width=200, height=CELL_SIZE*(len(self.templates[category])+1.5))
            tool_cv.bind("<Button-1>", lambda x, zone=category : self.select_template(zone, x))
            for ib, but in enumerate(self.templates[category]):
                color = get_color(ib, COLOR_PALETTES[ic])
                button = ColorButton(tool_cv, but, ib, color)
                self.template_buttons[category].append(button)
            tool_zone.pack()
            tool_cv.pack()

        # Drawing Window initialization
        self.draw_window = tk.LabelFrame(self.window, text="Map")
        self.draw_window.pack(side=tk.RIGHT)
        self.draw_zone = tk.Canvas(self.draw_window, width = CELL_SIZE*Level.WIDTH, height = CELL_SIZE*Level.HEIGHT)
        self.draw_zone.bind("<Button-1>", self.plop_on_map)
        self.draw_zone.bind("<Button-3>", self.remove_on_map)
        self.draw_zone.pack()
        self._clear_repr_level()

    
    
    def load_templates(self):
        self.templates = dict()
        for folder in TEMPLATE_DIRS:
            folder_templates = []
            for template in os.listdir(os.path.join("../static/templates/", folder)):
                if ".json" in template:
                    folder_templates.append(template)
            folder_templates.sort()
            self.templates[folder] = folder_templates

    def mainloop(self):
        self.window.mainloop()

    def select_template(self, zone, event):
        button = (event.y + 4)//CELL_SIZE
        if button>0:
            if self.selected is not None:
                self.selected[1].highlight() # toggle highlight of previous selected
            self.selected = (zone, self.template_buttons[zone][button-1])
            self.selected[1].highlight() # toggle highlight of current selected

    def plop_on_map(self, event):
        if self.selected is not None:
            i, j = event.x//CELL_SIZE, event.y//CELL_SIZE
            cat, but = self.selected
            self.repr_level[i][j] = Rectangle(self.draw_zone, i, j, but.color)
            self.level[i,j] = os.path.join(cat, but.text)
            print(self.level[i,j])

    def remove_on_map(self, event):
        i, j = event.x//CELL_SIZE, event.y//CELL_SIZE
        self.repr_level[i][j] = Rectangle(self.draw_zone, i, j, 'white')
        self.level[i,j] = None

    def export(self):
        popup = tk.Tk()
        popup.title("Export")
        txt = tk.Label(popup, text="Export as :")
        txt.pack()

        e = tk.Entry(popup)
        e.pack()

        e.delete(0, tk.END)
        e.insert(0, "my_level")

        back = tk.Button(popup,text='Back',command=popup.destroy)
        back.pack(side = tk.LEFT)

        def fct() :
            file_name = e.get()
            if False: # check if file_name exists
                messagebox.showerror("Error", "Level file '{}' already exists\nPlease select another name".format(file_name))
            else:
                self.level.to_file(file_name)
                popup.destroy()

        exp = tk.Button(popup, text = 'Export', command = fct)
        exp.pack(side = tk.RIGHT)
        popup.mainloop()

    def clear(self):
        self.level.clear()
        self._clear_repr_level()

    def _clear_repr_level(self):
        self.repr_level = [[None for _ in range(Level.HEIGHT)] for _ in range(Level.WIDTH)]
        for i in range(Level.WIDTH):
            for j in range(Level.HEIGHT):
                self.repr_level[i][j] = Rectangle(self.draw_zone, i, j, 'white')

if __name__ == "__main__" :
    editor = Editor()
    editor.mainloop()