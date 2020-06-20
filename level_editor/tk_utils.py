import tkinter as tk
from matplotlib.pyplot import cm
from common import *

class Rectangle:
    """
    A rectangle to be drawn on a canvas
    """
    def __init__(self, can, i, j, color):
        self.rect = can.create_rectangle(CELL_SIZE*i , CELL_SIZE*j , CELL_SIZE*(i+1) , CELL_SIZE*(j+1) ,
                            width=1, fill = color, outline="black")
        self.color = color
        self.pos = (i,j)
        self.master = can
        self.selected = False


class ColorButton:

    def __init__(self, can, txt, i, color):
        x1, y1, x2, y2 = 4, 16*(i+1), 20, 16*(i+2)
        self.coords= (x1,y1,x2,y2)
        self.color = color
        self.rectangle = can.create_rectangle(x1,y1,x2,y2, width=1, fill = self.color, outline='black')
        self.text = txt
        self.textRender = can.create_text(x2+4,(y1+y2)/2, text=txt, anchor=tk.W)
        self.pos = (x1//CELL_SIZE,y1//CELL_SIZE)
        self.master= can
        self.selected = False

    def highlight(self) :
        can = self.master
        x1,y1,x2,y2 = self.coords
        if not self.selected :
            self.rectangle = can.create_rectangle(x1,y1,x2,y2, width=1, fill = self.color, outline='#ee2')
        else :
            self.rectangle = can.create_rectangle(x1,y1,x2,y2, width=1, fill = self.color, outline='black')
        self.selected = not self.selected