from matplotlib.pyplot import cm
import random

def get_color(i=0):
    n = 20
    r,g,b,a = cm.hsv((i%n)/n)
    return (r/(i//n), g/(i//n), b/(i//n), a)
    

TEMPLATE_DIRS = ["", "obstacles", "tanks"]

CELL_SIZE = 16