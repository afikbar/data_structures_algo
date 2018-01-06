#ifndef Value_H
#define Value_H


class Value {
public:
    virtual ~Value() {};

    virtual Value *clone() const = 0;

    virtual bool operator<(const Value &rhs) const = 0;
};

#endif