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
    Value *get_value() const { return _value; };

    void set_value(Value *value) { _value = value->clone(); };

    const bool isLeaf() { return true; };


};

#endif //SRC_LEAF_H
