#include <iostream>
#include <stdexcept>
#include <list>
#include <algorithm>

class IDNotFoundException : std::exception
{
public:
    IDNotFoundException(const std::string id_name):
    m_what(std::string("Object\'") + id_name + "\' not found!")
    {
    }
    
    virtual ~IDNotFoundException() throw()
    {
    }
    
public:
    const char *what() const throw()
    {
        return m_what.c_str();
    }
    
private:
    std::string m_what;
};

class analyzedObject
{
    private:
    std::string id_obj_;
    public:
    analyzedObject(const std::string& id_ = "") : id_obj_(id_){}
    ~analyzedObject(){}
    std::string getId()const
    {
        return id_obj_;
    }
};

bool operator==(const analyzedObject &left, const analyzedObject &right)
{
    return left.getId() == right.getId();
}

long long int hash_function(const std::string& str)
{
    size_t abc = 22;
    long long int hash = 0, p_pow = 1;
    for(size_t i = 0; i < str.length(); ++i)
    {
        hash += (tolower(str[i]) - 'a' + 1) * p_pow;
        p_pow *= abc;
    }
    return hash;
}

template<typename T>
class HashTable
{
    public:
    static const size_t min_hash_value = int('A') + int('0');

    static const size_t max_hash_value = int('z') + int('z');
    
    static const size_t hash_table_size = max_hash_value - min_hash_value;
    
    public:
    HashTable()=default;
    ~HashTable()=default;
    template<typename Func>
    void add(const T&, Func);
    template<typename Func>
    T& get(const std::string&, Func);
    template<typename Func>
    void erase(const std::string&, Func);
        
    private:
    std::list<T> hash_table_[1000000];
    
};

template<typename T>
template<typename Func>
void HashTable<T>::add(const T& obj, Func hash)
{
   hash_table_[hash(obj.getId())].push_back(obj);
}

template<typename T>
template<typename Func>
T& HashTable<T>::get(const std::string& id, Func hash)
{
    std::list<T>& item = hash_table_[hash(id)];
    
  typename std::list<T>::iterator it = std::find_if(item.begin(), item.end(),[id](const T& ob){
        return ob.getId() == id;
    });
                                          
   if(it == item.end()) throw IDNotFoundException(id);
    return *it;
}

template<typename T>
template<typename Func>
void HashTable<T>::erase(const std::string& id, Func hash)
{
   std::list<T>& item = hash_table_[hash(id)];
   item.clear();
}

int main(){
	
}
