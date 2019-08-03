#include <iostream>
#include <cstring>
#include <initializer_list>
#include <type_traits>

template <typename T>
class Array
{
    template<typename U>
    friend std::ostream& operator<<(std::ostream &, const Array<U>&);
    
    //template<typename U, unsigned int K>
    //friend std::istream& operator>>(std::istream &,  Array<U, K>&);
    
    private:
    T* arrPtr_;
    size_t sizeArr_;
    size_t capacity_;
   
    
    public:
    Array();
    
    Array(const size_t &);
    
    template <typename U>
    Array(const std::initializer_list<U>&);
    
    Array(const Array<T> &);
    
    Array& operator=(const Array<T>&);
    
    template <typename U>
    Array(const Array<U> &);
    
    template <typename U>
    Array& operator=(const Array<U>&);
    
    Array(Array<T>&&);
    
    Array& operator=(Array<T> &&) &&;    
    
    template <typename V>
    friend class Array;
    
    virtual ~Array();
    
    size_t getSize() const;

    size_t getCapacity() const;
    
    void resize(const size_t&);
    
    bool operator==(const Array &rhs) const;
    
    T& operator[](const int &);
    
    const T& operator[](const int &) const;
    
    int search(const T &) const;
    
    Array<T>& eraseVal(const T&);
    
    void push_back(const T&);
    
};

template<typename T>
Array<T>::Array() : arrPtr_(nullptr), sizeArr_(0), capacity_(0)
{
}


template<typename T>
Array<T>::Array(const size_t &sz)
{
    if (sz > 0)
    {
        sizeArr_ = sz;
        capacity_ = sizeArr_ * 1.5;
        
        arrPtr_ = new(std::nothrow) T[capacity_];
        if (arrPtr_ != nullptr) 
        {
            memset(arrPtr_, 0, sizeArr_*sizeof(T));
        } else std::cerr<<"Bad alloc"<<std::endl;
    }

}

template <typename T>
template <typename U>
Array<T>::Array(const std::initializer_list<U> &il)
{
    if(il.size() > 0)
    {
        sizeArr_ = il.size();
        capacity_ = sizeArr_ * 1.5;
        arrPtr_ = new(std::nothrow) T[capacity_];
        if (arrPtr_ != nullptr)
        {
            auto it = il.begin(); 
            int i = 0;
            for(; it != il.end(); ++it, ++i)
            {
                arrPtr_[i] = *it;
            }
        } else std::cerr<<"Bad alloc"<<std::endl;    
    }
}

template <typename T>
template <typename U>
Array<T>::Array(const Array<U> &rhs):sizeArr_(rhs.sizeArr_), capacity_(rhs.capacity_)
{
    std::cout<<"Copy const";
        arrPtr_ = new(std::nothrow) T[capacity_];
        if (arrPtr_ != nullptr) 
        {
            for(int i = 0; i != sizeArr_; ++i)
            {
                arrPtr_[i] = rhs.arrPtr_[i];
            }
        } else std::cerr<<"Bad alloc"<<std::endl;
}

template <typename T>
Array<T>::Array(const Array<T> &rhs):sizeArr_(rhs.sizeArr_), capacity_(rhs.capacity_)
{
    std::cout<<"Copy const";
        arrPtr_ = new(std::nothrow) T[capacity_];
        if (arrPtr_ != nullptr) 
        {
            for(int i = 0; i != sizeArr_; ++i)
            {
                arrPtr_[i] = rhs.arrPtr_[i];
            }
        } else std::cerr<<"Bad alloc"<<std::endl;
}


template <typename T>
Array<T>::~Array()
{
    if (arrPtr_ != nullptr)
    {
        delete[] arrPtr_;
        arrPtr_ = nullptr;
    }
}

template <typename T>
template <typename U>
Array<T>&  Array<T>::operator=(const Array<U>& rhs)
{
    if(&rhs != this)
    {

        if(sizeArr_ != rhs.sizeArr_)
        {
            delete[] arrPtr_;
            sizeArr_ = rhs.sizeArr_;
            capacity_ = rhs.capacity_;
            using commType = typename std::common_type<T,U>::type;
            arrPtr_ = new(std::nothrow) commType[capacity_];
            if (arrPtr_ != nullptr) 
            {
                for( int i = 0; i != sizeArr_; ++i)
                {
                    arrPtr_[i] = rhs.arrPtr_[i];
                }
            } else std::cerr<<"Bad alloc"<<std::endl;
        }
    }
}

