#include <iostream>
#include <stdexcept>
template<typename T>
class stack
{
    private:
    struct node;
    node* head, *tail;
    size_t size;
    public:
    stack();
    ~stack();   
    void push(const T&);
    T top();
    T peek(const size_t&);
    void pop();
    void show()const;
    size_t getSize() const;
    
};

template<typename T>
stack<T>::stack() : head(nullptr), tail (nullptr), size(0)
{
}

template<typename T>
stack<T>::~stack()
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
struct stack<T>::node
{
    T data;
    node* next;
    node() = default;
    node(const T& val) : data(val), next(nullptr){}
};

template<typename T>
void stack<T>::push(const T& val)
{
    
    node* newNode = new node(val);
    newNode -> next = head;
    head = newNode;
    ++size;
}

template<typename T>
void stack<T>::pop()
{
    if( head == nullptr) return;
    node* tmp = head;
    head = tmp -> next;
    delete tmp;
 
    --size;
}

template<typename T>
T stack<T>::top()
{
    if(head != nullptr) return head -> data;
    else throw std::out_of_range("empty");
}

template<typename T>
T stack<T>::peek(const size_t& n)
{
    if(head == nullptr || n < 0 || n > size) throw std::out_of_range("empty");;
    size_t count{0};
    node* tmp = head;
    while(count <n)
    {
        tmp = tmp -> next;
        ++count;
    }
    return tmp -> data;
   
}

template<typename T>
size_t stack<T>::getSize() const
{
   return size;
}

template<typename T>
void stack<T>::show() const
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

int main()
{
	
}
