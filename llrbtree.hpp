#include <iostream>
using namespace std;

const bool red = true;
const bool black = false;

template <class T, class T2>
class LLRBTree {
    private:
        struct node {
            T key;
            T2 value;
            bool color;
            node* left;
            node* right;
            node* parent;
            node(T k, T2 v) {
                key = k; value = v; color = red; left = right = parent = nullptr;
            }
        };
        node* root;
        bool isRed(node* h) { return (h == nullptr) ? false:(h->color == red); }

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
            y->color = x->color;
            x->color = red;
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
            y->color = x->color;
            x->color = red;
        }
        void visit(node* x) {
            if (x) {
                cout<<x->key<<" ";
                visit(x->left);
                visit(x->right);
            }
        }
        void balance(node* x) {
            while (x != nullptr) {
                node *y = x;
                if (isRed(y->right) && !isRed(y->left)) left_rotate(y);
                if (isRed(y->left) && isRed(y->left->left)) right_rotate(y);
                if (isRed(y->right) && isRed(y->left)) {
                    y->color = red;
                    y->left->color = black;
                    y->right->color = black;
                }
                x = x->parent;
            }
        }
    public:
        LLRBTree() {
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
            root->color = black;
        }
        void show() {
            visit(root);
            cout<<endl;
        }
        bool contains(T key) {
            node* x = root;
            while (x != nullptr) {
                if (key == x->key)
                    return true;
                x = (key < x->key) ? x->left:x->right;
            }
            return false;
        }
};