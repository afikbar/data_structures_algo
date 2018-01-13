//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_NODE_H
#define SRC_NODE_H

#include "Value.h"
#include "Key.h"
#include "ParameterK.h"

class Node {

public:
    Node(Key *_key, Node *_parent) : _key(_key->clone()), _parent(_parent) {};

    virtual ~Node();

    Key *get_key() const { return _key; };

    Node *get_parent() const { return _parent; };

    bool set_key(Key *key) { _key = key->clone(); };

    bool set_parent(Node *newParent);
    void set_parent(Node *newParent);

    virtual const bool isLeaf()=0;

    bool operator==(const Node &rhs) const;

    bool operator<(const Node &rhs) const;

    bool operator>(const Node &rhs) const;

    bool operator<=(const Node &rhs) const;

    bool operator>=(const Node &rhs) const;

private:
    Key *_key;
    Node *_parent;

};

#endif //SRC_NODE_H

