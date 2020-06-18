import tkinter as tk
from common import *

class Mouse:
    ''' la classe qui gere toutes les actions du curseur dans l'interface Tkinter'''
    def __init__(self, window, color='white'):
        self.color = color
        self.master = window
        self._where = "main"
        self.selected = None # le rectangle de l'IA bleue selectionnee

    def where(self, x):
        self._where = x

    def onLeftClick(self, event):
        if self._where == "tool":
            self._leftClickTool()
        elif self._where == "draw":
            self._leftClickDraw()
    
    def onRightClick(self, event):
        if self._where == "tool":
            self._rightClickTool()
        elif self._where == "draw":
            self._rightClickDraw()

    def _leftClickDraw(self):
        return
    
    def _rightClickDraw(self):
        return

    def _leftClickTool(self):
        return
    
    def _rightClickTool(self):
        return


class Rectangle:
    """
    A rectangle to be drawn on a canvas
    """
    def __init__(self, wind, i, j, color):
        global color_dict
        rect = wind.create_rectangle(CELL_SIZE*i , CELL_SIZE*j , CELL_SIZE*(i+1) , CELL_SIZE*(j+1) ,
                            width=1, fill= color_dict[color][0], outline= "black")
        self.rect = rect
        self.color = color
        self.pos = (i,j)
        self.master = wind
        self.selected = False


class ColorButton:

    def __init__(self, can, but, i):
        x1, y1, x2, y2 = 4, 16*(i+1), 20, 16*(i+2)
        rect, text = self.create_button(can, x1, y1, x2, y2, color)
        self.rectangle = rect
        self.pos = (x1//CELL_SIZE,y1//CELL_SIZE)
        self.master= can
        self.coords= (x1,y1,x2,y2)
        self.text = text
        self.color = color
        self.selected = False

    def create_button(self,can,x1,y1,x2,y2,color):
        global color_dict, type_dict
        rect = can.create_rectangle(x1,y1,x2,y2, width=1, fill = color_dict[color][0], outline='black')
        text = can.create_text(x2+4,(y1+y2)/2, text=type_dict[color], anchor=tk.W)
        return rect, text

    def highlight_button(self) :
        can = self.master
        x1,y1,x2,y2 = self.coords
        color=self.color
        if not self.selected :
            self.rectangle = can.create_rectangle(x1,y1,x2,y2, width=1, fill = color_dict[color][0], outline='#ee2')
        else :
            self.rectangle = can.create_rectangle(x1,y1,x2,y2, width=1, fill = color_dict[color][0], outline='black')
        self.selected = not self.selected