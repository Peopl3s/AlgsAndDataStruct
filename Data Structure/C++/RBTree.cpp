#include <iostream>

typedef enum nodeColor { BLACK, RED } nodeColor;

template <typename K, typename V>
class rbTree
{
private:
    struct Node;
    Node* NIL = &emptyNode;
    Node emptyNode = {NIL, NIL,nullptr, BLACK, K(), V()};
    Node* root;

    void clear_(Node* nd)
    {
        if(nd != NIL)
        {
            if(nd -> left != NIL) clear_(nd -> left);
            if(nd -> right != NIL) clear_(nd -> right);
            delete nd;
        }

    }

    void copy_(Node* thisRoot, Node* sourceRoot)
    {
       if(sourceRoot == NIL) thisRoot = NIL;
       else
       {
           thisRoot = new Node;
           thisRoot->key = sourceRoot->key;
           thisRoot->value = sourceRoot->value;
           copy_(thisRoot->left, sourceRoot->left);
           copy_(thisRoot->right, sourceRoot->right);
       }
    }
public:

    rbTree(): root(NIL)
    {
    }
    rbTree(const rbTree& rhs)
    {
        if(rhs.root == NIL) root = NIL;
        else copy_(this->root, rhs.root);
    }

    ~rbTree()
    {
        if(root != NIL)
        {
            clear_(root);
        }
        root = nullptr;
    }

    void rotateLeft(Node*);
    void rotateRight(Node*);

    void insertFixup(Node*);
    Node* insertNode(const K&, const V&);

    void deleteFixup(Node*);
    void deleteNode(Node*);
    void deleteByKey(const K&);

    Node* findNode(const K&);
    Node* getRoot() const { return root; }

    void inOrderTraversal(Node*);
    void preOrderTraversal(Node*);
    void postOrderTraversal(Node*);

};

template<typename K, typename V>
void rbTree<K, V>::rotateLeft(Node *x)
{
    Node *y = x -> right;

    x -> right = y -> left;
    if (y -> left != NIL) y -> left -> parent = x;

    if (y != NIL) y -> parent = x -> parent;
    if (x -> parent)
    {
        if (x == x -> parent -> left)
            x -> parent -> left = y;
        else
            x -> parent -> right = y;
    } else
    {
        root = y;
    }

    y -> left = x;
    if (x != NIL) x -> parent = y;
}
template<typename K, typename V>
void rbTree<K, V>::rotateRight(Node *x)
{
    Node *y = x -> left;

    x -> left = y -> right;
    if (y -> right != NIL) y -> right -> parent = x;

    if (y != NIL) y -> parent = x -> parent;
    if (x -> parent)
    {
        if (x == x -> parent -> right)
            x -> parent -> right = y;
        else
            x -> parent -> left = y;
    } else
    {
        root = y;
    }

    y -> right = x;
    if (x != NIL) x -> parent = y;
}

template<typename K, typename V>
void rbTree<K, V>::insertFixup(Node *x)
{
    while (x != root && x -> parent -> color == RED)
    {
        if (x -> parent == x -> parent -> parent -> left)
        {
            Node *y = x -> parent -> parent -> right;
            if (y -> color == RED)
            {
                x -> parent -> color = BLACK;
                y -> color = BLACK;
                x -> parent -> parent -> color = RED;
                x = x-> parent -> parent;
            } else
            {
                if (x == x -> parent -> right)
                {
                    x = x -> parent;
                    rotateLeft(x);
                }
                x -> parent -> color = BLACK;
                x -> parent -> parent -> color = RED;
                rotateRight(x -> parent -> parent);
            }
        } else
        {
            Node *y = x -> parent -> parent -> left;
            if (y -> color == RED)
            {
                x -> parent -> color = BLACK;
                y -> color = BLACK;
                x -> parent -> parent -> color = RED;
                x = x -> parent -> parent;
            } else
            {
                if (x == x -> parent -> left)
                {
                    x = x -> parent;
                    rotateRight(x);
                }
                x -> parent -> color = BLACK;
                x -> parent -> parent -> color = RED;
                rotateLeft(x -> parent -> parent);
            }
        }
    }
    root -> color = BLACK;
}

