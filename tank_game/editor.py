# Tank Game:
# A game with tanks and stuff.
#
# by Erkalys & Florimond Manca
#
# Level editor

## Imports

from Tkinter import *
import math
import sys
import os
join = os.path.join
path = os.getcwd()


## Variables globales
X_LEVEL = 1280//32
Y_LEVEL = 800//32
CELL_SIZE = 16

edit_path = join(join(path,"static"), "custom_levels")

int_matrix = [[0 for j in range(X_LEVEL)] for i in range(Y_LEVEL)]

IA = [] #liste correspondant aux IA blue, bluePlus, purple et purplePlus

paths_matrix= []

rect_matrix= [[None for j in range(X_LEVEL)] for i in range(Y_LEVEL)]

color_dict = { 'white': ('#fff',0) , 'black': ('#000',1), 'brown': ('#a60',2),
           'green': ('#0f0',3) , 'yellow' : ('#ff0',4) , 'orange': ('#fc0',5),
           'blue': ('#00f',6), 'darkblue' : ('#00a',7) , 'red': ('#f00',8), 'darkred' : ('#c00', 9) ,
           'purple':('#f0f',10) , 'darkpurple' : ('#a0a' , 11) , 'grey' : ('#aaa' , 12), 'darkgrey' : ('#777', 13) }

type_dict = { 'white': 'None', 'black': 'Wall', 'brown': 'Pit',
          'green': 'Player', 'yellow': 'IA Yellow', 'orange': 'IA YellowPlus',
          'blue': 'IA Blue', 'darkblue' : 'IA BluePlus', 'red': 'IA Red', 'darkred' : 'IA redPlus',
        'purple': 'IA purple','darkpurple' : 'IA PurplePlus' , 'grey' : "Spawner", 'darkgrey' : "SpawnerPlus"}

## UTILITAIRES
def convert(liste,split=False) :
    """
    Renvoie la chaine de caractere correspondant a la liste avec des espaces
    """
    string = ""
    if not split :
        for i in range(len(liste)) :
            string+= str(liste[i])+" "
    else : #split = True, la liste est une liste de tupple qu'il faut separer
        for i in range((len(liste))) :
            string+= str(liste[i][0])+" "+ str(liste[i][1])+" "
    return string+'\n'

def create_level(matrice, paths) :
    n=1
    while os.path.exists(join(edit_path , "custom_level"+str(n)+".txt")):
        n+=1
    fname = "custom_level"+str(n)+".txt"
    fullname = join(edit_path, fname)
    file = open(fullname, 'w')
    for i in range(len(matrice)) :
          file.write(convert(matrice[i]))
    if paths != [] :
        for i in range(len(paths)) :
            file.write(str(len(paths[i]))+convert(paths[i], split=True))
    file.close()

def convert_and_sort(matrix) : #liste de liste de way_points -> liste de x1 y1 x2 y2 ...
    sortie = []
    for i in range(len(matrix)):
        sortie.append(matrix[i])
        for j in range(len(matrix[i])):
            (a,b) = matrix[i][j].pos
            sortie[i][j] = (b,a)
    sortie.sort() #on trie les listes de la matrice
    for i in range(len(sortie)):
        for j in range(len(sortie[i])):
            (a,b) = sortie[i][j]
            sortie[i][j] = (b,a)
    return sortie

def export() :
    global int_matrix , paths_matrix
    warn = Tk()
    warn.title("Warning")

    texte=Label(warn, text="You won't be able to edit this level after its exportation")
    texte.pack()

    back = Button(warn,text='Get back to work',command=warn.destroy)
    back.pack(side = LEFT)

    def fct() :
        create_level(int_matrix,convert_and_sort(paths_matrix))
        clear()
        warn.destroy()

    exp = Button(warn, text = 'Continue', command = fct)
    exp.pack(side = RIGHT)
    warn.mainloop()

