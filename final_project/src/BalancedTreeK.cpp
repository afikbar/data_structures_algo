//
// Created by Afik on 06/01/2018.
//

#include "include/BalancedTreeK.h"


void BalancedTreeK::Insert(const Key *nkey, const Value *nval) {
    Node *y = this->_root;
    Node *z = new Leaf(NULL, nkey, nval);

    while (!y->isLeaf()) {

    }
}

void BalancedTreeK::Delete(const Key *dkey) {

}

Value *BalancedTreeK::Search(const Key *key) const {
    Leaf *isNode = this->_root->search_node(key);
    return isNode == NULL ? isNode->get_value() : NULL;
}

unsigned BalancedTreeK::Rank(const Key *key) const {
    int rank = 1;
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
