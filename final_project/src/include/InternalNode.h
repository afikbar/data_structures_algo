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
    //TODO: internalNode c'tor init key and parent to null!
    //TODO: i might not need to New on keys in InternalNodes..... (problem with set_key,update_key)

    InternalNode(Node *parent, const Key *key) : Node(parent, key),
                                                 _childArr(new Node *[2 * K - 1]()),
                                                 _childCnt(0),
                                                 _maxVal(NULL) {};
    // _childArr is null pointers array

    virtual ~InternalNode() {
        for (size_t i = 0; i < 2 * K - 1; ++i) {
            if (_childArr[i]) delete _childArr[i];
        }
        delete[] _childArr;
    }

    virtual unsigned get_childCnt() const {
        return _childCnt;
    }

    virtual Node *get_childX(int x) const;

    virtual Value *get_value() const {
        return this->_maxVal;
    }

    const bool isLeaf() { return false; };

    virtual bool isSentinel() const { return false; }

    virtual void set_childArr(Node **childArr, unsigned start = 0, unsigned end = 2 * K - 1);

    virtual void set_value(Value *value) { _maxVal = value; }

    virtual void update_key();
    //TODO add minKey inorder to find correct place for getMaxKey (right boundry problem, no need for next\prev)
    // consider prev and next still since this ^ will require new search method.
    //TODO maybe i dont need to clone keys for internalnodes, just keep pointer to maxkey?

    virtual void update_size();

    virtual void update_childCnt();

    virtual void update_maxValue();

    virtual Node *borrow_merge();

    virtual Node *insert_split(Node *newNode);

    virtual unsigned int find_orderStats(Node *newChild);

    virtual Node *search_node(const Key *key);

    virtual void add_child(Node *newChild, unsigned int minBound = 0, unsigned int maxBound = 2 * K - 1);

    virtual void copy_child(Node **destArr, unsigned start = 0, unsigned end = 2 * K - 1);

    bool remove_child(Node *child);


};

#endif //SRC_INTERNALNODE_H
