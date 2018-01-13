//
// Created by Afik on 12/01/2018.
//

#include "InternalNode.h"

void InternalNode::update_key() {
    this->set_key(_child[_child_count]->get_key()); //rightmost child.key, assumes lower levels are intact.
}

bool InternalNode::remove_child(Node *child) {

}

void InternalNode::count_child() {
    int cnt = 0;
    while (this->_child[cnt++] != NULL);
    _child_count = cnt;
}


/**
 * gets new child array to replace to old one.
 * deletes the old one.
 * @param newChild
 */
void InternalNode::set_child(Node **newChild) {
//    if (this._child[0]->get_key() == NULL){ //child init
//        _child[0] = newChild;
//        return;
//    }
    for (int i = 0; i < 2 * K - 1 && newChild[i] != NULL; ++i) {
        newChild[i]->set_parent(this);
    }
    delete[] this->_child; //deletes the old
    this->_child = newChild;
    this->count_child();
    this->update_key();
}


void InternalNode::set_child(Node *newChild) {
    newChild->set_parent(this);
    if (this->_child[0] == NULL) { //init, first one is min Sentinel
        this->_child[0] = newChild;
        this->count_child();
        this->update_key();
        return;
    }

    //find node places
    auto temp_child = newChild;
    for (int i = 1; i < 2 * K - 1; ++i) { // assuming node is larger than minSentinel
        auto currChild = this->_child[i]; // this doesnt handle case if no room for the child?
        if (temp_child < currChild) {
            Node *temp = currChild;
            this->_child[i] = temp_child;
            temp_child = temp;
        }
    }

}

Node *InternalNode::insert_split(Node *newNode) {
    if (this->_child_count <= 2 * K - 1) { //handles case where there is room for newNode.
        this->add_child(newNode);
        return NULL;
    }
    Node * y = new InternalNode();
    

    return y;
}

void InternalNode::add_child(Node *newChild) {
    newChild->set_parent(this);
    auto temp_child = newChild;
    for (int i = 1; i < 2 * K - 1 && this->_child[i-1] != NULL; ++i) { //assuming newChild larger than minSentinel.
        auto currChild = this->_child[i];
        if (temp_child < currChild) {
            Node *temp = currChild;
            this->_child[i] = temp_child;
            temp_child = temp;
        }
    }

}



//    auto temp_child = newChild;
//    for (int i = 0; i < 2 * K - 2; ++i) {
//        auto currChild = this->_child[i];
//        if (temp_child < currChild) { //once the place has been spotted, t
//            Node *temp = currChild;
//            this->_child[i] = temp_child;
//            temp_child = temp;
//        }
//        this->_child[i] = currChild;
//
//    }