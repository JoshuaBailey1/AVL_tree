//Original BST from Harish R
//Joshua Bailey With Brant Miranda
#include<iostream>
#include<fstream>
using namespace std;

class BST 
{
private:
    struct node 
    {
        int data;
        int height;
        node* left;
        node* right;
    };

    node* insert(int value, node* root)
    {
        const int threshold = 1;

        if(root == NULL)
        {
            root = new node;
            root->data = value;
            root->left = root->right = NULL;
        }
        else if(value < root->data)
        {
            root->left = insert(value, root->left);
        }
        else if(value > root->data)
        {
            root->right = insert(value, root->right);
        }

        root->height = 1+max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);
        if (balance > threshold)
        {
            if (getBalance(root->left) >= 0)
            {
                root = rotateRight(root);
            }
            else
            {
                root = rotateLeftRight(root);
            }
        }
        else if (balance < -threshold)
        {
            if (getBalance(root->right) <= 0)
            {
                root = rotateLeft(root);
            }
            else
            {
                root = rotateRightLeft(root);
            }
        }
        return root;
    }

    node* rotateLeft(node* root)
    {
        node* rightTemp = root->right;
        root->right = rightTemp->left;
        rightTemp->left = root;
        root->height = 1+max(getHeight(root->left), getHeight(root->right));
        rightTemp->height = 1+max(getHeight(rightTemp->left),getHeight(rightTemp->right));
        return rightTemp;
    }

    node* rotateRight(node* root)
    {
        node* leftTemp = root->left;
        root->left = leftTemp->right;
        leftTemp->right = root;
        root->height = 1+max(getHeight(root->left), getHeight(root->right));
        leftTemp->height = 1+max(getHeight(leftTemp->left),getHeight(leftTemp->right));
        return leftTemp;
    }

    node* rotateLeftRight(node* root)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    node* rotateRightLeft(node* root)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    void inorder(node* root) 
    {
        if(root == NULL)
        {
            return;
        }
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void preorder(node* root) 
    {
        if(root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(node* root) 
    {
        if(root == NULL)
        {
            return;
        }
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

public:
    BST() 
    {
        root = NULL;
    }

    node* root;

    void insert(int value) 
    {
        root = insert(value, root);
    }

    int getHeight(node* root)
    {
        if (root == NULL)
        {
            return -1;
        }

        return root->height;
    }

    int getBalance(node* root) 
    {
        if (root == NULL)
        {
            return 0;
        }

        return getHeight(root->left) - getHeight(root->right);
    }

    void displayInOrder() 
    {
        inorder(root);
        cout << endl;
    }

    void displayPreOrder()
    {
        preorder(root);
        cout << endl;
    }

    void displayPostOrder()
    {
        postorder(root);
        cout << endl;
    }
};

void displayAllTraversals(BST Tree)
{
    cout << "InOrder = ";
    Tree.displayInOrder();
    cout << "PreOrder = ";
    Tree.displayPreOrder();
    cout << "PostOrder = ";
    Tree.displayPostOrder();
}

int main()
{
    BST Tree;
    int value;
    ifstream inFile;

    inFile.open("input.txt");
    do
    {
        inFile >> value;
        Tree.insert(value);
    }
    while(!inFile.eof());

    displayAllTraversals(Tree);

    inFile.close();
    return 0; 
}