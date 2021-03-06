#ifndef Key_H
#define Key_H

#include <cstddef>

class Key {
public:
    virtual ~Key() {};

    virtual Key *clone() const = 0;

    virtual bool operator<(const Key &rhs) const = 0;
};

#endif