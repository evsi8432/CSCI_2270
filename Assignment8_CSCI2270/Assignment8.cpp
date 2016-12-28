#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Graph.h"

using namespace std;

void printmenu(){
	cout<<"======Main Menu=====" << endl;
	cout<<"1. Print vertices" << endl;
	cout<<"2. Find districts" << endl;
	cout<<"3. Find shortest path" << endl;
	cout<<"4. Find shortest distance" << endl;
	cout<<"5. Extra credit" << endl;
	cout<<"6. Quit" << endl;
}

int main(int argc, char *argv[]){

    	ifstream inFile;
    	inFile.open(argv[1]);
    	string strLine;
    	string city;
    	string endcity;
    	int citynum = 0;
    	int weight = 0;
    	int endcitynum = 0;
    	int input = -1;

    	Graph graph;

    	getline(inFile, strLine);
    	stringstream cities(strLine);
    	getline(cities,city,',');
    	while(getline(cities, city, ',')){
        	graph.addVertex(city);
        	citynum++;
    	}

    	// go back to the original city
    	citynum = 0;

    	// find each of the other cities NAME from the rest of the file
    	while(getline(inFile,strLine)){
        	stringstream cities(strLine);
        	getline(cities,city,',');

        	// get the weight of each other city
        	while(getline(cities, endcity, ',')){
            		weight = atoi(endcity.c_str());
            		if(weight > -1){
                		graph.addEdge(graph.vertices[citynum].name,graph.vertices[endcitynum].name,weight);
            		}
            		endcitynum++;
        	}
        	endcitynum = 0;
        	citynum++;
    	}

    	string citystart;
    	string cityend;


    	while(input != 6){

        	printmenu();
        	cin >> input;
		cin.ignore();

        	if(input == 1){
            		graph.displayEdges();
        	}

        	if(input == 2){
            		graph.finddist();
        	}

        	if(input == 3){
            		cout << "Enter a starting city:" << endl;
            		getline(cin,citystart);
            		cout << "Enter an ending city:" << endl;
            		getline(cin,cityend);
            		graph.shortpath(cityend,citystart);
        	}

        	if(input == 4){
            		cout << "Enter a starting city:" << endl;
            		getline(cin,citystart);
            		cout << "Enter an ending city:" << endl;
            		getline(cin,cityend);
            		graph.shortdist(cityend,citystart);
        	}

        	if(input == 5){
            		cout << "Enter a starting city:" << endl;
            		getline(cin,citystart);
            		graph.extracredit(citystart);
        	}
    	}

   	cout << "Goodbye!" << endl;
    	return 0;
}


