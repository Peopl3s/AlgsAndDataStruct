class DoubleLinkedList:
    class Node:
        def __init__(self, data = None, next = None, prev = None):
            self.data = data
            self.next = next
            self.prev = prev
            
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0
        
    def addToTail(self, value):
        self.length += 1
        if self.head == None:
            self.head = self.tail = self.Node(value, None, None)
            self.head.next = self.tail
            tail.next = None
            self.head.prev = None
        else:
            nd = self.Node(value, None, None)
            nd.prev = self.tail
            self.tail.next = nd
            self.tail = nd
            
    def addToHead(self, value):
        self.length += 1
        if self.head == None:
            self.head = self.tail = self.Node(value, None, None)
            self.head.next = self.tail
            self.tail.next = None
            self.head.prev = None
        else:
            nd = self.Node(value, None, None)
            nd.next = self.head
            self.head.prev = nd
            self.head = nd
    
    def insertInPos(self, index, value):
        if index < 0 or index > self.length + 1:
            return
        if index == 0: addToHead(value)
        if index == self.length + 1: addToTail(value)
        tmp = self.head
        nd = self.Node(value, None, None)
        n = 0
        while n!= index:
            tmp = tmp.next
            n += 1
        tmp.prev.next = nd
        nd.next = tmp
        nd.prev = tmp.prev
        tmp.prev = nd
        self.length += 1
            
    def getLength(self):
        return self.length
    
    def remove(self, value):
        curr = self.head
        while curr != None:
            if curr.data == value:
                tmp = curr
                if curr == self.tail:
                    self.tail = self.tail.prev
                    self.tail.next = None
                if curr.next != None:
                    curr.next.prev = curr.prev
                if curr.prev != None:
                    curr.prev.next = curr.next
                    curr = curr.next
                else:
                    self.head = curr.next
                    curr = self.head
            else:
                curr = curr.next
        self.length -= 1
        
    def search(self, value):
        curr = self.head
        index = 0
        while curr != None:
            if curr.data == value:
                return (True, index)
            curr = curr.next
            index += 1
        return (False, -1)

    def showFromHead(self):
        if self.head == None: return
        curr = self.head
        while curr != None:
            print(curr.data, sep=' ')
            curr = curr.next
            
    def showFromTail(self):
        if self.head == None: return
        curr = self.tail
        while curr != None:
            print(curr.data, sep=' ')
            curr = curr.prev     
            
    def __str__(self):
        if self.head == Nonde: return 'LinkedList []'
        curr = self.head
        out = 'LinkedList: '
        while curr != None:
            out += str(curr.data)+' '
            curr = curr.next
        return out  
    
    def sort(self):
        if self.head == None: return
        for i in range(0, self.length - 1):
            tmp = self.head
            while tmp.next != None:
                if tmp.data > tmp.next.data:
                    tmp.data, tmp.next.data = tmp.next.data, tmp.data
                tmp = tmp.next
