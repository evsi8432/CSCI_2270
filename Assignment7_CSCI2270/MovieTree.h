#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <json/json.h>

struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;
    bool isRed;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;
};

class MovieTree
{
    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        void DeleteAll(MovieNode *node);
        MovieNode *root;
        int counter;
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        int opCount;
        void deleteArray();
        std::string titles[50];
        int numtitles;

        MovieNode *nil;

        // new functionality
        int LongestPath();
        //

        // check to see if anything needs to be done
        int isValid(MovieNode * node);
        //

        // fixing after changing the tree
        void rbAddFixup(MovieNode *x);
        void rbDeleteFixup(MovieNode *x);

        // rotate functions
        void leftrotate(MovieNode *x);
        //
        void rightrotate(MovieNode *x);
        //

        void rbtransplant(MovieNode *u, MovieNode *v);

    protected:
    
    private:

        void searchMovieTree(MovieNode *node, std::string title, bool rent, bool del);
        void print(MovieNode *node);
        int countMovieNodes(MovieNode *node);
        int LongestPath(MovieNode *node);
};

#endif // MOVIETREE_H


