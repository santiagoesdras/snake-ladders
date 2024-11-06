#ifndef QUEUE_H
#define QUEUE_H

#include "Player.h"

class Queue {
private:
    struct Node {
        Player* player;
        Node* next;
        Node(Player* p) : player(p), next(nullptr) {}
    };

    Node* front;
    Node* back;
    int size;

public:
    Queue();
    ~Queue();
    void enqueue(Player* p);
    Player* dequeue();
    Player* peekFront() const;
    bool isEmpty() const;
    int getSize() const;
};

#endif
