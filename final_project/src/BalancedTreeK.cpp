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
    return isNode ? isNode->get_value() : NULL;
}

unsigned BalancedTreeK::Rank(const Key *key) const {
    return 0;
}

const Key *BalancedTreeK::Select(unsigned index) const {
    return NULL;
}

const Value *BalancedTreeK::GetMaxValue(const Key *key1, const Key *key2) const {
    return NULL;
}
