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

Box* List::getItem(int index) const {
    if (index < 0) {
        std::cerr << "Error: índice negativo no válido en getItem." << std::endl;
        return nullptr;
    }
    
    Box* current = this->header;
    int contador = 0;
    while (current) {
        if (contador == index) {
            return current;
        }
        contador++;
        current = current->next;
    }

    // Si el índice está fuera de rango
    std::cout << "El indice fuera de rango es: " << index << std::endl;
    std::cerr << "Error: índice fuera de rango en getItem." << std::endl;
    system("pause");
    return nullptr;
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