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
    Leaf(Node *parent, const Key *key) : Node(parent, key), _value(NULL), _isSentinel(true) {
        this->update_size();
    }//Sentinel c'tor (no Value)

    Leaf(Node *parent, const Key *key, const Value *value) : Node(parent, key),
                                                             _isSentinel(false),
                                                             _value(value->clone()) {
        this->update_size();
    }

    virtual ~Leaf() {
        delete _value; // since clone uses new
    }

    virtual void update_size() {
        if (!this->_isSentinel) this->set_size(1);
        else this->set_size(0);
    }

    virtual Value *get_value() const { return _value; }

    bool is_isSentinel() const { return _isSentinel; }

    void set_isSentinel(bool isSentinel) { _isSentinel = isSentinel; }

    void set_value(const Value *value) { _value = value != NULL ? value->clone() : NULL; }

    virtual Node *get_childX(int x) const {
        return NULL;
    }

    const bool isLeaf() { return true; }

    virtual void update_key() {}

    virtual Node *search_node(const Key *key) {
        if (!(*(this->get_key()) < *key) && !(*key < *(this->get_key()))) return this; // !< && !> is ==
        return NULL;
    }
};

#endif //SRC_LEAF_H