template <typename T>
Array<T>&  Array<T>::operator=(const Array<T>& rhs)
{
	std::cout<<"operator=&";
    if(&rhs != this)
    {

        if(sizeArr_ != rhs.sizeArr_)
        {
            delete[] arrPtr_;
            sizeArr_ = rhs.sizeArr_;
            capacity_ = rhs.capacity_;
            arrPtr_ = new(std::nothrow) T[capacity_];
            if (arrPtr_ != nullptr) 
            {
                for( int i = 0; i != sizeArr_; ++i)
                {
                    arrPtr_[i] = rhs.arrPtr_[i];
                }
            } else std::cerr<<"Bad alloc"<<std::endl;
        }
    }
    return *this;
}


template <typename T>
Array<T>::Array(Array<T>&& rhs)
{
    std::cout<<"Move const";
    sizeArr_ = rhs.sizeArr_;
    capacity_ = rhs.capacity_;
    arrPtr_ = rhs.arrPtr_;
    rhs.sizeArr_ = 0;
    rhs.arrPtr_ = nullptr;
}



template <typename T>
Array<T>& Array<T>::operator=(Array<T> &&rhs) &&
{
    if(this != &rhs)
    {
        if(arrPtr_ != nullptr)
        {
            delete[] arrPtr_;
            sizeArr_ = rhs.sizeArr_;
            arrPtr_ = rhs.arrPtr_;
            capacity_ = rhs.capacity_;
            rhs.sizeArr_ = 0;
            rhs.arrPtr_ = nullptr;
        }
    }
    return *this;
}


template <typename T>
size_t Array<T>::getSize() const
{ 
    return sizeArr_; 
}

template <typename T>
size_t Array<T>::getCapacity() const
{ 
    return capacity_; 
}

template <typename T>
void Array<T>::resize(const size_t& newSize) 
{ 
    capacity_ = newSize * 1.5;
    T* newArr = new T[capacity_];
    if(arrPtr_ != nullptr)
    {
        size_t counter = newSize > sizeArr_ ? sizeArr_ : newSize;
        
        for(size_t i = 0; i != counter; ++i)
        {
            newArr[i] = arrPtr_[i];
        }
        delete[] arrPtr_;
        arrPtr_ = newArr;
        sizeArr_ = newSize;
    }
}

template <typename T>
bool Array<T>::operator==(const Array &rhs) const
{
    if(sizeArr_ != rhs.getSize() || capacity_ != rhs.capacity_) return false;
    for(int i = 0; i != sizeArr_; ++i)
    {
        if(arrPtr_[i] != rhs.arrPtr_[i]) return false;
    }
    return true;
}

template <typename T>   
T& Array<T>::operator[](const int &index)
{
    if (index >= 0 && index <= sizeArr_)
    {
        return arrPtr_[index];
    } else std::cerr<<"Index out of ranfe"<<std::endl;
}


template <typename T>   
const T& Array<T>::operator[](const int &index) const
{
    if (index >= 0 && index <= sizeArr_)
    {
        return arrPtr_[index];
    } else std::cerr<<"Index out of ranfe"<<std::endl;
}

template <typename T>   
std::ostream& operator<<(std::ostream &os, const Array<T> &arr)
{
    for(size_t i = 0; i != arr.getSize(); ++i)
    {
        os<<arr[i]<<" ";
    }
    os<<std::endl;
    return os;
}

template <typename T>  
int Array<T>::search(const T &val) const
{
    for(size_t i = 0; i != sizeArr_; ++i)
    {
        if(arrPtr_[i] == val) return i;
    }
    return -1;
}

template <typename T>  
Array<T>& Array<T>::eraseVal(const T &val)
{
    size_t count{0};
    for(size_t i = 0; i != sizeArr_; ++i)
    {
        if(arrPtr_[i] == val) ++count;
    }
        size_t newSize = sizeArr_ - count;
        size_t newCapacity = newSize * 1.5;
        T* newArr = new(std::nothrow) T[capacity_];
        if (newArr != nullptr) 
        {
            for( size_t i = 0, j = 0; i != sizeArr_; ++i)
            {
                if(arrPtr_[i] != val)
                {
                    newArr[j] = arrPtr_[i];
                    ++j;
                }
            }
            delete[] arrPtr_;
            sizeArr_ = newSize;
            capacity_ = newCapacity;
            arrPtr_ = newArr;
        } else std::cerr<<"Bad alloc"<<std::endl;
    
    return *this;
}
template<typename T>
void Array<T>::push_back(const T& val)
{
    if(sizeArr_ == capacity_)
    {
        resize(sizeArr_ + 1);
        --sizeArr_;  
	}    
	arrPtr_[++sizeArr_] = val;
}

int main()
{
	

}
