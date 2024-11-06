#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "Box.h"

class List{
    private:
        Box* header;
        int size;
    public:
        List();
        ~List();
        void Add(int x, int y, int n);
        Box *getItem(int index) const;
        void Clear();
        int getSize() const;
};
#endif