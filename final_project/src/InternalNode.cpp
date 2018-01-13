//
// Created by Afik on 12/01/2018.
//

#include "InternalNode.h"

void InternalNode::update_key() {
    this->set_key(_childArr[_child_count]->get_key()); //rightmost child.key, assumes lower levels are intact.
}

bool InternalNode::remove_child(Node *child) {

}

void InternalNode::count_child() {
    int cnt = 0;
    while (this->_childArr[cnt++] != NULL);
    _child_count = cnt;
}


/**
 * gets new child array to replace to old one.
 * deletes the old one.
 * @param childArr
 */
void InternalNode::set_childArr(Node **childArr) {
//    if (this._childArr[0]->get_key() == NULL){ //child init
//        _childArr[0] = newChild;
//        return;
//    }
    for (int i = 0; i < 2 * K - 1 && childArr[i] != NULL; ++i) {
        childArr[i]->set_parent(this);
    }
    delete[] this->_childArr; //deletes the old
    this->_childArr = childArr;
    this->count_child();
    this->update_key();
}


void InternalNode::add_child(Node *newChild) {
    newChild->set_parent(this);
    if (this->_childArr[0] == NULL) { //init, first one is min Sentinel
        this->_childArr[0] = newChild;
        this->count_child();
        this->update_key();
        return;
    }

    //find node places - to be fixed using orderStats and maybe implement new method to shift array.
    auto temp_child = newChild;
    for (int i = 1; i < 2 * K - 1; ++i) { // assuming node is larger than minSentinel
        auto currChild = this->_childArr[i]; // this doesnt handle case if no room for the child?
        if (temp_child < currChild) {
            Node *temp = currChild;
            this->_childArr[i] = temp_child;
            temp_child = temp;
        }
    }

}

Node *InternalNode::insert_split(Node *newNode) {
    Node **x_childArr = new Node *[2 * K - 1];
    int zOrderStats = this->find_orderStats(newNode); //finds the place of newNode
    if (this->_child_count < 2 * K - 1) { //handles case where there is room for newNode.
//        this->add_child(newNode);
        for (int i = 0, j = 0; j < _child_count && i < _child_count; ++i, ++j) {
            if (i == zOrderStats) {
                x_childArr[i] = newNode;
                i++;
            }
            x_childArr[i] = this->_childArr[j];
        }
        this->set_childArr(x_childArr);
        return NULL;
    }
    InternalNode *y = new InternalNode();
    Node **y_childArr = new Node *[2 * K - 1];

    int i, j = 0;
    for (i, j; j < K && i < K; ++i, ++j) {
        if (zOrderStats < K) {
            if (i == zOrderStats) {
                x_childArr[i] = newNode;
                i++;
            }
            x_childArr[i] = this->_childArr[j];
            y_childArr[j] = this->_childArr[K + j - 1];

        } else {
            if (j == zOrderStats - K) {
                y_childArr[j] = newNode;
                j++;
            }
            x_childArr[i] = this->_childArr[i];
            y_childArr[j] = this->_childArr[K + i - 1];
        }
    }
    for (i; i < K; ++i)x_childArr[i] = this->_childArr[i]; //completes left-overs
    for (j; j < K; ++j)y_childArr[j] = this->_childArr[K + j - 1];

    this->set_childArr(x_childArr);
    y->set_childArr(y_childArr);

    return y;
}


int InternalNode::find_orderStats(Node *newChild) {
    int left = 0, right = this->_child_count;
    while (left <= right) { //binary search
        int middle = (left + right) / 2;
        if (_childArr[middle] > newChild)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return left; //upper bound in end of search
}