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
    /**
     * number of leaves in subtree without sentinels
     */
    unsigned int _size; //number of leaves in subtree without sentinels

public:
    Node() : _parent(NULL), _key(NULL) {};

    Node(Node *parent, const Key *key) : _parent(parent), _key(key->clone()) {};

    virtual ~Node() {
        delete _key; //since clone uses new
    };

    Key *get_key() const { return _key; }

    Node *get_parent() const { return _parent; }

    virtual Value *get_value() const =0;

    unsigned int get_size() const { return _size; }

    virtual Node *get_childX(int x) const =0;

    virtual unsigned get_childCnt() const =0;

    Node *get_predecessor();

    void set_key(const Key *key) { _key = key != NULL ? key->clone() : NULL; }
    //TODO i might not need to clone each key. if removed modify internal delete to skip _key deletion.

    void set_size(const unsigned int size) { _size = size; }

    void set_parent(Node *newParent) { _parent = newParent; }

    virtual void set_value(Value *value) =0;

    virtual void copy_child(Node **destArr, unsigned start = 0, unsigned end = 2 * K - 1){};

    virtual void set_childArr(Node **childArr, unsigned start = 0, unsigned end = 2 * K - 1){};

    virtual void update_size()=0;

    //TODO check if updates need to be recursive? i.e. if child max key got updated it can affect parent same with size. if so, alter borrow&merge that uses set_children(calls updates) for nullifying childs
    virtual void update_key(){};

    virtual void update_childCnt(){};

    virtual void update_maxValue(){};

    virtual void update_helper(){
        this->update_childCnt();
        this->update_key();
        this->update_size();
        this->update_maxValue();
    };

    virtual const bool isLeaf()=0;

    virtual bool isSentinel() const=0;

    virtual void add_child(Node *newChild, unsigned int minBound = 0, unsigned int maxBound = 2 * K - 1){};

    virtual unsigned int find_orderStats(Node *newChild) {};

    virtual Node *insert_split(Node *newNode) {};

    virtual Node *search_node(const Key *key)=0;

    virtual Node *borrow_merge() {};

    Node *select_rec(unsigned index);

    bool operator==(const Node &rhs) const;

    bool operator<(const Node &rhs) const;

    bool operator>(const Node &rhs) const;

    bool operator<=(const Node &rhs) const;

    bool operator>=(const Node &rhs) const;


};

#endif //SRC_NODE_H

