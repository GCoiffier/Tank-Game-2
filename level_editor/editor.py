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

        self.window = tk.Tk()
        self.window.title("Tank Game Level Editor")

        self.load_templates()

        # mouse init
        self.mouse = Mouse(self.window)
        self.window.bind("<Button-1>", self.mouse.onLeftClick)
        self.window.bind("<Button-3>", self.mouse.onRightClick)

        # action button init
        self.act_window = tk.LabelFrame(self.window ,text="Options")
        self.act_window.pack(side=tk.RIGHT)
        tk.Button(self.act_window, text = "Export", command=self.export).pack()
        tk.Button(self.act_window, text = "Clear" , command = self.clear).pack()
        tk.Button(self.act_window, text = "Exit", command=self.window.destroy).pack()

        # tool buttons
        self.tool_window = tk.LabelFrame(self.window , text="Templates")
        self.tool_window.bind("<Enter>", lambda _: self.mouse.where("tool"))
        self.tool_window.bind("<Leave>", lambda _: self.mouse.where("main"))
        self.tool_window.pack(side=tk.LEFT)
        
        self.tool_zone = Canvas(self.tool_window, width=120, height=CELL_SIZE*Level.HEIGHT)
        for i,but in enumerate(self.templates):
            button = ColorButton(tool_zone, but, i)
            buttons.append(button)

        yDefil = tk.Scrollbar(self.tool_window, orient='vertical')
        lbox = tk.Listbox(self.tool_window, height=22, yscrollcommand=yDefil.set, listvariable=self.templatesVar, selectmode=tk.SINGLE)
        yDefil['command'] = lbox.yview
        yDefil.pack(side=tk.RIGHT)
        lbox.pack()

        # la fenetre de dessin
        self.draw_window = tk.LabelFrame(self.window, text="Map")
        self.draw_window.bind("<Enter>", lambda _: self.mouse.where("draw"))
        self.draw_window.bind("<Leave>", lambda _: self.mouse.where("main"))
        self.draw_window.pack(side=tk.RIGHT)
        draw_zone = tk.Canvas(self.draw_window, width = CELL_SIZE*Level.WIDTH, height = CELL_SIZE*Level.HEIGHT)
        draw_zone.pack()
        for i in range(Level.WIDTH):
            for j in range(Level.HEIGHT):
                rect = Rectangle(draw_zone, i, j, 'white')
    
    def load_templates(self):
        self.templatesVar = tk.StringVar()
        self.templates = []
        for folder in TEMPLATE_DIRS:
            for template in os.listdir(os.path.join("../static/templates/", folder)):
                if ".json" in template:
                    self.templates.append(os.path.join(folder,template))
        self.templatesVar.set(" ".join(self.templates))


    def mainloop(self):
        self.window.mainloop()

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
        self.level = Level()


if __name__ == "__main__" :
    editor = Editor()
    editor.mainloop()