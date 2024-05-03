#include <iostream>

class node
{
public:
    enum COLOR
    {
        BLACK,
        RED
    };

    int data;
    COLOR color;
    node *parent;
    node *left;
    node *right;

    node() : color(RED), parent(nullptr), left(nullptr), right(nullptr) {}

    node(const int &data_) : data(data_), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

class rbt
{
public:
    node *root;

    rbt() : root(NULL) {}

    void bstInsert(node *newNode)
    {
        if (root == NULL)
        {
            root = newNode;
            return;
        }

        node *prev = nullptr;
        node *current = root;

        while (current)
        {
            prev = current;
            if (newNode->data > current->data)
            {
                current = current->right;
            }
            else if (newNode->data < current->data)
            {
                current = current->left;
            }
        }

        if (newNode->data > prev->data)
        {
            prev->right = newNode;
        }
        else
        {
            prev->left = newNode;
        }
        newNode->parent = prev;
    }

    node *rotateRight(node *target)
    {
        if(target == root){
            root = target->left;
        }
        node *left = target->left;
        node *right = left->right;
        left->right = target;
        target->left = right;
        target->parent = left;
        if (right != nullptr)
            right->parent = target;
        return right;
    }

    node *rotateLeft(node *target)
    {
        if(target == root){
            root = target->right;
        }
        node *right = target->right;
        node *left = right->left;
        right->left = target;
        target->right = left;
        target->parent = right;
        if (left != nullptr)
            left->parent = target;
        return right;
    }

    void fixConflict(node *current)
    {
        if (current->parent == current->parent->parent->left)
        {
            if (current == current->parent->left)
            {
                // LL
                std::swap(current->parent->color, current->parent->parent->color);
                current->parent->parent = rotateRight(current->parent->parent);
            }
            else
            {
                // LR
                node *grandFather = current->parent->parent;
                current->parent = rotateLeft(current->parent);
                grandFather = rotateRight(grandFather);
                std::swap(current, grandFather);
            }
        }
        else if (current->parent == current->parent->parent->right)
        {
            if (current == current->parent->right)
            {
                // RR
                std::swap(current->parent->color, current->parent->parent->color);
                current->parent->parent = rotateLeft(current->parent->parent);
            }
            else
            {
                // RL
                node *grandFather = current->parent->parent;
                current->parent = rotateRight(current->parent);
                std::swap(current, grandFather);
                grandFather = rotateLeft(grandFather);
            }
        }
    }

    void insertHelper(node *&current)
    {
        
        if (root == current)
        {
            root->color = node::BLACK;
            return;
        }


        if (current->parent->color == node::RED && current != root)
        {
            node *uncle;
            if (current->parent->parent->left == current->parent)
            {
                uncle = current->parent->parent->right;
            }
            else
            {
                uncle = current->parent->parent->left;
            }


            if (uncle == nullptr){ 
                fixConflict(current);
            }
            else if(uncle->color == node::RED){
                current->parent->color = node::BLACK;
                uncle->color = node::BLACK;
                current->parent->parent->color = node::RED;
                insertHelper(current->parent->parent);
            }
            else if(uncle->color == node::BLACK){
                fixConflict(current);
            }
            
        }
    }

    void insert(int value)
    {
        node *newNode = new node(value);

        bstInsert(newNode);
        insertHelper(newNode);
    }

        void printTreeHelper(node* root, int space) {
        if (root != nullptr) {
            space += 10;
            printTreeHelper(root->right, space);
            std::cout << std::endl;
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << root->data << " " << root->color << std::endl;
            printTreeHelper(root->left, space);
        }
    }
    void printTree() {
        printTreeHelper(root, 0);
    }
};

int main()
{

    rbt tree;

    tree.insert(3);
    tree.insert(21);
    tree.insert(32);
    tree.insert(15);

    tree.printTree();

    return 0;
}