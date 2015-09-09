#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cassert>
using namespace std;

#define RED true
#define BLACK false

int max(int a, int b)
{
    if (a > b) return a;
    return b;
}

int min(int a, int b)
{
    if (a > b) return b;
    return a;
}

struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    bool color;
    TreeNode(int value, bool color)
    {
        this->value = value;
        this->color = color;
        this->left = NULL;
        this->right = NULL;
    }
};

class RedBlackTree
{
    private:
        TreeNode *root;
    public:
        RedBlackTree()
        {
            root = NULL;
        }
        bool isRed(TreeNode *node)
        {
            if (node == NULL) return false;
            return node->color == RED;
        }
        TreeNode * rotateLeft(TreeNode *h)
        {
            TreeNode * x = h->right;
            assert(x->color == RED);
            h->right = x->left;
            x->color = h->color;
            h->color = RED;
            x->left = h;
            return x;
        }
        TreeNode * rotateRight(TreeNode *h)
        {
            TreeNode * x = h->left;
            assert(x->color == RED);
            h->left = x->right;
            x->color = h->color;
            h->color = RED;
            x->right = h;
            return x;
        }
        void flipColor(TreeNode *h)
        {
            assert(h->left->color == RED);
            assert(h->right->color = RED);
            h->left->color = BLACK;
            h->right->color = BLACK;
            h->color = RED;
        }
        TreeNode * insert(TreeNode *node, int value)
        {
            if (node == NULL)
            {
                node = new TreeNode(value, RED);
                return node;
            }
            if (value < node->value) node->left = insert(node->left, value);
            else if (value > node->value) node->right = insert(node->right, value);
            else node->value = value;

            if (isRed(node->right) && !isRed(node->left)) node = rotateLeft(node);
            if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node);
            if (isRed(node->left) && isRed(node->right)) flipColor(node);

            return node;
        }
        void insert(int value)
        {
            this->root = this->insert(this->root, value);
        }
        void printTree(TreeNode *node)
        {
            if (node == NULL)
            {
                return;
            }
            else
            {
                printTree(node->left);
                cout << node->value << endl;
                printTree(node->right);
            }
        }
        void printTree()
        {
            this->printTree(this->root);
        }
        int getHeight(TreeNode *node)
        {
            if (node == NULL) return 0;
            return 1 + max(getHeight(node->left), getHeight(node->right));
        }
        int getHeight()
        {
            return getHeight(root);
        }
};

int main()
{
    RedBlackTree rbt;
    for (int i = 0; i < 1000; ++i)
    {
        rbt.insert(i);
    }
    cout << "Height of the tree is " << rbt.getHeight() << endl;
    return 0;
}
