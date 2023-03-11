#include <iostream>
using namespace std;

template <class T, class T2>
class AVL_Rec {
    struct node {
        T key;
        T2 value;
        int height;
        node* l;
        node* r;
        node(T k, T2 v) {
            key = k; value = v; height = 0; l = r = nullptr;
        }
    };
    int height(node* h) {
        return (h == nullptr) ? -1:h->height;
    }
    int max(int a, int b) { return (a < b) ? b:a; }
    node* rotL(node* h) {
        node* x = h->r; h->r = x->l; x->l = h;
        h->height = 1 + max(height(h->l), height(h->r));
        x->height = 1 + max(height(x->l), height(x->r));
        return x;
    }
    node* rotR(node* h) {
        node* x = h->l; h->l = x->r; x->r = h;
        h->height = 1 + max(height(h->l), height(h->r));
        x->height = 1 + max(height(x->l), height(x->r));
        return x;
    }
    int balanceFactor(node* h) {
        return height(h->l) - height(h->r);
    }
    node* put(node* h, T key, T2 val) {
        if (h == nullptr)
            return new node(key, val);
        if (key < h->key) h->l = put(h->l, key, val);
        else h->r = put(h->r, key, val);
        h->height = 1 + max(height(h->l), height(h->r));
        if (balanceFactor(h) < -1) {
            if (balanceFactor(h->r) > 0) {
                h->r = rotR(h->r);
            }
            h = rotL(h);
        } else if (balanceFactor(h) > 1) {
            if (balanceFactor(h->l) < 0) {
                h->l = rotL(h->l);
            }
            h = rotR(h);
        }
        return h;
    }
    node* root;
    public:
    AVL_Rec() {
        root = nullptr;
    }
    void insert(T key, T2 val) {
        root = put(root, key, val);
    }
};