class Queue:
    class Node:
        def __init__(self, data = None, next = None):
            self.data = data
            self.next = next
    def __init__(self):
        self.length = 0
        self.head = None
        self.tail = None
        
    def isEmpty():
        return self.length == 0
    
    def enqueue(self, value):
        node = self.Node(value, None)
        if self.length == 0:
            self.head = self.tail = node
        else:
            last = self.tail
            last.next = node
            self.tail = node
        self.length += 1
            
    def dequeue(self):
        if self.length == 0: return
        val = self.head.data
        self.head = self.head.next
        self.length -= 1
        if self.length == 0:
            self.tail = None
        return val
    
    def show(self):
        if self.head == None: return
        curr = self.head
        while curr != None:
            print(curr.data,' ')
            curr = curr.next
            
    def front(self):
        return self.head
    
    def back(self):
        return self.tail
