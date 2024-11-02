#include <iostream>
#include "List.h"

List::List():
    header(nullptr), size(0){}

List::~List(){
    Clear();
}

void List::Add(int x, int y, int n){
    Box* newBox = new Box(x, y, n);
    if(!header){
        header = newBox;
    }else{
        Box* temp = header;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = newBox;
    }
    size++;
}

void List::Clear(){
    Box* current = header;
    while(current){
        Box* nextBox = current->next;
        delete(current);
        current = nextBox;
    }
    header = nullptr;
    size = 0;
}

int List::getSize() const{
    return size;
}