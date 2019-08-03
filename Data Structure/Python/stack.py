class Stack:
    def __init__(self):
        self.items = []
    def push(self, value):
        self.items.append(value)
    def pop(self):
        return self.items.pop()
    def empty(self):
        return self.items == []
    def peek(self, index):
        if index > len(self.items): raise Exception('Bad index')
        return self.items[index]
    def getSize(self):
        return len(self.items)
    def show(self):
        print(' '.join(self.items))
