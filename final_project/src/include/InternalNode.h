//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_INTERNALNODE_H
#define SRC_INTERNALNODE_H

#include "Node.h"

class InternalNode : public Node {

private:
    Node **_childArr;
    unsigned _childCnt; //amount of children including sentinels
    Value *_maxVal;


public:
    InternalNode() : Node(), _childArr(new Node *[2 * K - 1]()), _childCnt(0), _maxVal(NULL) {};

    virtual ~InternalNode();

    virtual unsigned get_childCnt() const { return _childCnt; }

    virtual Node *get_childX(int x) const;

    virtual Value *get_value() const { return this->_maxVal; }

    virtual unsigned int find_orderStats(Node *newChild);

    virtual void copy_child(Node **destArr, unsigned start = 0, unsigned end = 2 * K - 1);

    virtual Node *search_node(const Key *key);

    const bool isLeaf() { return false; };

    virtual bool isSentinel() const { return false; }

    virtual void set_childArr(Node **childArr);

    virtual void set_value(Value *value) { _maxVal = value; }

    virtual void update_key();

    virtual void update_size();

    virtual void update_childCnt();

    virtual void update_maxValue();

    virtual void add_child(Node *newChild, unsigned int minBound = 0, unsigned int maxBound = 2 * K - 2);

    virtual Node *borrow_merge();

    virtual Node *insert_split(Node *z);
};

#endif //SRC_INTERNALNODE_H
