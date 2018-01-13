//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_INTERNALNODE_H
#define SRC_INTERNALNODE_H

#include "Node.h"

class InternalNode : public Node {

private:
    Node **_child;
    int _child_count;

public:
    InternalNode() {};

    InternalNode(Node *parent, const Key *key = NULL) : Node(parent, key),
                                                        _child(new Node *[2 * K - 1]) { // _child is null pointers array
        /*for (int i = 0; i < 2 * K - 1; ++i) {
            _child[i]->set_parent(this);
        }*/
    };

    virtual ~InternalNode() {
        for (size_t i = 0; i < 2 * K - 1; ++i) {
            if (_child[i]) delete _child[i]
        }
        delete[] _child;
    };

    virtual void update_key();

    void count_child();

    void add_child(Node* newChild);

    virtual Node *insert_split(Node *newNode);

    void set_child(Node **newChild);

    void set_child(Node *newChild);

    const bool isLeaf() { return false; };

    bool remove_child(Node *child);


};

#endif //SRC_INTERNALNODE_H
