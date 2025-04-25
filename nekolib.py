from jsonpickle import decode as jsonpickle_decode

class Neko(object):
    def __init__(self, id, url, width, height):
        self.id = id
        self.url = url
        self.width = width
        self.height = height

class NekoStore(object):
    def __init__(self, id_next, nekos):
        self.id_next = id_next
        self.nekos = nekos

def load_nekos(filename : str):
    fp = open(filename, 'r')
    json = fp.read()
    obj = jsonpickle_decode(json)
    print(obj.nekos)

def save_nekos(store : NekoStore, filename : str):
    pass