#include <iostream>
using namespace std;

template <class T, class T2>
class AVLTree {
    private:
        struct node {
            T key;
            T2 value;
            int height;
            node* left;
            node* right;
            node* parent;
            node(T k, T2 v) {
                key = k; value = v; height = 0; left = right = parent = nullptr;
            }
        };
        node* root;
        int height(node* h) {
            return (h == nullptr) ? -1:h->height;
        }
        int max(int a, int b) { return (a < b) ? b:a; }
        void left_rotate(node *x) {
            node *y = x->right;
            if (y) {
                x->right = y->left;
                if (y->left) y->left->parent = x;
                y->parent = x->parent;
            }
            if (!x->parent) root = y;
            else if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
            if (y) y->left = x;
            x->parent = y;
            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));
        }
  
        void right_rotate(node *x) {
            node *y = x->left;
            if (y) {
                x->left = y->right;
                if (y->right) y->right->parent = x;
                y->parent = x->parent;
            }
            if (!x->parent) root = y;
            else if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
            if (y) y->right = x;
            x->parent = y;
            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));
        } 
        int balanceFactor(node* h) {
            return height(h->left) - height(h->right);
        }
        void balance(node* x) {
            while (x && x->parent) {
                node *y = x->parent;
                y->height = 1 + max(height(y->left), height(y->right));
                if (balanceFactor(y) < -1) {
                    if (balanceFactor(y->right) > 0) {
                        right_rotate(y->right);
                    }
                    left_rotate(y);
                } else if (balanceFactor(y) > 1) {
                    if (balanceFactor(y->left) < 0) {
                        left_rotate(y->left);
                    }
                    right_rotate(y);
                }
                x = x->parent;
            }
        }
        void visit(node* h) {
            if (h != nullptr) {
                cout<<h->key<<" ";
                visit(h->left);
                visit(h->right);
            }
        } 
    public:
        AVLTree() {
            root = nullptr;
        }
        void insert(T key, T2 value) {
            node* x = root;
            node* p = x;
            while (x) {
                p = x;
                x = (key < x->key) ? x->left:x->right;
            }
            x = new node(key, value);
            if (!p) root = x;
            else if (key < p->key) p->left = x;
            else p->right = x;
            x->parent = p;
            balance(x);
        }
        void show() {
            visit(root);
            cout<<endl;
        }
};