template<typename K, typename V>
typename rbTree<K, V>::Node* rbTree<K, V>::insertNode(const K& data, const V &v)
{
    Node *current, *parent, *x;
    current = root;
    parent = 0;
    while (current != NIL)
    {
        if (data == current -> key) return current;
        parent = current;
        current = (data < current -> key) ?
                    current -> left : current -> right;
    }

    x = new(std::nothrow) Node(NIL, NIL, parent, RED, data, v);

    if(x == nullptr) throw std::string("Bad alloc");

    if(parent)
    {
        if(data < parent -> key)
            parent -> left = x;
        else
            parent -> right = x;
    } else
    {
        root = x;
    }
    insertFixup(x);
    return x;
}

template<typename K, typename V>
void rbTree<K, V>::deleteFixup(Node *x)
{
    while (x != root && x -> color == BLACK)
    {
        if (x == x -> parent -> left)
        {
            Node *w = x -> parent -> right;
            if (w -> color == RED)
            {
                w -> color = BLACK;
                x -> parent -> color = RED;
                rotateLeft (x -> parent);
                w = x -> parent -> right;
            }
            if (w -> left -> color == BLACK && w -> right -> color == BLACK)
            {
                w -> color = RED;
                x = x -> parent;
            } else
            {
                if (w -> right -> color == BLACK)
                {
                    w -> left -> color = BLACK;
                    w -> color = RED;
                    rotateRight (w);
                    w = x -> parent -> right;
                }
                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                w -> right -> color = BLACK;
                rotateLeft (x -> parent);
                x = root;
            }
        } else
        {
            Node *w = x -> parent -> left;
            if (w -> color == RED)
            {
                w -> color = BLACK;
                x -> parent -> color = RED;
                rotateRight (x -> parent);
                w = x -> parent -> left;
            }
            if (w -> right -> color == BLACK && w -> left -> color == BLACK)
            {
                w -> color = RED;
                x = x -> parent;
            } else
            {
                if (w -> left -> color == BLACK)
                {
                    w -> right -> color = BLACK;
                    w -> color = RED;
                    rotateLeft (w);
                    w = x -> parent -> left;
                }
                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                w -> left -> color = BLACK;
                rotateRight (x -> parent);
                x = root;
            }
        }
    }
    x -> color = BLACK;
}

template<typename K, typename V>
void rbTree<K, V>::deleteNode(Node *z)
{
    Node *x, *y;
    if (!z || z == NIL) return;

    if (z -> left == NIL || z -> right == NIL)
    {
        y = z;
    } else
    {
        y = z -> right;
        while (y -> left != NIL) y = y -> left;
    }

    if (y -> left != NIL)
        x = y -> left;
    else
        x = y -> right;

    x -> parent = y -> parent;
    if (y -> parent)
        if (y == y -> parent -> left)
            y -> parent -> left = x;
        else
            y -> parent -> right = x;
    else
        root = x;

    if (y != z)
    {
        z -> key = y -> key;
        z -> value = y -> value;
    }


    if (y -> color == BLACK)
        deleteFixup (x);

    delete y;
}

template<typename K, typename V>
typename rbTree<K, V>::Node* rbTree<K, V>::findNode(const K& data)
{
    Node *current = root;
    while(current != NIL)
        if(data == current -> key)
            return current;
        else
            current = (data < current -> key) ?
                        current -> left : current -> right;
    return(0);
}

template<typename K, typename V>
void rbTree<K, V>::deleteByKey(const K& data)
{
    deleteNode(findNode(data));
}

template <typename K, typename V>
void rbTree<K, V>::inOrderTraversal(Node*p)
{
    if(p != NIL)
    {
        inOrderTraversal(p -> left);
        std::cout<<p -> key <<"     "<< p-> value<<" ";
        inOrderTraversal(p -> right);
    }
}

template <typename K, typename V>
void rbTree<K, V>::preOrderTraversal(Node*p)
{
    if(p != NIL)
    {
        std::cout<<p -> key <<"     "<< p-> value<<" ";
        inOrderTraversal(p -> left);
        inOrderTraversal(p -> right);
    }
}

template <typename K, typename V>
void rbTree<K, V>::postOrderTraversal(Node*p)
{
    if(p != NIL)
    {
        inOrderTraversal(p -> left);
        inOrderTraversal(p -> right);
        std::cout<<p -> key <<"     "<< p-> value<<" ";
    }
}

template <typename K, typename V>
struct rbTree<K, V>::Node
{
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    nodeColor color;
    K key;
    V value;
    Node(){}
    Node(Node* lf, Node* rt, Node* pt, nodeColor cl, const K& k, const V& v):
        left(lf), right(rt), parent(pt), color(cl), key(k), value(v){}
    ~Node()
    {
        delete left;
        delete right;
        delete parent;
    }
};

int main()
{
}
