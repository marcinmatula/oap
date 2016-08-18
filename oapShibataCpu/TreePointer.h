
#ifndef TREEPOINTER_H
#define	TREEPOINTER_H

#include "Matrix.h"

enum TreePointerType {
    TYPE_COLUMN,
    TYPE_ROW
};

struct TreePointer {
    intt* nodeValue;
    intt realCount;
    intt count;
    intt index;
    TreePointerType type;
    math::Matrix* matrix;
    floatt* reValues;
    floatt* imValues;
};

#endif	/* TREEPOINTER_H */

