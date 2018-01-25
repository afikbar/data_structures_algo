//
// Created by Afik on 06/01/2018.
//

#include "BalancedTreeK.h"


void BalancedTreeK::Insert(const Key *nkey, const Value *nval) {
    Node *y = this->search_upper(nkey);//finds leaf that key == nkey or key is it's "next"
    /*while (!y->isLeaf()) {//finding the nearest bigger brother.
        unsigned int childCnt = y->get_childCnt();
        int i = 0;
        for (i; i < childCnt; ++i) {
            Node *currChild = y->get_childX(i);
            if (*z < *currChild) {
                y = currChild;
                break;
            }
        }
    }*/
    Node *x = y->get_parent();
    Node *z = new Leaf(x, nkey, nval); //temp node creation
    z = x->insert_split(z);
    while (x != this->_root) { //!! check if same address! not key
        x = x->get_parent();
        if (z != NULL) z = x->insert_split(z);
        else {
            x->update_helper();
//            x->update_key();
//            x->update_size();
        }
    }
    if (z != NULL) {
        InternalNode *w = new InternalNode();
        Node **w_childArr = new Node *[2 * K - 1]();
        w_childArr[0] = x;
        w_childArr[1] = z;
        w->set_childArr(w_childArr);
        this->_root = w;
    }
}

/**
 * Deletes from the tree node with key=dkey if such exist.
 * otherwise - nothing. O(log_n)
 * @param dkey
 */
void BalancedTreeK::Delete(const Key *dkey) {
    Node *x = this->_root->search_node(dkey);
    if (x == NULL) return;
    Node *y = x->get_parent();
    Node **y_childArr = new Node *[2 * K - 1]();
    int xOrderStats = y->find_orderStats(x);
    for (int i = 0; i < xOrderStats; ++i) {
        y_childArr[i] = y->get_childX(i);
    }
    for (int j = xOrderStats; j < y->get_childCnt() - 1; ++j) {
        y_childArr[j] = y->get_childX(j + 1);
    }
    y->set_childArr(y_childArr);
    delete x;//must be a leaf, no worries from children delete.
    //check if y is legit
    while (y != NULL) {
        int y_childCnt = y->get_childCnt();
        if (y_childCnt < K && y != this->_root) { //not enoguh childs
            y = y->borrow_merge();//return the suspected next level node
        } else if (y_childCnt < 2) {//
            this->_root = y->get_childX(y_childCnt - 1);//rightmost child
            this->_root->set_parent(NULL);
            //safe delete of y
            y->set_childArr(new Node *[2 * K - 1]());
            delete y;
            return;// this is root..
        } else {
//            y->update_key();
            y->update_helper();
            y = y->get_parent();

        }

    }
    //continue here pl0x

}

Value *BalancedTreeK::Search(const Key *key) const {
    Node *isNode = this->_root->search_node(key);
    return isNode != NULL ? isNode->get_value() : NULL;
}

unsigned BalancedTreeK::Rank(const Key *key) const {
    unsigned rank = 1;
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
    if (*key2 < *key1) return NULL;
    Node *rightNode = this->search_upper(key1);
    Node *leftNode = this->search_upper(key2)->get_predecessor();
    if (*leftNode < *rightNode) return NULL;
    Value *rValue = rightNode->get_value();
    Value *lValue = leftNode->get_value();
    Value *maxVal = *rValue < *lValue ? lValue : rValue;
    //get first shared parent
    Node *rPrnt = rightNode->get_parent();
    Node *lPrnt = leftNode->get_parent();
    while (rPrnt!= lPrnt) {
        int rOrderStats = rPrnt->find_orderStats(rightNode);
        int lOrderStats = lPrnt->find_orderStats(leftNode);
        for (int i = lOrderStats+1; i < lPrnt->get_childCnt(); ++i) {//without leftnode value/maxval
            Value *currVal = lPrnt->get_childX(i)->get_value();
            if (currVal == NULL) continue;//TODO understand why there is nulls, probably deleted values or something..
            maxVal = *maxVal < *currVal ? currVal : maxVal;
        }
        for (int j = 0; j < rOrderStats; ++j) {//without rightnode value/maxval
            Value *currVal = rPrnt->get_childX(j)->get_value();
            if (currVal == NULL) continue;
            maxVal = *maxVal < *currVal ? currVal : maxVal;
        }
        rightNode = rPrnt;
        leftNode = lPrnt;
        rPrnt = rPrnt->get_parent();
        lPrnt = lPrnt->get_parent();
    }//rPrnt->get_parent() = lPrnt->get_parent()
    Node *shrdParent = rPrnt;
    int rOrderStats = shrdParent->find_orderStats(rightNode);
    int lOrderStats = shrdParent->find_orderStats(leftNode);
    for (int i = lOrderStats + 1; i < rOrderStats; ++i) {
        Value *currVal = shrdParent->get_childX(i)->get_value();//internalNode get_val is maxval.
        if (currVal == NULL) continue;
        maxVal = *maxVal < *currVal ? currVal : maxVal;
    }
    return maxVal;
}

Node *BalancedTreeK::search_upper(const Key *key1) const {
    Node *rightNode = this->_root;
    while (!rightNode->isLeaf()) {//finding the nearest bigger brother. or the node itself.
        unsigned int childCnt = rightNode->get_childCnt();
        int i = 0;
        for (i; i < childCnt; ++i) {
            Node *currChild = rightNode->get_childX(i);
            if (!(*(currChild->get_key()) < *key1)) {// !< is >=
                rightNode = currChild;
                break;
            }
        }
    }
    return rightNode;
}

