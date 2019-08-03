#include <iostream>
#include <vector>

template<typename T>
class priority_queue
{
    private:
    struct element;
    std::vector<element> elements;
    size_t size;
    void up(size_t i);
    void down(size_t i);
    
    public:
    priority_queue();
    priority_queue(const priority_queue&);
    ~priority_queue(); 
    void enqueue(const T&, const size_t&);
    T dequeue();
    void show()const;
    const T top() const;
    size_t getSize()const;
    
};

template<typename T>
struct priority_queue<T>::element
{
    T data;
    size_t priprity;
    element() = default;
    element(const T& val, const size_t& pty) : data(val), priprity(pty){}
    ~element(){}
};

template<typename T>
void priority_queue<T>::up(size_t i)
{
    while(i != 0 && elements[i].priprity > elements[(i - 1) / 2].priprity)
    {
        std::swap(elements[i], elements[(i - 1) / 2]);
        i = (i - 1) / 2;
    } 
}

template<typename T>
void priority_queue<T>::down(size_t i)
{
    while( i < size / 2)
    {
        size_t maxI = 2 * i + 1;
        if( 2 * i + 2 < size && elements[2 * i + 2].priprity > elements[2 * i + 1].priprity)
            maxI = 2 * i + 2;
        if(elements[i].priprity >= elements[maxI].priprity) return;
        std::swap(elements[i], elements[maxI]);
        i = maxI;
    }
}

template<typename T>
priority_queue<T>::priority_queue() : size(0)
{
}

template<typename T>
priority_queue<T>::~priority_queue()
{
}

template<typename T>
priority_queue<T>::priority_queue(const priority_queue& rhs) : element(rhs.element), size(rhs.size)
{
}

template<typename T>
void priority_queue<T>::enqueue(const T& val, const size_t& pty)
{
    elements.push_back(element(val, pty));
    ++size;
    up (size - 1);
}

template<typename T>
T priority_queue<T>::dequeue()
{
    if(size <= 0) throw std::string("empty");
    std::swap(elements[0], elements[--size]);
    down(0);
    return elements[size].data;
}

template<typename T>
void priority_queue<T>::show() const
{
    for(const auto& x : elements)
    {
        std::cout<<x.data<<" ";
    }
    std::cout<<std::endl;
}

template<typename T>
const T priority_queue<T>::top() const
{
    return elements[0].data;
}

template<typename T>
size_t priority_queue<T>::getSize() const
{
    return size;
}

int main()
{
}
