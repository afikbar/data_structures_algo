//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_INTERNALNODE_H
#define SRC_INTERNALNODE_H

#include "Node.h"
#include "Leaf.h"

class InternalNode : public Node {

private:
    Node **_childArr;
    int _child_count;


public:
    InternalNode() {};

    InternalNode(Node *parent, const Key *key = NULL) : Node(parent, key),
                                                        _childArr(new Node *[2 * K - 1]) { // _childArr is null pointers array
        /*for (int i = 0; i < 2 * K - 1; ++i) {
            _childArr[i]->set_parent(this);
        }*/
    };

    virtual ~InternalNode() {
        for (size_t i = 0; i < 2 * K - 1; ++i) {
            if (_childArr[i]) delete _childArr[i];
        }
        delete[] _childArr;
    };

    virtual void update_key();

    virtual void update_size();

    void update_childCnt();

    int find_orderStats(Node *newChild);

    void add_child(Node* newChild);

    virtual Node *insert_split(Node *newNode);

    void set_childArr(Node **childArr);

    const bool isLeaf() { return false; };

    virtual Leaf * search_node(const Key *key);

    bool remove_child(Node *child);


};

#endif //SRC_INTERNALNODE_H
