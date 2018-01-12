//
// Created by Afik on 12/01/2018.
//
#include "Node.h"

bool Node::set_parent(Node *newParent) {

}


bool Node::operator<(const Node &rhs) const {
    return this->_key < rhs._key;
}

bool Node::operator>(const Node &rhs) const {
    return rhs._key < this->_key;
}

bool Node::operator==(const Node &rhs) const {
    return !(*this < rhs) && !(*this > rhs);
}

bool Node::operator<=(const Node &rhs) const {
    return !(rhs < *this);
}

bool Node::operator>=(const Node &rhs) const {
    return !(*this < rhs);
}
