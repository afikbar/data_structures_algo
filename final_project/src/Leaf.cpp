//
// Created by Afik on 12/01/2018.
//
#include "Leaf.h"


Node *Leaf::search_node(const Key *key) {
    if (!(*(this->get_key()) < *key) && !(*key < *(this->get_key()))) return this; // !< && !> is ==
    return NULL;
}

void Leaf::update_size() {
    if (!this->_isSentinel) this->set_size(1);
    else this->set_size(0);
}
