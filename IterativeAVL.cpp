#include <iostream>
#include <queue>
#include <stack>
using namespace std;

enum TRAVERSALMETHOD {
    PREORDER,
    INORDER,
    POSTORDER
};

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
        void visit(node* x, TRAVERSALMETHOD tm) {
            if (x) {
                if (tm == PREORDER)
                    cout<<x->key<<" ";
                visit(x->left, tm);
                if (tm == INORDER)
                    cout<<x->key<<" ";
                visit(x->right, tm);
                if (tm == POSTORDER)
                    cout<<x->key<<" ";
            }
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
        node* min(node * t) {
            if (t == nullptr) return nullptr;
            while (t->left != nullptr) t = t->left;
            return t;
        }
        node* max(node* t) {
            if (t == nullptr) return nullptr;
            while (t->right != nullptr) t = t->right;
            return t;
        }
        node* succeessor(node* x) {
            if (x == nullptr) return nullptr;
            if (x->right) return min(x->right);
            node* y = x->parent;
            while (y != nullptr && x == y->right) {
                x = y;
                y = y->parent;
            }
            return y;
        }
        node* predeceessor(node* x) {
            if (x == nullptr) return nullptr;
            if (x->left) return max(x->left);
            node* y = x->parent;
            while (y != nullptr && x == y->left) {
                x = y;
                y = y->parent;
            }
            return y;
        }
        void transplant(node* u, node* v) {
            if (u->parent == nullptr)
                root = v;
            else if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            if (v != nullptr) v->parent = u->parent;
        }
        T2 nullItem;
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
        void erase(T key) {
            node* x = root;
            while (x) {
                if (key == x->key) break;
                x = (key < x->key) ? x->left:x->right;
            }
            if (x == nullptr) {
                cout<<"Item not found.\n";
                return; 
            }
            if (x->left == nullptr) {
                transplant(x, x->right);
            } else if (x->right == nullptr) {
                transplant(x, x->left);
            } else {
                node* y = min(x->right);
                if (y->parent != x) {
                    transplant(y, y->right);
                    y->right = x->right;
                    y->right->parent = y;
                }
                transplant(x, y);
                y->left = x->left;
                y->left->parent = y;
            }
        }
        T2& find(T key) {
            node* x = root;
            while (x) {
                if (key == x->key)
                    return x->value;
                x = (key < x->key) ? x->left:x->right;
            }
            return nullItem;
        }
        T2 min() {
            node* t = max(root);
            if (t != nullptr)
                return t->value;
            return -1;
        }
        T2 max() {
            node* t = max(root);
            if (t != nullptr)
                return t->value;
            return -1;
        }
        void inorder() {
            visit(root, INORDER);
            cout<<endl;
        }
        void preorder() {
            visit(root, PREORDER);
            cout<<endl;
        }
        void postorder() {
            visit(root, POSTORDER);
            cout<<endl;
        }
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
        T2& operator[](const T& key) {
            node* x = root;
            while (x != nullptr) {
                if (key == x->key)
                    return x->value;
                x = (key < x->key) ? x->left:x->right;
            }
            insert(key, nullItem);
            return find(key);
        }
    protected:
        class Iterator {
            private:
                stack<node*> sf;
            public:
                Iterator(node* it) {
                    node* curr = it;
                    while (it != nullptr) {
                        sf.push(curr);
                        curr = curr->left;
                    }
                }
                T2& curr() {
                    return sf.top()->value;
                }
                void next() {
                    node* curr = sf.top()->right;
                    sf.pop();
                    while (curr != nullptr) {

                    }
                }
                bool end() {
                    return sf.empty();
                }
        };
    public:
    Iterator begin() {
            return Iterator(root);
        }
};

int main() {
    string sed = "ASERCHINGX";
    AVLTree<char, char> avl;
    for (char c : sed)
        avl.insert(c, c);
    avl.preorder();
    avl.inorder();
    avl.postorder();
    avl.levelorder();
    avl['z'] = 'Z';
    cout<<avl['z']<<"\n";
    avl.levelorder();
    for (auto t = avl.begin(); !t.end(); t.next()) {
        cout<<t.curr()<<" ";
    }
    cout<<endl;
    return 0;
}