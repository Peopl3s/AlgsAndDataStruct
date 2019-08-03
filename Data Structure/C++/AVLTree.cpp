#include <iostream>

template <typename T>
class AvlTree
{
    private:
    struct node;
    node* root;
    
    private:
    int height_(node*) const;
    int balanceFactor_(node*)const;
    void overHeight_(node*);
    node* smallRightRotation_(node*);
    node* smallLeftRotation_(node*);
    node* balance_(node*);
    node* insert_(node*, const T&);
    node* erase_(node*, const T&);
    node* searchMin_(node*);
    node* deleteMin_(node*);
    node* searchItem_(node*, const T&);
    void clear_(node*) const;
    
    
    public:
    AvlTree(node* root_ = nullptr) : root(root_){}
    ~AvlTree(){
if(root != nullptr)
    {
      clear_(root);  
    }
    root = nullptr;
};
    node* insert(const T& k) { root = insert_(root, k); return root;}
    node* erase(const T& k) {  root = erase_(root, k); return root; }
    node* search(const T& k) { return searchItem_(root, k);}
    node* getRoot() const { return root; }
    void inOrderTraversal(node*) const;
    void preOrderTraversal(node*) const;
    void postOrderTraversal(node*) const;

};


    
template<typename T>
struct AvlTree<T>::node
{
    T data;
    int height;
    node* left, *right;
    node(const T& dt = T(), const int& height_ = 1, node* lf = nullptr, node* rht = nullptr):
    data(dt), height(height_), left(lf), right(rht) {};
    ~node()=default;
};

template<typename T>
int AvlTree<T>::height_(node* p) const
{
    if(p != nullptr) return p -> height;
    else return 0;
}

template<typename T>
void AvlTree<T>::clear_(node* nd) const
{
    if(nd != nullptr)
    {
        if(nd -> left != nullptr) clear_(nd -> left);
        if(nd -> right != nullptr) clear_(nd -> right);
        delete nd;
    }
}
    
template<typename T>
int AvlTree<T>::balanceFactor_(node* p) const
{
    return height_(p -> right) - height_(p -> left);
}

template<typename T>
void AvlTree<T>::overHeight_(node* p)
{
   if(p == nullptr) return;
   int heightLeft = height_(p -> left);
   int heightRight = height_(p -> right);
   p -> height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

template<typename T>
typename AvlTree<T>::node*  AvlTree<T>::smallRightRotation_(node* p)
{
    node *tmp = p -> left;
    p -> left = tmp -> right;
    tmp -> right = p;
    overHeight_(p);
    overHeight_(tmp);
    return tmp;
}

template<typename T>
typename AvlTree<T>::node* AvlTree<T>::smallLeftRotation_(node* p)
{
    node* tmp = p -> right;
    p -> right = tmp -> left;
    tmp -> left = p;
    overHeight_(p);
    overHeight_(tmp);
    return tmp;
}

template<typename T>
typename AvlTree<T>::node* AvlTree<T>::balance_(node* p)
{
    overHeight_(p);
    if(balanceFactor_(p) == 2)
    {
        if(balanceFactor_(p -> right) < 0) p -> right = smallRightRotation_(p -> right);
        return smallLeftRotation_(p);
    }
    if(balanceFactor_(p) == -2)
    {
        if(balanceFactor_(p -> left) > 0) p -> left = smallLeftRotation_(p -> left);
        return smallRightRotation_(p);
    }
    return p;
}

template<typename T>
typename AvlTree<T>::node* AvlTree<T>::insert_(node* p, const T& fkey)
{
    if(p == nullptr) return new node(fkey);
    if(fkey < p -> data) p -> left = insert_(p -> left, fkey);
    else p -> right = insert_(p -> right, fkey);
    return balance_(p);
}

template<typename T>
typename AvlTree<T>::node* AvlTree<T>::erase_(node* p, const T& fkey)
{
    if(p == nullptr) return nullptr;
    if(fkey < p -> data) p -> left = erase_(p -> left, fkey);
    else if(fkey > p -> data) p -> right = erase_(p -> right, fkey);
    else
    {
        node* l = p -> left;
        node* r = p -> right;
        delete p;
        if(r == nullptr) return l;
        node* min = searchMin_(r);
        min -> right = deleteMin_(r);
        min -> left = l;
        return balance_(min);
    }
    return balance_(p);
}

template<typename T>
typename AvlTree<T>::node* AvlTree<T>::searchMin_(node* p)
{
   return p -> left != nullptr ? searchMin_(p -> left) : p;
}

template<typename T>
typename AvlTree<T>::node* AvlTree<T>::deleteMin_(node* p)
{
   if(p -> left == nullptr) return p -> left;
    p -> left = deleteMin_(p -> left);
    balance_(p);
}

template<typename T>
typename AvlTree<T>::node* AvlTree<T>::searchItem_(node* p, const T& k)
{
   if(p == nullptr) return nullptr;
    if(k < p -> data)
    {
        if(p -> left != nullptr) return searchItem_(p -> left, k);
        else throw std::string("No el");
    } else if(k > p -> data)
    {
         if(p -> right != nullptr) return searchItem_(p -> right, k);
        else throw std::string("No el");
    } else
    {
        return p;
    }
}

template<typename T>
  void AvlTree<T>::inOrderTraversal(node* p) const
    {
        if(p != nullptr)
        {
            inOrderTraversal(p -> left);
            std::cout<<p -> data<<" ";
            inOrderTraversal(p -> right);
        }
    }

template<typename T>
  void AvlTree<T>::preOrderTraversal(node* p) const
    {
        if(p != nullptr)
        {
            std::cout<<p -> data<<" ";
            inOrderTraversal(p -> left);
            inOrderTraversal(p -> right);
        }
    }

template<typename T>
  void AvlTree<T>::postOrderTraversal(node* p) const
    {
        if(p != nullptr)
        {
            inOrderTraversal(p -> left);
            inOrderTraversal(p -> right);
            std::cout<<p -> data<<" ";
    }
  }

int main()
{

}
