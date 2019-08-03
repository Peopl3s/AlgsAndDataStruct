class BSTree():
    class Node():
        def __init__(self, key=0, val=0, left = None, right = None, parent = None):
            self.key = key
            self.val = val
            self.left = left
            self.right = right
            self.parent = parent
            
        def isRoot(self):
            return not self.parent
        
        def idLeaf(self):
            return not (self.right or self.left)
        
    def __init__(self):
        self.root = None
        self.size = 0
        
    def getRoot(self):
        return self.root    
        
    def length(self):
        return self.size
    
    def add(self, key, val):
        if self.root:
            self._add(key, val, self.root)
        else:
            self.root = self.Node(key, val)
        self.size += 1
        
    def _add(self, key, val, node):
        if key < node.key:
            if node.left != None:
                self._add(key, val, node.left)
            else:
                node.left = self.Node(key, val, parent = node)
        else:
            if node.right != None:
                self._add(key, val, node.right)
            else:
                node.right = self.Node(key, val, parent = node)
                
    def search(self, key):
        if self.root:
            element = self._search(key, self.root)
            if element != None:
                return element.val
            else:
                return None
        else:
            return None
        
    def _search(self, key, node):
        if not node:
            return None
        elif node.key == key:
            return node
        elif key < node.key:
            return self._search(key, node.left)
        else:
            return self._search(key, node.right)
        
    def remove(self, key):
        if self.size > 1:
            nodeToRemove = self._search(key, self.root)
            if nodeToRemove:
                self._remove(nodeToRemove)
                self.size -= 1
            else:
                raise KeyError('Invalid key')
        elif self.size == 1 and self.root.key == key:
            self.root = None
            self.size -= 1
        else:
            raise KeyError('Invalid key')
      
    def _remove(self, node):
            if node.left == None and node.right == None:
                if node.parent == None:
                    self.root = None
                elif node.parent.right and node.parent.right.key == node.key:
                    node.parent.right = None
                elif node.parent.left and node.parent.left.key == node.key:
                    node.parent.left = None
            elif node.left != None and node.right == None:
                if node.parent == None:
                    self.root = node.left
                elif node.parent.left and node.parent.left.key == node.key:
                    node.parent.left = node.left
                elif node.parent.right and node.parent.right.key == node.key:
                    node.parent.right = node.left 
                node.left.parent = node.parent
         
            elif node.left == None and node.right != None:
                if node.parent == None:
                    self.root = right
                elif node.parent.left and node.parent.left.key == node.key:
                    node.parent.left = node.right
                elif node.parent.right and node.parent.right.key == node.key:
                    node.parent.right = node.right
                node.right.parent = node.parent
            else: 
                if node.right.left == None:
                    node.right.parent = node.parent
                    node.right.left = node.left
                    node.left.parent = node.right
                    if node.parent == None: self.root = node.right
                else:
                    lastLeft = node.right
                    while lastLeft.left:
                        lastLeft = lastLeft.left
                    lastLeft.parent.left = None
                    lastLeft.left = node.left
                    lastLeft.right = node.right
                    lastLeft.parent = node.parent
                    if node.parent == None: self.root = lastLeft
              
    def inOrderTraversal(self, node):
        if node != None:
           self.inOrderTraversal(node.left)
           print(node.val)
           self.inOrderTraversal(node.right)
        print()
        
    def preOrderTraversal(self, node):
        if node != None:
           print(node.val) 
           self.inOrderTraversal(node.left)
           self.inOrderTraversal(node.right)
        print()
    
    def postOrderTraversal(self, node):
            if node != None:
               self.inOrderTraversal(node.left)
               self.inOrderTraversal(node.right)
               print(node.val) 
            print()
    
    def findMin(self):
        curr = self.root
        while curr.left:
            curr = curr.left
        return curr
