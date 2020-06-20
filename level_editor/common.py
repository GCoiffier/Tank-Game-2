import random
from matplotlib.pyplot import cm

def get_color(i, cm, n=10):
    r,g,b,a = cm( (i%n) / n)
    rgb = (int(255*r), int(255*g), int(255*b))
    return '#%02x%02x%02x' % rgb

TEMPLATE_DIRS = ["", "tanks", "obstacles"]
COLOR_PALETTES = [cm.prism, cm.tab20, cm.twilight_shifted]

CELL_SIZE = 20