//
// Created by Afik on 12/01/2018.
//

#include <Leaf.h>
#include "InternalNode.h"

void InternalNode::update_key() {
    this->set_key(_childArr[_childCnt - 1]->get_key()); //rightmost child.key, assumes lower levels are intact.
}

bool InternalNode::remove_child(Node *child) {

}

void InternalNode::update_childCnt() {
    unsigned cnt = 0;
    while (this->_childArr[++cnt] != NULL && cnt < 2 * K - 1);
    _childCnt = cnt;
}


/**
 * gets new child array to replace to old one.
 * deletes the old one.
 * @param childArr
 */
void InternalNode::set_childArr(Node **childArr, unsigned start/* = 0*/, unsigned end/* = 2 * K - 1*/) {
    for (int i = start; i < end && childArr[i] != NULL; ++i) {
        childArr[i]->set_parent(this);
    }
    delete[] this->_childArr; //deletes the old
    // TODO understand if needed to delete each node in the array (might not be needed because im copying pointers)
    this->_childArr = childArr;
    this->update_childCnt();
    this->update_key();
    this->update_size();
}


void InternalNode::add_child(Node *newChild, unsigned int minBound/* = 0*/, unsigned int maxBound/* = _childCnt*/) {
    newChild->set_parent(this);
    if (this->_childArr[0] == NULL) { //init, first one is min Sentinel
        this->_childArr[0] = newChild;
        this->update_childCnt();
        this->update_key();
        this->update_size();
        return;
    }

    //implemt good add_child to use in insert_split:
    //assumptions: must be room for the node! i.e _childCnt < 2*K-1
    //copies current child between min and max bound, and adds new child inside
    int newOrderStats = this->find_orderStats(newChild); //finds the place of newNode - zero based
    Node **currArr = this->_childArr;
    Node **x_childArr = new Node *[2 * K - 1]();
    x_childArr[newOrderStats - minBound] = newChild;//puts new node at correct place/
    for (int i = minBound, j = minBound;//parallel to i = min - min (0), i< max-min+1
         j < maxBound && i < maxBound + 1; ++i, ++j) {//adding one node, so i can go higher
        if (i == newOrderStats) {
            i++;
        }
        x_childArr[i - minBound] = currArr[j];
    }
    this->set_childArr(x_childArr);
}

Node *InternalNode::insert_split(Node *newNode) {
    Node **x_childArr = new Node *[2 * K - 1]();
    int zOrderStats = this->find_orderStats(newNode); //finds the place of newNode - zero based
    if (this->_childCnt < 2 * K - 1) { //handles case where there is room for newNode.
        this->add_child(newNode, 0, _childCnt); //TODO check if works..
        return NULL;
    }
    //split needed, y will be the "larger" node
    InternalNode *y = new InternalNode();
    Node **y_childArr = new Node *[2 * K - 1]();
    this->copy_child(y_childArr, K, _childCnt);//init y_arr to last K-1 elements.
    y->set_childArr(y_childArr);//y_arr elements are in [0,K-1)
    if (zOrderStats < K) {//!!needs only to "shrink" x ("this") to K-1 and insert to it newNode
        y->add_child(this->get_childX(K - 1), 0, K - 1);//adds "missing" first elemnt in y
        this->add_child(newNode, 0, K - 1);//copies 4 nodes and insert 1 new = 5 [0,K-1)
    } else {//!!needs only to "shrink" x to K, and insert into y newNode.
        this->copy_child(x_childArr, 0, K);// [0,K) = K elemt
        this->set_childArr(x_childArr);
        y->add_child(newNode, 0, K - 1);// adds newNode + K-1 last elements = K elements.
    }
    return y;
}

/**
 * searchs for the order statisitc of a node in the childArr, Zero-Based!
 * if exist, returns it, if not, returns the index of the minimum key that is larger.
 * @param newChild
 * @return
 */
unsigned int InternalNode::find_orderStats(Node *newChild) {
    int left = 0, right = this->_childCnt - 1;
    while (left <= right) { //binary search
        int middle = (left + right) / 2;
        if (*_childArr[middle] == *newChild) return middle;
        if (*_childArr[middle] > *newChild)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return left; //upper bound in end of search
}

Node *InternalNode::search_node(const Key *key) {
    for (int i = 0; i < this->_childCnt; ++i) {
        if (!(*(this->_childArr[i]->get_key()) < *key)) return this->_childArr[i]->search_node(key); // !< is >=
    }
    return NULL;
}

void InternalNode::update_size() {
    unsigned int size = 0;
    for (int i = 0; i < _childCnt; ++i)
        size += _childArr[i]->get_size();
    this->set_size(size);
}

Node *InternalNode::get_childX(int x) const {
    if (x < _childCnt)
        return _childArr[x];
    std::cout << "Cant access child\n";
    return NULL;
}

void InternalNode::copy_child(Node **destArr, unsigned int start, unsigned int end) {
    for (int i = start; i < end; ++i) {
        destArr[i - start] = this->_childArr[i];
    }
}
