#include<iostream> 
using namespace std;

class AVLTree {
private:
    class Node {
    public:
        int key;
        Node* left;
        Node* right;
        int height;
    };

    Node* root;

    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* newNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* add(Node* node, int key) {
        if (node == nullptr)
            return(newNode(key));

        if (key < node->key)
            node->left = add(node->left, key);
        else if (key > node->key)
            node->right = add(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current && current->left != nullptr)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    bool search(Node* root, int key) {
        if (root == nullptr)
            return false;
        if (root->key == key)
            return true;
        if (key < root->key)
            return search(root->left, key);
        else
            return search(root->right, key);
    }

    void printElem(Node* root, int space) {
        if (root == nullptr)
            return;
        space += 5;
        printElem(root->right, space);
        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << root->key << "\n";
        printElem(root->left, space);
    }

public:
    AVLTree() : root(nullptr) {}

    void add(int key) {
        root = add(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    bool contains(int key) {
        return search(root, key);
    }

    void print() {
        printElem(root, 0);
    }
};




int main() {
    AVLTree avlTree;

    avlTree.add(30);
    avlTree.add(10);
    avlTree.add(50);
    avlTree.add(60);
    avlTree.add(20);
    avlTree.add(25);
    avlTree.add(70);
    avlTree.add(51);

    cout << "AVL tree: \n";
    avlTree.print();



    int searchKey = 50;
    cout << "\nIs " << searchKey << " in AVL tree? " << (avlTree.contains(searchKey) ? "Yes" : "No") << endl;

    return 0;
}
