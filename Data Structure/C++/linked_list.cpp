#include <iostream>

template<typename T>
class linkedList
{
    private:
    struct node;
    node* head, *tail;
    size_t count;
    public:
    linkedList();
    ~linkedList();
    void addToTail(const T&);
    void addToHead(const T&);
    void removeFromHead();
    void removeElementByVal(const T&);
    void show();
    bool contain(const T&);
    void insert(node* pos, const T&);
    

};

template<typename T>
struct linkedList<T>::node
{
    T data;
    node* next;
    node() = default;
    node(const T& val) : data(val), next(nullptr){}
};

template<typename T>
linkedList<T>::linkedList() : head(nullptr), tail (nullptr), count(0)
{
}  

template<typename T>
linkedList<T>::~linkedList()
{
    while(head != nullptr)
    {
        node* tmpNewHead = head->next;
        delete head;
        head = tmpNewHead;
    }
    tail = nullptr;
    count = 0;
}

template<typename T>
void linkedList<T>::addToTail(const T& val)
{
    node* newNode = new (std::nothrow) node(val);
    if(newNode != nullptr)
    {
        if(head == nullptr)
        {
            head = tail = newNode;
        } else
        {
            tail -> next = newNode;
            tail = newNode;
            ++count;
        }
    }
}

template<typename T>
void linkedList<T>::addToHead(const T& val)
{
    node* newNode = new (std::nothrow) node(val);
    if(newNode != nullptr)
    {
       newNode -> next = head;
       head = newNode;
       ++count;
    } 
}

template<typename T>
void linkedList<T>::removeFromHead()
{
    if (head != nullptr)
    {
        node* newNode = head -> next;
        delete head;
        head = newNode;
    }
}

template<typename T>
void linkedList<T>::removeElementByVal(const T& val)
{
    if (head == nullptr) return;
    
    node *current = head, *prev = nullptr;
    while( current != nullptr)
    {
        if(current -> data == val)
        {
            if(prev != nullptr)
            {
               prev -> next = current -> next;
                if(current -> next == nullptr)
                {
                    tail = prev;
                    tail -> next == nullptr;
                }
                delete current;
                current = prev;
            }
            else
            {
                current = head -> next;
                delete head;
                head = current;
                if(head == nullptr)
                {
                    tail = nullptr;
                }
                
            }
            --count;
        }
        prev = current;
        current = current -> next;
    }
}

template<typename T>
void linkedList<T>::show()
{
    node *tmp = head;
    while(tmp != nullptr)
    {
        std::cout<<tmp -> data<<" ";
        tmp = tmp -> next;
    }
    std::cout<<std::endl;
}

template<typename T>
bool linkedList<T>::contain(const T &val)
{
    if(head == nullptr) return false;
    node* tmp = head;
    while(tmp != nullptr)
    {
        if( tmp -> data == val) return true;
        tmp = tmp -> next;
    }
    return false;
}
template<typename T>
void linkedList<T>::insert(node *pos, const T &val)
{
    if(pos == nullptr) return;
    node *curr = head, *prev = nullptr;
    while( curr != pos)
    {
        prev = curr;
        curr = curr -> next;
    }
    
    node* newNode = new (std::nothrow) node(val);
    if(newNode != nullptr)
    {
        if(pos == head)
        {
            newNode -> next = head;
            head = newNode;
        } else
        {
            newNode -> next = pos;
            prev -> next = newNode;
        }
    }
    ++count;
}
    
int main()
{
 
}

