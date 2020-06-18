import json

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
        entities = dict()
        for i in range(Level.WIDTH):
            for j in range(Level.HEIGHT):
                if self.tileMap[i,j] in entities:
                    entities[self.tileMap[i,j]]["position"].append([i,j])
                else:
                    entities[self.tileMap] = {"position" : [[i,j]]}
        with open(fileName,'w') as output:
            json.dump(entities, output)

    def clear(self):
        for i in range(Level.WIDTH):
            for j in range(level.HEIGHT):
                tileMap[i,j] = " "

    def add_entity(self, i, j, ent):
        self.tileMap[i,j] = ent