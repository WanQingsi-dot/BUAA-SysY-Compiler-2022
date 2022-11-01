#ifndef THIS_PROJECT_ARRAY1_CONST_H
#define THIS_PROJECT_ARRAY1_CONST_H

#include <vector>

class Array1Const {
public:
    const int d;  // 维度
    int *values;

    explicit Array1Const(int d, int *values)
            : d(d), values(values) {}

    ~Array1Const() {
        delete values;
    }
};

#endif //THIS_PROJECT_ARRAY1_CONST_H
