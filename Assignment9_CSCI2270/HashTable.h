#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <iostream>

struct Movie{
    std::string title;
    int year;
    Movie *next;

    Movie(){};

    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;
    }

};

class HashTable
{
    public:
        HashTable();
        ~HashTable();
        void insertMovie(std::string in_title, int in_year);
        void findMovie(std::string in_title);
        void deleteMovie(std::string in_title);
        void printInventory();
        int hashsum(std::string x);
    protected:
    private:
        Movie *hashTable[10];
        Movie *nil;
};

#endif // HASHTABLE_H
