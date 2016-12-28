////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <json/json.h>
#include "MovieTree.h"


using namespace std;

void printmenu(){
	cout<<"======Main Menu=====" << endl;
	cout<<"1. Rent a movie" << endl;
	cout<<"2. Print the inventory" << endl;
	cout<<"3. Delete a movie" << endl;
	cout<<"4. Count the movies" << endl;
	cout<<"5. Count longest path" << endl;
	cout<<"6. Quit" << endl;
}

int main(int argc, char *argv[]){
//int main(){

	ifstream inFile;
	inFile.open(argv[1]);
	string strLine;
	int ranking;
	string title;
	int releaseYear;
	int quantity;
	MovieTree Tree;
	int counter;
	int countlong;
	while(!inFile.eof()){

		getline(inFile, strLine, ',');
		ranking = atoi(strLine.c_str());

		getline(inFile, strLine, ',');
		title = strLine;

		getline(inFile, strLine, ',');
		releaseYear = atoi(strLine.c_str());

		getline(inFile, strLine);
		quantity = atoi(strLine.c_str());

		Tree.addMovieNode(ranking, title, releaseYear, quantity);
	}

	int input = -1;
	string str = "";

	Tree.opCount++;
	Tree.isValid(Tree.root);

	while(input != 6){

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

			string newtitle;

			cout << "Enter title:" << endl;
			getline(cin,newtitle);
			Tree.rentMovie(newtitle);

		}

		if (input == 2){
			Tree.printMovieInventory();
		}

		if (input == 3){

			string newtitle;

			cout << "Enter title:" << endl;
			getline(cin,newtitle);
			Tree.deleteMovieNode(newtitle);
			Tree.isValid(Tree.root);

		}

		if (input == 4){

			counter = Tree.countMovieNodes();
			cout << "There are a total of " << counter << " movies." <<  endl;
			Tree.counter = 0;

		}

		if (input == 5){
			countlong = Tree.LongestPath();
			cout << "The tree is " << countlong << " nodes deep." <<  endl;
		}
	}

	cout << "Goodbye!" << endl;
  
	return 0;
}

