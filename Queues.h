#ifndef QUEUES_h
#define QUEUES_H

#include <iostream>

class Queues{
    private:        
        struct Players{
            int coordx = 0;
            int coordy = 0;
            int position = 0;
            std::string name;
            Players* next;
            Players(std::string n): 
            name(n), next(nullptr){}
        };
        Players* last = nullptr;
        Players* first = nullptr;
        int size;
    public:
        Queues();
        ~Queues();
        void enqueue(std::string name);
        std::string dequeue();
        bool isEmpty() const;
        int getSize() const;
        void clear();

};
#endif