//
// Created by Afik on 06/01/2018.
//

#include "include/BalancedTreeK.h"


void BalancedTreeK::Insert(const Key *nkey, const Value *nval) {
    Node *z = new Leaf(NULL, nkey, nval); //temp node creation
    Node *y = this->_root;
    while (!y->isLeaf()) {
        unsigned int childCnt = y->get_childCnt();
        int i = 0;
        for (i; i < childCnt; ++i) {
            Node *currChild = y->get_childX(i);
            if (*z < *currChild) {
                y = currChild;
                break;
            }
        }
    }
    Node *x = y->get_parent();
    z = x->insert_split(z);
    while (x != this->_root) { //!! check if same address! not key
        x = x->get_parent();
        if (z != NULL) z = x->insert_split(z);
        else {
            x->update_key();
            x->update_size();
        }
    }
    if (z != NULL) {
        InternalNode *w = new InternalNode();
        Node **w_childArr = new Node *[2 * K - 1]();
        w_childArr[0] = x;
        w_childArr[1] = z;
        w->set_childArr(w_childArr);
        this->_root = w;
    }
}

void BalancedTreeK::Delete(const Key *dkey) {

}

Value *BalancedTreeK::Search(const Key *key) const {
    Node *isNode = this->_root->search_node(key);
    return isNode != NULL ? isNode->get_value() : NULL;
}

unsigned BalancedTreeK::Rank(const Key *key) const {
    unsigned rank = 1;
    Node *x = this->_root->search_node(key);
    if (x == NULL) return 0;
    Node *y = x->get_parent();
    while (y != NULL) {
        int xOrderStats = y->find_orderStats(x);
        for (int i = 0; i < xOrderStats; ++i) {
            rank += y->get_childX(i)->get_size();
        }
        x = y;
        y = y->get_parent();
    }
    return rank;
}

const Key *BalancedTreeK::Select(unsigned index) const {
    Node *selected = this->_root->select_rec(index);
    if (selected == NULL) return NULL;
    return selected->get_key();
}

const Value *BalancedTreeK::GetMaxValue(const Key *key1, const Key *key2) const {
    return NULL;
}
