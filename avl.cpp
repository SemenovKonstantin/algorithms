#include <algorithm>
#include <iostream>

template <typename T>
struct AVLNode {
    public:
    // Data field represents an information which will store inside of AVL tree
    T data;
    // Pointers type AVLNode represent left and right child of the current node
    AVLNode* left;
    AVLNode* right;
    // Height is sufficient option to handle whether tree is self-balanced or not.
    int height;
    AVLNode(T data_) : data(data_), left(nullptr),right(nullptr),height(0) {}   
};

template <typename T>
struct AVLTree
{
    private:
    AVLNode<T> *root;

    int height(AVLNode<T>* node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(AVLNode<T>* node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // Always rotate the first node in the subtree which invokes imbalance.

    // Function to perform a right rotation on a subtree.
    AVLNode<T>* rightRotation(AVLNode<T>* node_x)
    {
        // Preparations to rotate operation.
        AVLNode<T>* node_y = node_x->left;
        AVLNode<T>* possibleSubTree = node_y->right;

        // Perform rotations.
        node_y->right = node_x;
        node_x->left = possibleSubTree;

        // After making rotations need to update height of each changed node, they can either change height or not, better to update.
        node_x->height = std::max(height(node_x->left),height(node_x->right)) + 1;      
        node_y->height = std::max(height(node_y->left),height(node_y->right)) + 1;

        // Return new root
        return node_y;
    }


    // Function to perform a left rotation on a subtree
    AVLNode<T>* leftRotation(AVLNode<T>* node_x)
    {
        AVLNode<T>* node_y = node_x->right;         
        AVLNode<T>* possibleSubTree = node_y->left;

        node_y->left = node_x;
        node_x->right = possibleSubTree;

        node_x->height = std::max(height(node_x->left),height(node_x->right)) + 1;      
        node_y->height = std::max(height(node_y->left),height(node_y->right)) + 1;
    
        // Return new root
        return node_y;
    }
    
    // Function to insert a data into subtree rooted with a node
    AVLNode<T>* insert(AVLNode<T>* node, T data)
    {
        // Compare is data less or greater than node. Recursively from a root to correspond node.
        if (node == nullptr)
            return new AVLNode<T>(data);
        
        if (data < node->data)
            node->left = insert(node->left,data);
        else if (data > node->data)
            node->right = insert(node->right,data);
        else
            return node;

        // Update the height of ancestor node.
        node->height = std::max(height(node->left),height(node->right)) + 1;

        // Check if there is an imbalance after inserting a new element.
        // If imbalance of this node not equals to | balance <= 1 |, we'll handle this situation 4 different ways.
        int balanceFactorVariable = balanceFactor(node);

        // Left Left Case. Right Rotation. Imbalance equals to 2.
        //       20
        //      /
        //    10       =>      10
        //   /                /  \
        //  5                5   20
        if (balanceFactorVariable > 1 && data < node->left->data)
            return rightRotation(node);

        // Left Right Case: Left-Right Rotation. Imbalance equals to 2.
        //       20             20             
        //      /              /
        //    10       =>    15      =>     15
        //      \           /              /   \
        //       15       10              10    20
        else if (balanceFactorVariable > 1 && data > node->left->data)
        {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right Right Case. Left Rotation. Imbalance equals to 2.
        //       20
        //         \
        //          30     =>      30
        //            \          /    \
        //             45       20     45
        else if (balanceFactorVariable < -1 && data > node->right->data)
            return leftRotation(node);
        // Right Left Case: Right-Left Rotation. Imbalance equals to 2.
        //       20             20             
        //         \              \
        //         30    =>       25      =>     25
        //        /                 \           /   \
        //      25                  30         20    30
        else if (balanceFactorVariable < -1 && data < node->right->data)
        {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;

    }

    // Function to get the minimal node in the AVL tree.
    AVLNode<T>* minElement(AVLNode<T>* node)
    {
        AVLNode<T>* current = node;
        while(current->left != nullptr)
            minElement(current);
        return current;
    }

    // Function to delete a node from a subtree with root node
    AVLNode<T>* deleteNode(AVLNode<T>* root, T data)
    {
        if (root == nullptr)
            return 0;

        if (data < root->data)
            root->left = deleteNode(root->left,data);
        else if (data > root->data)
            root->right = deleteNode(root->right,data);
        else
        {
            // There are 2 options. One option the node we want to delete has n-count of successors, never mind right or left.
            // The result will be the same. In this situation we should change our node with node-successor, 
            // After oblige to delete the node in order of redundancy elimination. 

            if(root->left == nullptr || root->right == nullptr)
            {
                AVLNode<T>* temporary = root->left ? root->left : root->right;
                if (temporary == nullptr) {
                    temporary = root;
                    root = nullptr;
                }
                else {
                    *root = *temporary;
                }

                delete temporary;
            }
            else 
            {
                AVLNode<T>* temp = minElement(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right,temp->data); // To get rid of redundancy of min element in the right subtree aka min successor.
            }
        }

        if (root == nullptr)
            return root;

        // Update height of the current node
        root->height = 1 + std::max(height(root->left),height(root->right));

        // Get the balance factor of this node
        int balance = balanceFactor(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotation(root);

        // Left Right Case
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }

        // Right Right Case
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotation(root);

        // Right Left Case
        if (balance < -1
            && balanceFactor(root->right) > 0) {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }
    //                                                   STACK - LIFO
    //               20                                 |           |
    //            /     \                               |           |
    //          10       30                             |     5     |   
    //         /  \     /   \                           |    10     |       => 5 10 18 20
    //        5   18  25    40                          |    20     |
   void inorder(AVLNode<T>* node)
    {
        if (node != nullptr)
        {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

    bool search(AVLNode<T>* root, T data)
    {
        if (root == nullptr)
            return 0;
        if (root->data == data)
            return true;
        else if (data < root->data)
            return search(root->left,data);
        else 
            return search(root->right,data);
    }

    public:
    AVLTree() : root(nullptr) {}

    // Function to insert a data into the AVL tree
    void insertInto(T data) { root = insert(root, data); }

    // Function to remove a data from the AVL tree
    void remove(T data) { root = deleteNode(root, data); }

    // Function to search for a data in the AVL tree
    bool searchIn(T data) { return search(root, data); }

    // Function to print the inorder traversal of the AVL tree
    void printInorder()
    {
        inorder(root);
        std::cout << std::endl;
    }
};

int main()
{
    AVLTree<int> avl;

    // Insert nodes into the AVL tree
    avl.insertInto(10);
    avl.insertInto(20);
    avl.insertInto(30);
    avl.insertInto(40);
    avl.insertInto(50);
    avl.insertInto(25);

    // Print the inorder traversal of the AVL tree
    std::cout << "Inorder traversal of the AVL tree: ";
    avl.printInorder();

    // Remove a node from the AVL tree
    avl.remove(30);
    std::cout << "Inorder traversal after removing 30: ";
    avl.printInorder();

    // Search for nodes in the AVL tree
    std::cout << "Is 25 in the tree? "
         << (avl.searchIn(25) ? "Yes" : "No") << std::endl;
    std::cout << "Is 30 in the tree? "
         << (avl.searchIn(30) ? "Yes" : "No") << std::endl;

    return 0;
}