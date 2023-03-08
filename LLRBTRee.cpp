#include <iostream>
#include <queue>
using namespace std;

enum TRAVERSALMETHOD {
    PREORDER,
    INORDER,
    POSTORDER
};
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
};

int main() {
    string sed = "ASEARCHINGEXAMPLE";
    LLRBTree<char, char> ll;
    for (char c : sed)
        ll.insert(c, c);
    ll.preorder();
    ll.inorder();
    ll.postorder();
    ll.levelorder();
    ll['z'] = 'Z';
    cout<<ll['z']<<"\n";
    ll.levelorder();
    return 0;
}
