#include <iostream>
#include <queue>
using namespace std;

enum TreeType {
    SPLAY,
    LLRB,
    AVL
};

template <class T, class T2>
class BalancedTree {
private:
    const static bool red = true;
    const static bool black = false;
    struct node {
        T key;
        T2 value;
        bool color;
        int height;
        node* left;
        node* right;
        node* parent;
        node(T k, T2 v) {
            height = 0;
            key = k; value = v; color = red; left = right = parent = nullptr;
        }
    };
    TreeType balMethod;
    node* root;
    bool isRed(node* h) { return (h == nullptr) ? false:(h->color == red); }
    int height(node* h) { return (h == nullptr) ? -1:h->height; }
    int balanceFactor(node* h) { return height(h->left) - height(h->right); }
    int max(int a, int b) { return (a < b) ? b:a; }
    void left_rotate(node* x);
    void right_rotate(node* x);
    void balanceSplay(node* x);
    void balanceAVL(node* x);
    void balanceLLRB(node* x);
public:
    BalancedTree(TreeType treeType) {
        balMethod = treeType;
        root = nullptr;
    }
    void insert(T key, T2 val);
    void levelorder() {
            queue<node*> fq;
            fq.push(root);
            while (!fq.empty()) {
                int nc = fq.size();
                while (nc > 0) {
                    node* x = fq.front();
                    fq.pop(); nc--;
                    if (x) {
                        cout<<x->key<<" ";
                        fq.push(x->left);
                        fq.push(x->right);
                    }
                }
                cout<<endl;
            }
        }
};


template <class T, class T2>
void BalancedTree<T,T2>::left_rotate(node *x) {
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
    switch (balMethod) {
        case LLRB:
                y->color = x->color;
                x->color = red;
                break;
        case AVL:
                x->height = 1 + max(height(x->left), height(x->right));
                y->height = 1 + max(height(y->left), height(y->right));
        case SPLAY: break;
    }
}
  
template <class T, class T2>
void BalancedTree<T,T2>::right_rotate(node *x) {
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
    switch (balMethod) {
        case LLRB:
                y->color = x->color;
                x->color = red;
                break;
        case AVL:
                x->height = 1 + max(height(x->left), height(x->right));
                y->height = 1 + max(height(y->left), height(y->right));
        case SPLAY: break;
    }
}

template <class T, class T2>
void BalancedTree<T,T2>::balanceSplay(node* x) {
    while (x->parent) {
      if (!x->parent->parent) {
        if (x->parent->left == x) right_rotate(x->parent);
        else left_rotate(x->parent);
      } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
        right_rotate(x->parent->parent);
        right_rotate(x->parent);
      } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
        left_rotate(x->parent->parent);
        left_rotate(x->parent);
      } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
        right_rotate(x->parent);
        left_rotate(x->parent);
      } else {
        left_rotate(x->parent);
        right_rotate(x->parent);
      }
    }
}


template <class T, class T2>
void BalancedTree<T,T2>::balanceLLRB(node* x) {
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

template <class T, class T2>
void BalancedTree<T,T2>::balanceAVL(node* x) {
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

template <class T, class T2>
void BalancedTree<T,T2>::insert(T key, T2 value) {
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
    switch (balMethod) {
        case LLRB:
                balanceLLRB(x);
                break;
        case AVL:
                balanceAVL(x);
                break;
        case SPLAY: 
                balanceSplay(x);
                break;
    }
}

int main() {
    BalancedTree<char, char> llrb(LLRB);
    BalancedTree<char, char> avl(AVL);
    BalancedTree<char, char> splay(SPLAY);
    string sed = "ASEARCHINGEXAMPLE";
    for (char c : sed) {
        llrb.insert(c, c);
        avl.insert(c, c);
        splay.insert(c, c);
    }

    cout<<"Left Leaning RedBlack tree: \n";
    llrb.levelorder();
    cout<<"AVL Tree: \n";
    avl.levelorder();
    cout<<"Splay Tree: \n";
    splay.levelorder();
    return 0;
}