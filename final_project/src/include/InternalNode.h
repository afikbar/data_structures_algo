//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_INTERNALNODE_H
#define SRC_INTERNALNODE_H

#include "Node.h"

class InternalNode : public Node {

private:
    Node *_child[2 * K - 1];

public:
    virtual ~InternalNode() {
        for (size_t i = 0; i < 2 * K - 1; ++i) {
            if (_child[i]) delete _child[i]
        }
        delete[] _child;
    };
    const bool isLeaf() { return false; };

    bool remove_child(Node *child);



};

#endif //SRC_INTERNALNODE_H
