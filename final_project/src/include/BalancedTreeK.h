//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_BALANCEDTREEK_H
#define SRC_BALANCEDTREEK_H

#include "Node.h"
#include "InternalNode.h"
#include "Leaf.h"
#include "ParameterK.h"
#include <cstddef>

class BalancedTreeK {

private:
    Node *_root;


public:
    /** class C'tor:
     *
     * @param min
     * @param max
     */
    BalancedTreeK(const Key *min, const Key *max) {

        InternalNode *root = new InternalNode(NULL);
        Node **newChild = new Node *[2 * K - 1];
        Leaf *minNode = new Leaf(root, min, NULL);
        Leaf *maxNode = new Leaf(root, max, NULL);

        newChild[0] = minNode;
        newChild[1] = maxNode;
        root->set_child(newChild); // O(1)
        _root = root;
    }
    /** class D'tor:
     * deletes the tree in O(n). recursive calls to node d'tors.
     * since internal nodes < leaves(n), total calls to delete < 2n.
     */
    virtual ~BalancedTreeK() {
        if (_root) delete _root;
    }
    /** Insert:
     * inserts a new leaf while copies given key and val.
     * required O(logn)
     * @param nkey
     * @param nval
     */
    void Insert(const Key *nkey, const Value *nval);

    void Delete(const Key *dkey);

    Value *Search(const Key *key) const;

    unsigned Rank(const Key *key) const;

    const Key *Select(unsigned index) const;

    const Value *GetMaxValue(const Key *key1, const Key *key2) const;


};

#endif //SRC_BALANCEDTREEK_H
