//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_NODE_H
#define SRC_NODE_H

#include "iostream"
#include "Value.h"
#include "Key.h"
#include "ParameterK.h"
#include <cstddef>

class Node {
private:
    Key *_key;
    Node *_parent;
    unsigned int _size; //number of leaves in subtree without sentinels

public:
    Node() : _parent(NULL), _key(NULL) {};

    Node(Node *parent, const Key *key) : _parent(parent) {
        set_key(key);
    };

    Key *get_key() const { return _key; }

    Node *get_parent() const { return _parent; }

    virtual Value *get_value() const {}

    unsigned int get_size() const { return _size; }

    virtual Node *get_childX(int x) const =0;

    virtual unsigned get_childCnt() const {}

    void set_key(const Key *key) { _key = key != NULL ? key->clone() : NULL; }

    void set_size(const unsigned int size) { _size = size; }

    void set_parent(Node *newParent) { _parent = newParent; }

    virtual void update_size()=0;

    virtual const bool isLeaf()=0;

    virtual void update_key()=0;

    virtual unsigned int find_orderStats(Node *newChild) {};

    virtual Node *insert_split(Node *newNode) {};

    virtual Node *search_node(const Key *key)=0;

    Node *select_rec(unsigned index);

    bool operator==(const Node &rhs) const;

    bool operator<(const Node &rhs) const;

    bool operator>(const Node &rhs) const;

    bool operator<=(const Node &rhs) const;

    bool operator>=(const Node &rhs) const;


};

#endif //SRC_NODE_H

