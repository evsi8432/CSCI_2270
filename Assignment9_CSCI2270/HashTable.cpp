#include "HashTable.h"

using namespace std;

HashTable::HashTable()
{
  nil = new Movie;
	nil -> next = NULL;
	nil -> title = "nil";
	nil -> year = 0;
  for(int i = 0; i < 10; i++){
    hashTable[i] = nil;
  }
}

HashTable::~HashTable()
{
    //dtor
}

int HashTable::hashsum(string x){
    int sum = 0;
    for(int i = 0; i < x.size(); i++){
        sum = sum + x[i];
    }
    sum = sum % 10;
    return sum;
}

void HashTable::insertMovie(string title, int year){
    Movie *n1 = new Movie;
    n1->title = title;
    n1->year = year;
    n1->next = nil;
    int key = hashsum(title);
    if(hashTable[key] == nil){
        hashTable[key] = n1;
    }
    else if(n1->title < hashTable[key]->title){
        n1->next = hashTable[key];
        hashTable[key] = n1;
    }
    else{
        Movie *x = hashTable[key];
        while(x->next != nil){
            if(n1->title < x->next->title){
                n1->next = x->next;
                x->next = n1;
                return;
            }
            x = x->next;
        }
        x->next = n1;
    }
}

void HashTable::deleteMovie(string title){
    int key = hashsum(title);
    Movie *x = hashTable[key];
    bool found = false;
    if(x->title == title){
        hashTable[key] = x->next;
        delete x;
        return;
    }
    while(x != nil){
        if(x->next->title == title){
            found = true;
            break;
        }
        x = x->next;
    }
    if(found == false){
        cout << "Movie not found" << endl;
        return;
    }
    else{
      Movie *del = x->next;
      x->next = del->next;
      delete del;
    }
}

void HashTable::findMovie(string title){
    int key = hashsum(title);
    Movie *x = hashTable[key];
    while(x != nil){
        if(x->title == title){
            cout << key << ":" << x->title << ":" << x->year << endl;
            return;
        }
        x = x->next;
    }
    cout << "not found" << endl;
}

void HashTable::printInventory(){
    Movie *x;
    bool empt = true;
    for(int i = 0; i < 10; i++){
        x = hashTable[i];
        while(x != nil){
            cout << x->title << ":" << x->year << endl;
            empt = false;
            x = x->next;
        }
    }
    if(empt == true){
        cout<<"empty"<<endl;
    }
}
