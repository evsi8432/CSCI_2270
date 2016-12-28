#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H
#include <string>

struct node{

    std::string city;
    std::string message; //intended to hold one word
    node *next;
    node *previous;

};

class CommunicationNetwork
{
    public:
        CommunicationNetwork(int);
        virtual ~CommunicationNetwork();
        //circular queue methods
        void enqueue(std::string);
        void dequeue(); //should send through network, call transmit msg
        void printQueue();
        void buildNetwork();
        void printPath();
        bool queueIsFull(); //send when full
        bool queueIsEmpty();
        bool pathMade();
        void transmitMsg(std::string);

    protected:
    
    private:
        node *head;
        node *tail;
        int queueSize;
        int queueHead;
        int queueTail;
        std::string *arrayQueue;
        bool path;
        bool full;
};

#endif // COMMUNICATIONNETWORK_H
