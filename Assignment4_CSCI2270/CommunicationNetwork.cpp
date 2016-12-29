#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

CommunicationNetwork::CommunicationNetwork(int qs) {
	queueSize = qs;
	arrayQueue = new string[queueSize];
	queueHead = 0;
	queueTail = 0;
	head = new node;
	path = false;
	full = false;
} 

CommunicationNetwork::~CommunicationNetwork(){
	delete[] arrayQueue;
}

bool CommunicationNetwork::pathMade(){
	if(!path){
		cout<< "Build a network before attempting to transmit a message" <<endl;
	}
	return path;
}

void CommunicationNetwork::enqueue(string x){
  
  	arrayQueue[queueTail] = x;
  
  	if(queueTail == queueSize-1){
    		queueTail = 0;
	}
	else{
		queueTail++;
	}
	
  	if(queueTail == queueHead){
    		full = true;
  	}
	
	cout << "E: " << x << endl;
	cout << "H: " << queueHead << endl;	
	cout << "T: " << queueTail << endl;	
	cout << full << endl;

}

void CommunicationNetwork::dequeue(){

	if(path == false){
		cout<< "Build a network before attempting to transmit a message" <<endl;
	}
	else if(queueIsEmpty()){
		cout<< "Queue is empty."<< endl;
	}
	else{

		string temp = arrayQueue[queueHead];
	
		if(queueHead == queueSize-1){
			queueHead = 0;
		}
		else{
			queueHead++;
		}

		cout << "H: " << queueHead << endl;	
		cout << "T: " << queueTail << endl;	
	
		node *x;
		x = head;

		while(x->next != NULL){
			x -> message = temp;
			cout<< x->city <<" received "<< x->message <<endl;
			x = x-> next;
		}
		x = x->previous;
		x = x->previous;
		while(x->previous != NULL){
			x -> message = temp;
			cout<< x->city <<" received "<< x->message <<endl;
			x = x -> previous;
		}
		cout<< x->city <<" received "<< x->message <<endl;	
		full = false;
	}
}


void CommunicationNetwork::printQueue(){
	
	int head = queueHead;
	int tail = queueTail;
	bool again = full;
	
	while(head != tail or again == true){
		cout<<head<< ": " << arrayQueue[head]<<endl;
		if(head == queueSize - 1){
			head = 0;
		}
		else{
			head++;
		}
		again = false;
	}
}

void CommunicationNetwork::buildNetwork(){
	
	string startcities[] = {"Los Angeles","Phoenix","Denver","Dallas",
		"St. Louis","Chicago","Atlanta","Washington, D.C.",
		"New York","Boston"};
		
	int numcities = 10;
	node *x;
	x = head;
	x -> previous = NULL;
	int i = 0;
	while(i < numcities){
		x->city = startcities[i];
	        node *n1 = new node;
		x->next = n1;
        	n1->next = NULL;
        	n1->previous = x;
        	if (i == 9){
			tail = x;
		}
        	x = n1;
        	i++;
	}
   	path = true;
} 

void CommunicationNetwork::printPath(){
	cout << "===CURRENT PATH===" << endl;
	node *cities = head;
	while(cities->next != NULL){
		cout << cities->city;
		cities = cities->next;
		cout << " -> ";
		if(cities->next == NULL){
			cout << "NULL" << endl;
		}
	}
	cout << "==================" << endl;
}

bool CommunicationNetwork::queueIsFull(){
	if((queueTail == queueHead) and (full == true)){
		return true;
	}
	else{
		return false;
	}
}

bool CommunicationNetwork::queueIsEmpty(){ 
	if((queueTail == queueHead) and (full == false)){
		return true;
	}
	else{
		return false;
	}
}

void CommunicationNetwork::transmitMsg(string word){
	enqueue(word);
	if(queueIsFull()){
		while(!queueIsEmpty() and path){
			dequeue();
		}
	}
}
