#include <iostream>
template <typename K, typename V>
class binarySearchTree
{
    private:
    struct node;
    void clear_(node*);
    node* root;
    size_t count;
    public:
    binarySearchTree( node* root_ = nullptr, const size_t& cnt = 0) : root(root_), count(cnt){}
    ~binarySearchTree();
    binarySearchTree(const binarySearchTree&);
    binarySearchTree& operator=(const binarySearchTree&);
    node* insert(const K&, const V&);
    void remove(const K&);
    V search(const K&);
    void inOrderTraversal(node*);
    void preOrderTraversal(node*);
    void postOrderTraversal(node*);
    node* getRoot();
    V getMax(node*) const;
    V getMin(node*) const;
};

template <typename K, typename V>
struct binarySearchTree<K, V>::node
{
    K key;
    V value;
    node* left, *right, *parent;
    binarySearchTree* host;
    node(const K& key_ = K(), const V& value_ = V(), node* left_ = nullptr, node* right_ = nullptr, node* parent_ = nullptr, binarySearchTree* bts = nullptr) :
    key(key_), value(value_), left(left_), right(right_), parent(parent_), host(bts){}
    ~node(){}
    node* insert_(const K&, const V&);
    void remove_(const K&);
    V search_(const K&);
    
};  

template <typename K, typename V>
typename  binarySearchTree<K, V>::node* binarySearchTree<K, V>::node::insert_(const K& nkey, const V& nval)
{
    if(nkey > key) 
    {
        if(right != nullptr) right -> insert_(nkey, nval);
        else return right = new node(nkey, nval, nullptr, nullptr, this, host);
    } else if(nkey < key)
    {
        if(left != nullptr) left -> insert_(nkey, nval);
        else return left = new node(nkey, nval, nullptr, nullptr, this, host);
    } else
    {
        key = nkey;
        value = nval;
        return this;
    }
    
}

template <typename K, typename V>
void binarySearchTree<K, V>::node::remove_(const K& nkey)
{
    if(nkey > key)
    {
        if(right != nullptr) right -> remove_(nkey);
        else throw std::string("No element");
    } else if(nkey < key)
    {
        if(left != nullptr) left -> remove_(nkey);
        else throw std::string("No element");
    } else
    {
        if(left == nullptr && right == nullptr)
        {
            if(parent == nullptr)
            {
                host -> root = nullptr;
            } else if(parent -> left && parent -> left -> key == nkey)
            {
                parent -> left = nullptr;
            } else if(parent -> right && parent -> right -> key == nkey)
            {
                parent -> right = nullptr;
            }       
        } else if(left != nullptr && right == nullptr)
        {
            if(parent == nullptr)
            {
                host -> root = left;
            } else if(parent -> left && parent -> left -> key == nkey)
            {
                parent -> left = left;
            } else if(parent -> right && parent -> right -> key == nkey)
            {
                parent -> right = left;
            }
            left -> parent = parent;
        } else if(left == nullptr && right != nullptr)
        {
            if(parent == nullptr)
            {
                host -> root = right;
            } else if(parent -> left && parent -> left -> key == nkey)
            {
                parent -> left = right;
            } else if(parent -> right && parent -> right -> key == nkey)
            {
                parent -> right = right;
            }
            right -> parent = parent;
        } else
        {
            if(right -> left == nullptr)
            {
                right -> parent = parent;
                right -> left = left;
                left -> parent = right;
                
                if(parent == nullptr) host -> root = right;
            } else 
            {
                node* lastLeft = right;
                while(lastLeft -> left)
                {
                    lastLeft = lastLeft -> left;
                }
                lastLeft -> parent -> left = nullptr;
                
                lastLeft -> left = left;
                lastLeft -> right = right;
                lastLeft -> parent = parent;
                
                if(parent == nullptr) host -> root = lastLeft;
            }
        }
        delete this;
    }
    
}

template <typename K, typename V>
V binarySearchTree<K, V>::node::search_(const K& nkey)
{
    if(nkey > key)
    {
        if (right != nullptr) return right -> search_(nkey);
        else throw std::string("No element");
    } else if(nkey < key)
    {
        if (left != nullptr) return left -> search_(nkey);
        else throw std::string("No element");
    } else
    {
        return value;
    }
}

template <typename K, typename V>
binarySearchTree<K, V>::~binarySearchTree()
{
    if(root != nullptr)
    {
      clear_(root);  
    }
    root = nullptr;
    count = 0;
}

template <typename K, typename V>
void binarySearchTree<K, V>::clear_(node* nd)
{
    if(nd != nullptr)
    {
        if(nd -> left != nullptr) clear_(nd -> left);
        if(nd -> right != nullptr) clear_(nd -> right);
        delete nd;
    }
}

template <typename K, typename V>
typename binarySearchTree<K, V>::node* binarySearchTree<K, V>::insert(const K& nkey, const V& nval)
{
    if(root == nullptr)
    {
        root = new node(nkey, nval, nullptr, nullptr, nullptr, this);
        return root;
    }
    return root -> insert_(nkey, nval);
}

template <typename K, typename V>
void binarySearchTree<K, V>::remove(const K& nkey)
{
    if(root == nullptr)
    {
        return;
    }
    root -> remove_(nkey);
}

template <typename K, typename V>
V binarySearchTree<K, V>::search(const K& nkey)
{
    if(root == nullptr)
    {
        throw std::string("No element");
    }
    return root -> search_(nkey);
}


template <typename K, typename V>
void binarySearchTree<K, V>::inOrderTraversal(binarySearchTree<K, V>::node* nd)
{
    if (nd != nullptr)
    {
        inOrderTraversal(nd -> left);
         std::cout<<nd -> value<<" ";
        inOrderTraversal(nd -> right);
    }
    std::cout<<std::endl;
}

template <typename K, typename V>
void binarySearchTree<K, V>::preOrderTraversal(binarySearchTree<K, V>::node* nd)
{
    
    if (nd != nullptr)
    {
        std::cout<<nd -> value<<" ";
        inOrderTraversal(nd -> left);
        inOrderTraversal(nd -> right);
    }
    std::cout<<std::endl;
}

template <typename K, typename V>
void binarySearchTree<K, V>::postOrderTraversal(node* nd)
{
      if (nd != nullptr)
    {
          
        inOrderTraversal(nd -> left);
        inOrderTraversal(nd -> right);
        std::cout<<nd -> value<<" ";
    }
    std::cout<<std::endl;
}

template <typename K, typename V>
typename binarySearchTree<K, V>::node* binarySearchTree<K, V>::getRoot()
{
   return root;
}
   

template <typename K, typename V>
V binarySearchTree<K, V>::getMin(node *nd) const
{
    if (nd -> left == nullptr)
    {
        return nd -> value;
    }
    return getMin(nd -> left);
}

template <typename K, typename V>
V binarySearchTree<K, V>::getMax(node *nd) const
{
    if (nd -> right == nullptr)
    {
        return nd -> value;
    }
    return getMax(nd -> right);
}

int main()
{
}
