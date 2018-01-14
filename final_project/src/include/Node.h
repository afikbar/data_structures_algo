//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_NODE_H
#define SRC_NODE_H

#include "Value.h"
#include "Key.h"
#include "ParameterK.h"
#include "Leaf.h"
#include <cstddef>

class Node {

public:
    Node() : _parent(NULL), _key(NULL) {};

    Node(Node *parent, const Key *key) : _parent(parent), _key(key->clone()) {};

    virtual ~Node() {
        delete _key;
    };

    Key *get_key() const { return _key; }

    Node *get_parent() const { return _parent; }

    int get_size() const { return _size; }

    void set_key(const Key *key) { _key = key->clone(); }

    void set_size(const int size) { _size = size; }

    void set_parent(Node *newParent);

    virtual void update_size()=0;

    virtual const bool isLeaf()=0;

    virtual void update_key()=0;

    virtual Node *insert_split(Node *newNode)=0;

    virtual Leaf *search_node(const Key *key)=0;

    bool operator==(const Node &rhs) const;

    bool operator<(const Node &rhs) const;

    bool operator>(const Node &rhs) const;

    bool operator<=(const Node &rhs) const;

    bool operator>=(const Node &rhs) const;

private:
    Key *_key;
    Node *_parent;
    int _size; //number of leaves in subtree

};

#endif //SRC_NODE_H

