#include "Queues.h"

Queues::Queues():
    last(nullptr), first(nullptr), size(0){}

Queues::~Queues(){
    clear();
}

void Queues::enqueue(std::string name){
    Players* newplayer = new Players(name);
    if(isEmpty()){
        first = last = newplayer;
    }else{
        last->next = newplayer;
        last = newplayer;
    }
    size++;
}

std::string Queues::dequeue(){
    if(isEmpty())throw std::out_of_range("La cola de jugadores esta vacia");
    Players* temp = first;
    std::string retorno = temp->name;
    first = first->next;
    delete(temp);
    if(isEmpty()) last = nullptr;
    return retorno;
}

bool Queues::isEmpty() const{
    return first == nullptr;
}

int Queues::getSize() const{
    return size;
}

void Queues::clear(){
    while(!isEmpty()){
        dequeue();
    }
}