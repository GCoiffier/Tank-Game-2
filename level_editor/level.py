import json
import os

class Level:

    WIDTH = 40
    HEIGHT = 25

    def __init__(self, tm = None):
        if tm is None:
            self.tileMap = [[None for _ in range(Level.HEIGHT)] for _ in range(Level.WIDTH)]
        else:
            self.tileMap = tm

    @staticmethod
    def from_file(self, fileName):
        with open(fileName, 'r') as inpt:
            lines = inpt.readlines()
        s = "".join([x.strip() for x in lines])
        self.entities = json.loads(s)
        for entity in self.entities:
            for (i,j) in self.entities[entity]["position"]:
                self.tileMap[i,j] = entity

    def to_file(self, fileName):
        path = os.path.join("../static/levels", fileName)
        entities = dict()
        for i in range(Level.WIDTH):
            for j in range(Level.HEIGHT):
                if self.tileMap[i][j] is not None:
                    if self.tileMap[i][j] in entities:
                        entities[self.tileMap[i][j]]["position"].append([i,j])
                    else:
                        entities[self.tileMap[i][j]] = {"position" : [[i,j]]}
                    
                    if "obstacles" in self.tileMap[i][j]:
                        entities[self.tileMap[i][j]]["connect_adjacent"] = True

        with open(fileName,'w') as output:
            json.dump(entities, output)

    def clear(self):
        for i in range(Level.WIDTH):
            for j in range(Level.HEIGHT):
                self.tileMap[i][j] = None

    def __getitem__(self, ind):
        i,j = ind
        return self.tileMap[i][j]

    def __setitem__(self, ind, item):
        i,j = ind
        self.tileMap[i][j] = item