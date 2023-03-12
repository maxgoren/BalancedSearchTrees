#include <iostream>
using namespace std;

template <class T, class T2>
class LLRB_Rec {
    struct node {
        T key;
        T2 value;
        bool color;
        node* l;
        node* r;
        node(T k, T2 v) {
            key = k; value = v; color = true; l = r = nullptr;
        }
    };
    bool isRed(node* h) { return (h == nullptr) ? false:(h->color == true); }
    node* rotL(node* h) {
        node* x = h->r; h->r = x->l; x->l = h;
        x->color = h->color;
        h->color = true;
        return x;
    }
    node* rotR(node* h) {
        node* x = h->l; h->l = x->r; x->r = h;
        x->color = h->color; h->color = true;
        return x;
    }
    node* colorFlip(node* h) {
        h->color = !h->color;
        h->l->color = !h->l->color;
        h->r->color = !h->r->color;
        return h;
    }
    node* put(node* h, T key, T2 val) {
        if (h == nullptr)
            return new node(key, val);
        if (key < h->key) h->l = put(h->l, key, val);
        else h->r = put(h->r, key, val);
        if (isRed(h->r) && !isRed(h->l))  h = rotL(h);
        if (isRed(h->l) && isRed(h->l->l)) h = rotR(h);
        if (isRed(h->r) && isRed(h->l)) h = colorFlip(h);
        return h;
    }
    bool find(node* h, T key) {
        if (h == nullptr) return false;
        if (h->key == key) return true;
        if (key < h->key) return find(h->l, key);
        else return find(h->r, key);
    }
    node* root;
    public:
    LLRB_Rec() {
        root = nullptr;
    }
    void insert(T key, T2 val) {
        root = put(root, key, val);
        root->color = false;
    }
    bool contains(T key) {
        return find(root, key);
    }
};