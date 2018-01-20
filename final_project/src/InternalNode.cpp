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
        this->add_child(newNode, 0, _childCnt);
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

/**
 * gets y parent of deleted node, that needs "completion" from brother
 * notice that y is expected to be after deletion and before childCnt update!
 * @param y parent of deleted node.
 * @return
 */
Node *InternalNode::borrow_merge() {
    InternalNode *y = this;
    int y_lastPos = y->get_childCnt();//removed
    Node *z = y->get_parent();
    Node **z_childArr = new Node *[2 * K - 1]();
    Node **y_childArr = new Node *[2 * K - 1]();
    Node **x_childArr = new Node *[2 * K - 1]();
    Node *x;//brother of y
    for (int i = 0; i < z->get_childCnt(); ++i) {
        if (y == z->get_childX(i)) {//pointer equality!
            //search for promised bro assuming K>1
            x = i == 0 ? z->get_childX(i + 1) : z->get_childX(i - 1);//x is bro
            /**because y child got removed**/
            if (y_lastPos + x->get_childCnt() <= 2 * K - 1) {
                //there is enough place in x for all y's child's
                for (int j = 0; j < y_lastPos; ++j) { //
                    x->add_child(y->get_childX(j));
                }
                y->set_childArr(y_childArr);//NULLS - quick replace of y_childArr to avoid deletion via ptrs.
                delete y;
                for (int k = i; k < z->get_childCnt() - 1; ++k) {//i is the place of y in z
                    z_childArr[k] = z->get_childX(k + 1);
                }
                z_childArr[z->get_childCnt() - 1] = NULL;
                z->set_childArr(z_childArr);

            } else {//need to borrow to make y good
                y->copy_child(y_childArr, 0, y_lastPos);// copy y elemnts
                if (i==0){
                    y_childArr[y_lastPos] = x->get_childX(0);
                    x->copy_child(x_childArr,1,x->get_childCnt());
                }
                else {
                    y->add_child(x->get_childX(x->get_childCnt()-1));
                    x->copy_child(x_childArr,0,x->get_childCnt()-1);
                }
//                for (int k = y_lastPos; k < K; ++k) {
//                    y_childArr[k] = x->get_childX(k - y_lastPos);
//                }
                y->set_childArr(y_childArr);
                //x->copy_child(x_childArr, K, x->get_childCnt());
                x->set_childArr(x_childArr);
                z->update_key();
                z->update_size();
            }
            return z;
        } else z_childArr[i] = z->get_childX(i);//add childs of z up to y.

    }
    return NULL;
}
