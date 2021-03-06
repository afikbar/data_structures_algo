//
// Created by Afik on 12/01/2018.
//
#include "Node.h"

void Node::set_key(const Key *key) {
    delete this->_key;
    _key = key != NULL ? key->clone() : NULL;
}

void Node::update_helper() {
    this->update_childCnt();
    this->update_key();
    this->update_size();
    this->update_maxValue();
}

Node *Node::select_rec(unsigned index) {
    if (this->get_size() < index) return NULL;
    if (this->isLeaf()) return this;
    unsigned prvSize = 0;
    unsigned leftSize = 0;
    for (int i = 0; i < this->get_childCnt(); ++i) {
        Node *currChild = this->get_childX(i);
        leftSize += currChild->get_size(); //leftmost size
        if (index <= leftSize)
            return currChild->select_rec(
                    index - prvSize);//TODO debug missing by plus one the node(getting the sequel one)
        prvSize = leftSize;
    }
    return NULL;

}

Node *Node::get_predecessor() {
    Node *x = this;
    Node *z = x->get_parent();
    while (x == z->get_childX(0)) {
        x = z;
        z = z->get_parent();
    }
    int xOrderStats = z->find_orderStats(x);// x is not 0! (from while)
    Node *y = z->get_childX(xOrderStats - 1);
    while (!y->isLeaf()) y = y->get_childX(y->get_childCnt() - 1);
//    if (y->isSentinel()) return NULL;
    return y;
}


bool Node::operator<(const Node &rhs) const {
    return *(this->_key) < *(rhs._key);
}

bool Node::operator>(const Node &rhs) const {
    return *(rhs._key) < *(this->_key);
}

bool Node::operator==(const Node &rhs) const {
    return !(*this < rhs) && !(*this > rhs);
}

bool Node::operator<=(const Node &rhs) const {
    return !(*this > rhs);
}

bool Node::operator>=(const Node &rhs) const {
    return !(*this < rhs);
}

