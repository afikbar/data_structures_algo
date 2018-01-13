//
// Created by Afik on 06/01/2018.
//

#ifndef SRC_BALANCEDTREEK_H
#define SRC_BALANCEDTREEK_H

#include "Key.h"
#include "Value.h"
#include <cstddef>

class BalancedTreeK {

private:



public:
    BalancedTreeK(const Key *min, const Key *max) {

    }

    /** class D'tor:
     * deletes the tree in O(n). recursive calls to node d'tors.
     * since internal nodes < leaves(n), total calls to delete < 2n.
     */
    virtual ~BalancedTreeK() {
        if (_root) delete _root;
    }
    void Insert(const Key *nkey, const Value *nval);

    void Delete(const Key *dkey);

    Value *Search(const Key *key) const;

    unsigned Rank(const Key *key) const;

    const Key *Select(unsigned index) const;

    const Value *GetMaxValue(const Key *key1, const Key *key2) const;


};

#endif //SRC_BALANCEDTREEK_H
