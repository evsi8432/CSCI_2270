#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "CommunicationNetwork.h"

using namespace std;



void printmenu(){
	cout<<"======Main Menu====="<<endl;
	cout<<"1. Build Network"<<endl;
	cout<<"2. Print Network Path"<<endl;
	cout<<"3. Enqueue"<<endl;
	cout<<"4. Dequeue"<<endl;
	cout<<"5. Print Queue"<<endl;
	cout<<"6. Send Entire Message"<<endl;
	cout<<"7. Quit"<<endl;
}

int main(){
	
	ifstream inFile;
    inFile.open("messageIn.txt");
    string strLine;
	
	CommunicationNetwork Network(10);
	
	int input = 0;
  string str = "";
	
	while(input != 7){
		
		printmenu();
    cin >> str;
    if(str.size() > 1){
      input = 0;
    }
    else{
      input = atoi(str.c_str());
    }
		cin.ignore();
		
		if (input == 1){
			Network.buildNetwork();
			Network.printPath();
		}
		if (input == 2){
			Network.printPath();
		}
		if (input == 3){
			if(Network.queueIsFull()){
				cout<<"Queue is full."<<endl;
			}
			else if(inFile.eof()){
				cout<<"No more words to queue."<<endl;
			}
			else{
				inFile >> strLine;
				Network.enqueue(strLine);
			}
		}
		if (input == 4){
			Network.dequeue();
		}
		if (input == 5){
			Network.printQueue();
		}
		if (input == 6){
			inFile.close();
			inFile.open("messageIn.txt");
			while(!inFile.eof()){
				inFile >> strLine; 
				if(!inFile.eof()){
					Network.transmitMsg(strLine);
				}
			}
			while(!Network.queueIsEmpty()){
				Network.dequeue();
			}
		}	
	}	
	cout << "Goodbye!" << endl;
	return 0;
}
