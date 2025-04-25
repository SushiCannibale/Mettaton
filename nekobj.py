class Neko(object):
    def __init__(self, id : int, url : str, width : int, height : int):
        self.id = id
        self.url = url
        self.width = width
        self.height = height

class NekoStore(object):
    def __init__(self, id_next : int, nekos : list[Neko]):
        self.id_next = id_next
        self.nekos = nekos