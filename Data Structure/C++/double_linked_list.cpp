#include <iostream>

template<typename T>
class doubleLinkedList
{
    private:
    struct node;
    node* head, *tail;
    size_t count;
    public:
    doubleLinkedList();
    ~doubleLinkedList();
    void addToHead(const T&);
    void addToTail(const T&);
    void showFromHead();
    void showFromTail();
    int search(const T&) const;
    void eraseElementByVal(const T&);
    void insert(const size_t&, const T&);
    void sort(const bool& ascending = true);
    
};


template<typename T>
struct doubleLinkedList<T>::node
{
    T data;
    node* next, *prev;
    node() = default;
    node(const T& val) : data(val), next(nullptr), prev(nullptr){}
};

template<typename T>
doubleLinkedList<T>::doubleLinkedList() : head(nullptr), tail(nullptr), count(0)
{
}  

template<typename T>
doubleLinkedList<T>::~doubleLinkedList()
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
void doubleLinkedList<T>::addToHead(const T &val)
{
    node* newNode = new(std::nothrow) node(val);
    if(newNode != nullptr)
    {
        if (head == nullptr) 
        {
            head = tail = newNode;
            head -> next = tail;
            tail ->next = nullptr;
            head -> prev = nullptr;
        }
        else 
        {
            newNode -> next = head;
            head -> prev = newNode;
            head = newNode;
        }
    }
    ++count;
}

template<typename T>
void doubleLinkedList<T>::showFromHead()
{
    if(head == nullptr) return;
    node* tmp = head;
    while(tmp != nullptr)
    {
        std::cout<<tmp -> data<<" ";
        tmp = tmp -> next;
    }
    std::cout<<std::endl;
}

template<typename T>
void doubleLinkedList<T>::showFromTail()
{
    if(head == nullptr) return;
    node* tmp = tail;
    while(tmp != nullptr)
    {
        std::cout<<tmp -> data<<" ";
        tmp = tmp -> prev;
    }
    std::cout<<std::endl;
}

template<typename T>
void doubleLinkedList<T>::addToTail(const T &val)
{
    node* newNode = new(std::nothrow) node(val);
    if(newNode != nullptr)
    {
        if (head == nullptr) 
        {
            head = tail = newNode;
            head -> next = tail;
            tail ->next = nullptr;
            head -> prev = nullptr;
        }
        else 
        {
            newNode -> prev = tail;
            tail -> next = newNode;
            tail = newNode;
        }
    }
    ++count;
}

template<typename T>
int doubleLinkedList<T>::search(const T &val) const
{
    if(head == nullptr) return -1;
    node* tmp = head;
    size_t pos{0};
    while(tmp != nullptr)
    {
        if(tmp -> data == val) return pos;
        tmp = tmp -> next;
        ++pos;
    }
    return -1;
}   

template<typename T>
void doubleLinkedList<T>::eraseElementByVal(const T& val)
{
   for ( node *current = head; current != nullptr; )
   {
       if ( current-> data == val )
       {
           node *tmp = current;
           if( current == tail)
           {
               tail = tail -> prev;
               tail -> next = nullptr;
           }
           if ( current->next != nullptr )
           {
               current->next->prev = current->prev;
           }

           if ( current->prev != nullptr )
           {
               current -> prev -> next = current -> next;
               current = current -> next;
           }
           else
           {
               head = current -> next;
               current = head;
           }
           delete tmp;
           --count;
       }
       else
       {
           current = current->next;
       } 
    }
}


template<typename T>
void doubleLinkedList<T>::insert(const size_t& pos, const T& val)
{
    if( head == nullptr || pos < 0 || pos > count + 1) return;
    if(pos == 0) addToHead(val);
    if(pos == count + 1) addToTail(val);
    
    node* tmp = head;
    node* newNode = new node(val);
    size_t n{0};
    while(n != pos)
    {
        tmp = tmp -> next;
        ++n;
    }

    tmp -> prev -> next = newNode;
    newNode -> next = tmp;
    newNode -> prev = tmp -> prev;
    tmp -> prev = newNode;
    ++count;
    
}

template<typename T>
void doubleLinkedList<T>::sort(const bool& ascending)
{
     if (head == nullptr) return;

   for(int i = 0; i != count; i++)
   {  
        node *temp = head;
        while(temp -> next != nullptr) 
        {     
            if(temp -> data > temp -> next -> data) 
            {
                T tmpVal = temp -> data;     
                temp -> data = temp -> next -> data;
                temp -> next -> data = tmpVal;
            }
            temp = temp -> next;  
        }
    }
}

int main()
{
	
}

