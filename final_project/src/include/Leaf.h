//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_LEAF_H
#define SRC_LEAF_H

#include "Node.h"

class Leaf : public Node {

private:
    Value *_value;
    bool _isSentinel;

public:
    Leaf(Node *parent, const Key *key) : Node(parent, key, 0), _value(NULL), _isSentinel(true) {}
    //Sentinel c'tor (no Value)

    Leaf(Node *parent, const Key *key, const Value *value) : Node(parent, key, 1),
                                                             _isSentinel(false),
                                                             _value(value->clone()) {}

    virtual ~Leaf() { delete _value; }

    virtual void update_size();

    virtual Value *get_value() const { return this->_value; }

    virtual bool isSentinel() const { return _isSentinel; }

    virtual void set_value(Value *value) { _value = value;}

    virtual unsigned int get_childCnt() const { return 0; }

    virtual Node *get_childX(int x) const { return NULL; }

    const bool isLeaf() { return true; }

    virtual Node *search_node(const Key *key);
};

#endif //SRC_LEAF_H
