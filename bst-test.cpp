#include <iostream>
#include "avl_rec.hpp"
#include "avltree.hpp"
#include "llrb_rec.hpp"
#include "llrbtree.hpp"
#include "rbtree.hpp"
#include <map>
using namespace std;

void avlr(int num) {
    cout<<"AVL (Rec)\n";
    AVL_Rec<int, int> avlr;
    for (int i = 0; i < num; i++) {
        avlr.insert(rand() % 255000, i);
    }
    int fcnt = 0, mcnt = 0;
    for (int i = 0; i < num; i++) {
        if (avlr.contains(rand() % 255000)) fcnt++;
        else mcnt++;
    }
    cout<<"hits: "<<fcnt<<"\n";
    cout<<"misses: "<<mcnt<<"\n";
}

void llrbr(int num) {
    cout<<"LLRB (Rec)\n";
    LLRB_Rec<int, int> llrbr;
    for (int i = 0; i < num; i++) {
        llrbr.insert(rand() % 255000, i);
    }
    int fcnt = 0, mcnt = 0;
    for (int i = 0; i < num; i++) {
        if (llrbr.contains(rand() % 255000)) fcnt++;
        else mcnt++;
    }
    cout<<"hits: "<<fcnt<<"\n";
    cout<<"misses: "<<mcnt<<"\n";
}

void avl(int num) {
    cout<<"AVL (Itr)\n";
    AVLTree<int, int> avl;
    for (int i = 0; i < num; i++) {
        avl.insert(rand() % 255000, i);
    }
    int fcnt = 0, mcnt = 0;
    for (int i = 0; i < num; i++) {
        if (avl.contains(rand() % 255000)) fcnt++;
        else mcnt++;
    }
    cout<<"hits: "<<fcnt<<"\n";
    cout<<"misses: "<<mcnt<<"\n";
}

void llrb(int num) {
    cout<<"LLRB (Itr)\n";
    LLRBTree<int, int> llrb;
    for (int i = 0; i < num; i++) {
        llrb.insert(rand() % 255000, i);
    }
    int fcnt = 0, mcnt = 0;
    for (int i = 0; i < num; i++) {
        if (llrb.contains(rand() % 255000)) fcnt++;
        else mcnt++;
    }
    cout<<"hits: "<<fcnt<<"\n";
    cout<<"misses: "<<mcnt<<"\n";
}

void rb(int num) {
    cout<<"RedBlack (Itr)\n";
    RBTree<int, int> rb;
    for (int i = 0; i < num; i++) {
        rb.insert(rand() % 255000, i);
    }
    int fcnt = 0, mcnt = 0;
    for (int i = 0; i < num; i++) {
        if (rb.contains(rand() % 255000)) fcnt++;
        else mcnt++;
    }
    cout<<"hits: "<<fcnt<<"\n";
    cout<<"misses: "<<mcnt<<"\n";
}

void stdmap(int num) {
    cout<<"std::map (Iterative RB)\n";
    map<int, int> stl;
    for (int i = 0; i < num; i++) {
        stl.insert(make_pair(rand() % 255000, i));
    }
        int fcnt = 0, mcnt = 0;
    for (int i = 0; i < num; i++) {
        if (stl.find(rand() % 255000) == stl.end()) mcnt++;
        else fcnt++;
    }
    cout<<"hits: "<<fcnt<<"\n";
    cout<<"misses: "<<mcnt<<"\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout<<"Specify tree size.\n";
        return -1;
    }
    int num = atoi(argv[1]);
    cout<<"N = "<<num<<"\n";
    string alg = argv[2];
    if (alg == "avl") avl(num); 
    if (alg == "avlr") avlr(num); 
    if (alg == "llrb") llrb(num);
    if (alg == "llrbr") llrbr(num);
    if (alg == "rb") rb(num);
    if (alg == "stl") stdmap(num);
    return 0;
}