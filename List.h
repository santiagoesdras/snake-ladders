#ifndef LIST_H
#define LIST_H

#include <iostream>

class List{
    private:
        struct Box{
            std::string type;
            int number = 0;
            int coordx = 0;
            int coordy = 0;
            Box* next;
            Box(int x, int y, int n): 
            type("ordinary"), number(n), coordx(x), coordy(y), next(nullptr){}
        };
        Box* header;
        int size;
    public:
        List();
        ~List();
        void Add(int x, int y, int n);
        void Clear();
        int getSize() const;
};
#endif