//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_LEAF_H
#define SRC_LEAF_H

#include "Node.h"

class Leaf : public Node {

private:
    Value *_value;

public:
    Leaf(Node *parent, const Key *key, const Value *value) : Node(parent, key), _value(value->clone()) {}

    virtual ~Leaf() {
        delete _value;
    }

    Value *get_value() const { return _value; };

    void set_value(Value *value) { _value = value->clone(); };

    const bool isLeaf() { return true; };

    virtual void update_key() {};

    virtual Leaf * search_node(const Key *key) {
        if (this->get_key() == key) return this;
        return NULL;
    }
};

#endif //SRC_LEAF_H
