class LinkedList:
    class Node:
        def __init__(self, data = None, next = None):
            self.data = data
            self.next = next
            
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0
        
    def addToTail(self, value):
        self.length += 1
        if self.head == None:
            self.head = self.tail = self.Node(value, None)
        else:
            self.tail.next = self.tail = self.Node(value, None)
            
    def addToHead(self, value):
         self.length += 1
         if self.head == None:
                self.head = self.tail = self.Node(value, None)
         else:
                    self.head = self.Node(value, self.head)
            
    def insertInPos(self, index, value):
        if index < 0 or index > self.length + 1:
            return
        if index == 0:
            addToHead(value)
        if index == self.length + 1:
            addToTail(value)
        curr = self.head
        n = 0
        while curr != None:
            if n == index:
                curr.next = self.Node(value, curr.next)
                break
            ++n
            curr = curr.next
            
    def getLength(self):
        return self.length
    
    def remove(self, value):
        if self.head == None: return
        curr = self.head
        prev = None
        while curr != None:
            if curr.data == value:
                if prev != None:
                    prev.next = curr.next
                    if curr.next == None:
                        tail = prev
                        tail.next =None
                    curr = prev
                else:
                    curr = self.head.next
                    self.head = curr
                    if self.head == None:
                        tail = None
            self.length -= 1
            prev = curr
            curr = curr.next
        
    def search(self, value):
        curr = self.head
        index = 0
        while curr != None:
            if curr.data == value:
                return (True, index)
            curr = curr.next
            index += 1
        return (False, -1)

    def show(self):
        if self.head == None: return
        curr = self.head
        while curr != None:
            print(curr.data, sep=' ')
            curr = curr.next
            
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
