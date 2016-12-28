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
	warning = false;
} 

CommunicationNetwork::~CommunicationNetwork(){
	delete[] arrayQueue;
}

void CommunicationNetwork::enqueue(string x){
		if(queueTail == queueSize-1){
			arrayQueue[queueTail] = x;
			queueTail = 0;
		}
		else{
			arrayQueue[queueTail] = x;
			queueTail ++;
		}
	if((queueTail == queueHead-1)or(queueTail == 8)){
		warning = true;
	}
	
	cout << "E: " << x << endl;
	cout << "H: " << queueHead << endl;	
	cout << "T: " << queueTail << endl;	

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
}
	warning = false;
}


void CommunicationNetwork::printQueue(){
	
	int head = queueHead;
	int tail = queueTail;
	bool again = warning;
	
	while(head != tail or again == true){
		cout<<head<< ": " << arrayQueue[head]<<endl;
		if(queueHead == queueSize){
			head = 0;
		}
		else{
			head ++;
		}
		if (again == true){
			again = false;
			tail = 10;
		}
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
	if((queueTail == queueHead)and(warning == true)){
		return true;
	}
	else{
		return false;
	}
}

bool CommunicationNetwork::queueIsEmpty(){ 
	if((queueTail == queueHead)and(warning == false)){
		return true;
	}
	else{
		return false;
	}
}

void CommunicationNetwork::transmitMsg(string word){
	bool full = queueIsFull();
	if(full){
		while(!queueIsEmpty()){
			dequeue();
		}
	}
	enqueue(word);
}
