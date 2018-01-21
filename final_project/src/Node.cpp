//
// Created by Afik on 12/01/2018.
//
#include "Node.h"


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

Node *Node::select_rec(unsigned index) {
    if (this->get_size() < index) return NULL;
    if (this->isLeaf()) return this;
//    Node *currChild = this->get_childX(0);
    unsigned prvSize = 0;
    //unsigned leftSize = currChild->get_size(); //leftmost size
    unsigned  leftSize = 0;
    for (int i = 0; i < this->get_childCnt();++i) {
        Node *currChild = this->get_childX(i);
        leftSize += currChild->get_size(); //leftmost size
        if (index <= leftSize) return currChild->select_rec(index - prvSize);
        prvSize = leftSize;
//        currChild = this->get_childX(i);
//        leftSize += currChild->get_size();
    }
    return NULL;
}



