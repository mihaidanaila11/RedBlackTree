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

private:    

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

    node* minNode(node* target){
        node *current = target;

        while(current->left != nullptr){
            current = current->left;
        }

        return current;
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

    node* getUncle(node* target){
        if(target->parent == target->parent->parent->left)
            return target->parent->parent->right;

        return target->parent->parent->left;
    }

    void fixConflict(node *current)
    {
        if(!(current->color == node::RED && current->parent->color == node::RED))
            return;

        
        node *parent = current->parent;
        node *grandfather = current->parent->parent;

        if (parent == grandfather->left)
        {
            if (current == parent->left)
            {
                // LL
                std::cout << "LL-\n";
                std::swap(grandfather->color, parent->color);
                grandfather = rotateRight(grandfather);
            } else{
                // LR
                std::cout << "LR-\n";
                parent = rotateLeft(parent);
                fixConflict(parent);
            }
       }
       else{
        if(current == parent->right){
            // RR
            std::cout << "RR-\n";
            std::swap(grandfather->color, parent->color);
            grandfather = rotateLeft(grandfather);
            
        } else{
            // RL
            std::cout << "RL-\n";
            parent = rotateRight(parent);
            fixConflict(parent);
        }
       }
    }

    void insertHelper(node *&current)
    {
        if(current == root){
            current->color = node::BLACK;
            return;
        }

        if(current->parent->color == node::RED && current != root){
            
            node *uncle = getUncle(current);

            if(uncle != nullptr && uncle->color == node::RED){
                
                current->parent->color = node::BLACK;
                uncle->color = node::BLACK;
                current->parent->parent->color = node::RED;

                insertHelper(current->parent->parent);
                return;
            }
            else{
                
                fixConflict(current);
            }
        }
    }

public:
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