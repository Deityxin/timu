#include <iostream>
using namespace std ;
#define eletype int
struct Sequentlist{
    eletype *data;
    int size;
    int capacity;
};

void Intilist(Sequentlist *list , int capacity){
    list->size = 0 ;
    list->capacity = capacity ;
    list->data = new eletype[capacity] ;
}