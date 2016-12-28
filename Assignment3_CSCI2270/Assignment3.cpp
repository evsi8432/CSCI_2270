// Evan Sidrow
// Assignment 2
// Hoenigman

// This program builds a linked list of cities which can be 
// altered by the user. A message can be sent across the 
// cities

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

struct node{
	string city;
	string message;
	node *next;
};

node *createlist(string cities[], int numcities){
	node *x;
	node *head;
	x = new node;
	head = x;
	int i = 0;
	while(i < numcities){
		x->city = cities[i];
		node *n1 = new node;
		x->next = n1;
		n1->next = NULL;
		x = n1;
		i++;
	}
   return head;
} 

void printpath(node *cities, int numcities){
	cout << "===CURRENT PATH===" << endl;
	while(cities->next != NULL){
		cout << cities->city;
		cities = cities->next;
		cout << " -> ";
		if(cities->next == NULL){
			cout << " NULL" << endl;
		}
	}
	cout << "=================" << endl;
}

void printmenu(){
	cout<<"======Main Menu====="<<endl;
	cout<<"1. Build Network"<<endl;
	cout<<"2. Print Network Path"<<endl;
	cout<<"3. Transmit Message Coast-To-Coast"<<endl;
	cout<<"4. Add City"<<endl;
	cout<<"5. Delete City"<<endl;
	cout<<"6. Clear Network"<<endl;
	cout<<"7. Quit"<<endl;
}

void sendmessage(node *cities){
	node *head;
	head = new node;
	head = cities;
	
	ifstream inFile;
	inFile.open("messageIn.txt");
	string strLine;
	bool check = false;

	while(!inFile.eof()){
		while(cities->next != NULL){
			if(check){
				cities -> message = strLine;
				cout<<cities->city<<" received "<<cities->message<<endl;
			}
			cities = cities -> next;
		}
		check = true;
		inFile >> strLine;
		cities = head;
	}
}

void addcity(node *cities, string newcity, string oldcity){
	
	while(cities->next != NULL){
		if(oldcity == "First"){
			node *n1;
			n1 = new node;
			n1->city = newcity;
			n1->next = cities;
			cities = n1;
			break;
		}
		if(cities->city == oldcity){
			node *n1;
			n1 = new node;
			n1->city = newcity;
			n1->next = cities->next;
			cities->next = n1;
			break;
		}
		cities = cities -> next;
	}
}

void deletecity(node *cities, string delcity){
	
	while(cities->next != NULL){
		if(cities->next->city == delcity){
			node *n1;
			n1 = cities->next->next;
			delete cities->next;
			cities->next = n1;
			break;
		}
		cities = cities->next;
	}
}

void clear(node *cities){
	
	node *n1;
	
	while(cities->next != NULL){
		n1 = cities->next->next;
		delete cities->next;
		cities->next = n1;
	}
	
	delete cities;
}
		
	
		
int main(){
	
	string startcities[] = {"Los Angeles","Phoenix","Denver","Dallas",
		"St. Louis","Chicago","Atlanta","Washington, D.C.",
		"New York","Boston"};
	
	int numcities = 10;
	int input = 0;
	string str;
	
	node *cities;
	cities = new node;
	cities -> next = NULL;
	

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
			cities = createlist(startcities, numcities);
			printpath(cities,numcities);
		}
		else if (input == 2){
			printpath(cities,numcities);
		}
		else if (input == 3){
			sendmessage(cities);
		}
		else if (input == 4){
			string newcity;
			string oldcity;	
	
			cout << "Enter a city name: " << endl;
			getline(cin,newcity);
	
			cout << "Enter a previous city name: " << endl;
			getline(cin, oldcity);
			
			addcity(cities, newcity, oldcity);
		}
		else if (input == 5){
			string delcity;	
	
			cout << "Enter a city name: " << endl ;
			getline(cin,delcity);
			
			deletecity(cities, delcity);
		}
		else if (input == 6){
			clear(cities);
		}
	}	
	cout << "Goodbye!" << endl;
}
