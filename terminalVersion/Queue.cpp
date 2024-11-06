#include "Queue.h"

Queue::Queue() : front(nullptr), back(nullptr), size(0) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(Player* p) {
    Node* newNode = new Node(p);
    if (isEmpty()) {
        front = back = newNode;
    } else {
        back->next = newNode;
        back = newNode;
    }
    size++;
}

Player* Queue::dequeue() {
    if (isEmpty()) return nullptr;
    Node* temp = front;
    Player* p = front->player;
    front = front->next;
    delete temp;
    size--;
    return p;
}

Player* Queue::peekFront() const {
    return front ? front->player : nullptr;
}

bool Queue::isEmpty() const {
    return size == 0;
}

int Queue::getSize() const {
    return size;
}
