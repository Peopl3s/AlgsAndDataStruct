#include <iostream>
template<typename T>
class queue
{
    private:
    struct node;
    node* head, *tail;
    size_t size;
    
    public:
    queue();
    queue(const queue&);
    ~queue(); 
    void enqueue(const T&);
    void dequeue ();
    void show()const;
    const T& front() const;
    const T& back() const;
    size_t getSize()const;
    
};

template<typename T>
queue<T>::queue() : head(nullptr), tail(nullptr), size(0)
{
}

template<typename T>
queue<T>::queue(const queue& rhs) : size(rhs.size)
{
    node* tmp = rhs.head;
    while(tmp != nullptr)
    {
        enqueue(tmp -> data);
        tmp = tmp -> next;
    }
}

template<typename T>
queue<T>::~queue()
{
    while(head != nullptr)
    {
        node* tmp = head -> next;
        delete head;
        head = tmp;
    }
    size = 0;
}

template<typename T>
void queue<T>::enqueue(const T& val)
{
    node* newNode = new node(val);
    if(head == nullptr)
    {
        head = tail = newNode;
    } else
    {
        tail -> next = newNode;
        tail = newNode;
    }
    ++size;
}

template<typename T>
void queue<T>::dequeue()
{
   if(head == nullptr) return;
    node* tmp = head;
    head = head -> next;
    delete tmp;
    --size;
}

template<typename T>
const T& queue<T>::front() const
{
   if(head != nullptr) return head -> data;
   else throw std::string("Empty"); 
}

template<typename T>
const T& queue<T>::back() const
{
   if(tail != nullptr) return tail -> data;
   else throw std::string("Empty"); 
}

template<typename T>
size_t queue<T>::getSize() const
{
   return size;
}

template<typename T>
void queue<T>::show() const
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
struct queue<T>::node
{
    T data;
    node* next;
    node() = default;
    node(const T& val) : data(val), next(nullptr){}
};

int main()
{

}
