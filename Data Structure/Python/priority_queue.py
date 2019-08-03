class Priority_Queue:
    class Node:
        def __init__(self, data = None, priority = None):
            self.data = data
            self.priority = priority
    def __init__(self):
        self.queue = list()
        
    def isEmpty(self):
        return len(self.queue) == 0
    
    def enqueue(self, value, priprity):
        node = self.Node(value, priprity)
        if self.isEmpty():
            self.queue.append(node)
        else:
            for x in range(0, len(self.queue)):
                if node.priority >= self.queue[x].priority:
                    if x == (len(self.queue) - 1):
                        self.queue.insert(x + 1, node)
                    else:
                        continue
                else:
                    self.queue.insert(x, node)
    def dequeue(self):
        return self.queue.pop(0)
    
    def top(self):
        return (self.queue[0].data, self.queue[0].priority)
        
    def show(self):
        for x in self.queue:
            print(str(x.data)+" - "+str(x.priority))
