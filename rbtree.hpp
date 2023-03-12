#include <iostream>
using namespace std;


template <class Key, class Value>
class RBTree {
    private:
        const bool red = true;
        const bool black = false;
        struct node {
            node* left;
            node* right;
            bool color;
            Key key;
            Value value;
            node(Key k, Value v, bool c, node* ll, node* rr)
            {
                key = k; value = v; color = c; 
                left = ll; right = rr;
            }
        };
        typedef node* link;
        link head, z;
        link x, p, g, gg;
        void rotR(link& h)
        {
            link x = h->left;
            h->left = x->right;
            x->right = h;
            h = x;
        }
        void rotL(link& h)
        {
            link x = h->right;
            h->right = x->left;
            x->left = h;
            h = x;
        }
        //this is mark allen weiss's re-write
        //it performs the same operations as sedgewick's original
        //but it is far simpler to read. 
        link rotate(Key v, link y)
        {
            if (v < y->key)
            {
                if (v < y->left->key)
                    rotR(y->left);
                else
                    rotL(y->left);
                return y->left;
            } else {
                if (v < y->right->key)
                    rotR(y->right);
                else
                    rotL(y->right);
                return y->right;
            }
        }
        link flipColor(link x)
        {
            x->color = red; x->left->color = black; x->right->color = black;
            return x;
        }
        void split(Key v)
        {
            x = flipColor(x);
            if (p->color)
            {
                g->color = red;
                if (v < g->key != v < p->key) p = rotate(v, g);
                x = rotate(v, gg);
                x->color = black;
            }
        }
        void preorder(link h)
        {
            if (h != z)
            {
                cout<<h->key<<" ";
                preorder(h->left);
                preorder(h->right);
            }
        }
    public:
        RBTree()
        {
            z = new node(0, 0, black, nullptr, nullptr);
            z->left = z; z->right = z;
            head = new node(INT_MIN, 0, black, 0, z);
        }
        void insert(Key v, Value info)
        {
            p = head;
            x = head;
            g = head;
            while (x != z)
            {
                gg = g; g = p; p = x;
                x = (v < x->key) ? x->left:x->right;
                if (x->left->color && x->right->color)
                    split(v);
            }
            x = new node(v, info, red, z, z);
            if (v < p->key) p->left = x; else p->right = x;
            split(v);
            head->right->color = black;
        }
        void show() {
            preorder(head->right);
            cout<<endl;
        }
        bool contains(Key key) {
            node* x = head->right;
            while (x != z) {
                if (x->key == key)
                    return true;
                x = (key < x->key) ? x->left:x->right;
            }
            false;
        }
};