def clear() : #reinitialise l'editeur de niveau
    global int_matrix, paths_matrix, IA
    int_matrix = [[0 for j in range(X_LEVEL)] for i in range(Y_LEVEL)]
    paths_matrix= []
    IA = []
    for i in range(Y_LEVEL) :
        for j in range(X_LEVEL) :
            if i==0 or i==Y_LEVEL-1 or j==0 or j==X_LEVEL-1 : #on est sur les bords
                rect = rectangle(zone_dessin, i, j, 'black')
                rect_matrix[i][j] = rect
                int_matrix[i][j] = color_dict['black'][1]
            else :
                rect = rectangle(zone_dessin, i, j, 'white')
                rect_matrix[i][j] = rect
                int_matrix[i][j] = color_dict['white'][1]

def clear_paths() : #reinitialise uniquement les chemins lies aux IA
    global paths_matrix, zone_dessin, IA
    paths_matrix = []
    for i in range(len(IA)) :
        paths_matrix.append([])
        zone_dessin.delete(("path",str(i)))
    for x in IA :
        x.points_list = [way_point(zone_dessin,x.pos[1],x.pos[0],x.id)]

## GESTION D'EVENEMENTS LIES A LA SOURIS

class mouse():
    ''' la classe qui gere toutes les actions du curseur dans l'interface Tkinter'''
    def __init__(self,fenetre,color='white'):
        self.color = color
        self.mode = 'normal'
        self.where = fenetre
        self.buttons = None
        self.selected = None # le rectangle de l'IA bleue selectionnee

    # les fonctions d'etat

    def mouse_normal(self):
        # passe la souris en mode normal a l'appui sur le bouton 'Normal mode'
        global zone_dessin
        self.mode = 'normal'
        self.selected = None
        zone_dessin.delete("paths")

    def mouse_path_creation(self):
        # passe la souris en mode de creation de path pour IA bleue a
        # l'appui sur le bouton 'Path creation mode'
        global zone_dessin
        self.mode = 'path_creation'
        for x in IA :
            pts = x.points_list
            for i in range(len(pts)-1) :
                pts[i].plot()
                pts[i].bind(pts[i+1])

    def In_Outils(self,event):
        self.where = "zone_outils"
    def Out(self,event):
        self.where = None
    def In_Dessin(self,event):
        self.where = "zone_dessin"

    ## les fonctions d'edition

    def mouse_color_click(self,event):
    # permet de donner a la souris la couleur qui a ete choisie
        for button in self.buttons:
            if button.selected :
                button.highlight_button() #on enleve la precedente selection
            if (event.x//CELL_SIZE,event.y//CELL_SIZE) == button.pos:
                self.color = button.color
                self.mode = 'normal' #on repasse en mode normal
                button.highlight_button()

    def print_color(self,event):

    # permet en mode normal de deposer sur le canevas un rectangle de couleur self.color
    # permet en mode creation de chemin de dessiner le chemin de la derniere IA selectionnee

        global zone_dessin , int_matrix, rect_matrix, paths_matrix, color_dict, IA_bleues

        j , i = event.x//CELL_SIZE , event.y//CELL_SIZE

        if 1<=i<=19 and 1<=j<=30: # on ne doit pas changer les murs exterieurs
            rect = rect_matrix[i][j]

            # Cas 1: on est en mode normal d'edition
            if self.mode == 'normal':
                if rect.color != self.color:
                    if self.color == 'blue' or self.color == 'darkblue'  or self.color == 'purple' or  self.color == 'darkpurple' : #on a affaire a une IA necessitant un path
                        newIA = IA_rectangle(zone_dessin,i,j,self.color)
                        rect_matrix[i][j] = newIA
                        int_matrix[i][j] = color_dict[self.color][1]
                        newIA.id = len(IA)
                        IA.append(newIA)
                        paths_matrix.append([])
                    else :
                        rect_matrix[i][j] = rectangle(zone_dessin,i,j,self.color)
                        int_matrix[i][j] = color_dict[self.color][1]

            # Cas 2: on est en mode creation de chemin d'IA bleue
            if self.mode == 'path_creation' :
                n = int_matrix[i][j]
                if n == 6 or n==7 or n==10 or n==11 : #on a affaire a une IA qui necessite un path
                    for x in IA :
                        if x.selected :
                            x.highlight_rect() #on deselectionne toutes les IA
                        cwia = rect_matrix[i][j]
                        self.selected = cwia.id
                        cwia.highlight_rect()
                elif self.selected != None :
                    cwia = IA[self.selected]
                    pt=way_point(zone_dessin,i,j,cwia.id)
                    pt.bind(cwia.points_list[-1])
                    pt.plot()
                    cwia.points_list.append(pt)
                    paths_matrix[cwia.id] = cwia.points_list

    def mouse_click_left(self,event):
        if self.where == 'zone_dessin':
            self.print_color(event) # on effectue l'action de la zone de dessin
        elif self.where == 'zone_outils':
            self.mouse_color_click(event) #on effecture l'action de la zone des outils

    def mouse_click_right(self,event) :
    #N'est activee que dans la zone de dessin (contrairement au clic gauche)

        global zone_dessin , int_matrix, rect_matrix, paths_matrix, color_dict, number
        if  self.where=="zone_dessin" :

            if self.mode == 'normal' :    #En mode normal, permet d'effacer le rectangle sur lequel pointe la souris
                j , i = event.x//CELL_SIZE , event.y//CELL_SIZE
                if 1<=i<=19 and 1<=j<=30: # on ne doit pas changer les murs exterieurs
                    rect = rect_matrix[i][j]
                if self.mode == 'normal' :
                    rect_matrix[i][j] = rectangle(zone_dessin,i,j, "white")
                    int_matrix[i][j] = 0

            elif self.mode == 'path_creation' : #En mode path_creation, permet d'enlever un point du chemin
                if self.selected != None :
                    cwia = IA[self.selected]
                    pts = cwia.points_list
                    if (len(pts))>1 :
                        pts.pop()
                        cwia.points_list = pts
                        paths_matrix[cwia.id] = pts
                        zone_dessin.delete(("paths",str(cwia.id)))
                        for i in range(len(pts)-1) :
                            pts[i].plot()
                            pts[i].bind(pts[i+1])


## CLASSES DIVERSES

class rectangle():
    '''regroupe un rectangle du canevas, sa couleur et sa position'''
    def __init__(self,can,i,j,color):
        global color_dict
        rect = can.create_rectangle(CELL_SIZE*j , CELL_SIZE*i , CELL_SIZE*(j+1) , CELL_SIZE*(i+1) ,
                            width=1, fill= color_dict[color][0], outline= "black")
        self.rect = rect
        self.color = color
        self.pos = (j,i)
        self.master = can
        self.selected = False

class IA_rectangle() :
    ''' un rectangle d'une IA bleue. Contient, en plus d'un rectangle classique, le parcours de l'IA'''
    def __init__(self,can,i,j,color) :
        global zone_dessin, color_dict
        rect = can.create_rectangle(CELL_SIZE*j , CELL_SIZE*i , CELL_SIZE*(j+1) , CELL_SIZE*(i+1) ,
                            width=1, fill= color_dict[color][0], outline= "black")
        self.rect = rect
        self.color = color
        self.pos = (j,i)
        self.master = can
        self.id = -1
        self.selected = False
        self.points_list = [way_point(zone_dessin,i,j,self.id)] #liste d'objets de classe way_point formant le chemin suivi

    def highlight_rect(self) :
        can = self.master
        j,i = self.pos
        color=self.color
        if not self.selected :
            self.rect = can.create_rectangle(CELL_SIZE*j , CELL_SIZE*i , CELL_SIZE*(j+1) , CELL_SIZE*(i+1) , width=1, fill= color_dict[color][0], outline= "#fe2")
            self.points_list[0] = way_point(zone_dessin,i,j,self.id)
        else :
            self.rect = can.create_rectangle(CELL_SIZE*j , CELL_SIZE*i , CELL_SIZE*(j+1) , CELL_SIZE*(i+1), width=1, fill = color_dict[color][0], outline='black')
            self.points_list[0] = way_point(zone_dessin,i,j,self.id)
        self.selected = not self.selected

class way_point() :
    def __init__(self,can,i,j,n):
        rect = can.create_rectangle(CELL_SIZE*j+5 , CELL_SIZE*i+5 , CELL_SIZE*(j+1)-5 , CELL_SIZE*(i+1)-5 ,
                                    width=1, fill= "#aaa", outline= "#000", tag = ("path",str(n)))
        self.id = n
        self.rect = rect
        self.color = "#aaa"
        self.pos = (j,i)

    def bind(self,wp) : #trace une ligne entre deux waypoints
        global zone_dessin
        (j1,i1)= self.pos
        (j2,i2)= wp.pos
        x1,y1,x2,y2= CELL_SIZE*j1+12 , CELL_SIZE*i1+12 , CELL_SIZE*j2+12 , CELL_SIZE*i2+12
        if abs(x1-x2) > abs(y1-y2):
                zone_dessin.create_line(x1,y1,x2,y1, x2,y2, fill = "#aaa", width = 1, tag = ("path",str(self.id)))
        else :
            zone_dessin.create_line(x1,y1,x1,y2, x2,y2, fill = "#aaa", width = 1, tag = ("path",str(self.id)))

    def plot(self) :
        global zone_dessin
        (j,i) = self.pos
        zone_dessin.create_rectangle(CELL_SIZE*j+8,CELL_SIZE*i+8,CELL_SIZE*(j+1)-8,CELL_SIZE*(i+1)-8, tag=("path",str(self.id)))

class color_button():
    # classe des boutons-outil
    def __init__(self,can,x1,y1,x2,y2,color):
        rect, text = self.create_button(can,x1,y1,x2,y2,color)
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
        text = can.create_text(x2+4,(y1+y2)/2, text=type_dict[color], anchor=W)
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


## LA FONCTION PRINCIPALE

def level_editor() :

    global int_matrix, paths_matrix, zone_dessin

    fenetre = Tk()
    fenetre.title("Tank Game Level Editor")

    # la souris
    souris = mouse(fenetre)
    fenetre.bind("<Button-1>",souris.mouse_click_left)
    fenetre.bind("<Button-3>", souris.mouse_click_right)
    bout = Button(fenetre,text='Exit',command=fenetre.destroy)
    bout.pack()

    # la fenetre de boutons d'action
    fenetre_divers = LabelFrame(fenetre,text="Options")
    fenetre_divers.pack(side=RIGHT)
    b_normal = Button(fenetre_divers, text="Normal mode", command=souris.mouse_normal)
    b_normal.pack()
    b_path = Button(fenetre_divers, text="Path creation mode", command=souris.mouse_path_creation)
    b_path.pack()
    exporter = Button(fenetre_divers,text="Export",command=export)
    exporter.pack()
    clear_all = Button(fenetre_divers, text = "Clear All" , command = clear)
    clear_all.pack()
    clear_p = Button(fenetre_divers, text = "Clear Paths", command = clear_paths)
    clear_p.pack()

    # la fenetre de boutons-outil
    fenetre_outils = LabelFrame(fenetre , text="Outils")
    fenetre_outils.bind("<Button-1>",souris.mouse_color_click)
    fenetre_outils.bind("<Enter>",souris.In_Outils)
    fenetre_outils.bind("<Leave>",souris.Out)
    fenetre_outils.pack(side=LEFT)
    zone_outils=Canvas(fenetre_outils, width=120, height=516)
    zone_outils.pack()

    # la fenetre de dessin
    fenetre_dessin = LabelFrame(fenetre, text="Map")
    fenetre_dessin.bind("<Enter>",souris.In_Dessin)
    fenetre_dessin.bind("<Leave>",souris.Out)
    fenetre_dessin.pack(side=RIGHT)
    zone_dessin = Canvas(fenetre_dessin, width = 640, height = 400)
    zone_dessin.pack()

    # creation des boutons-outil dans le canevas zone_outils
    buttons = []
    for color in color_dict:
        n = color_dict[color][1]
        button = color_button(zone_outils,4, CELL_SIZE*(n+1), 4+CELL_SIZE, CELL_SIZE*(n+2), color)
        buttons.append(button)
    souris.buttons = buttons

    clear()
    fenetre.mainloop()

if __name__ == "__main__" :
    level_editor()
