// Evan Sidrow
// Assignment 2
// Hoenigman

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

struct wordcount{
    int number;
    string word;
};

void BubbleSort(wordcount *array, int arraysize){
	wordcount temp;
	bool end = false;
	while(end == false){
		end = true;
		for(int i = 0; i < arraysize; i++){
			if(array[i].number < array[i+1].number){
				temp = array[i];
				array[i] = array[i+1];
				array[i+1] = temp;
				end = false;
			}
		}
	}
}

wordcount *doublearray(wordcount *array, int size){
	
	wordcount empty;
	empty.number = 0;
	empty.word = ' ';
	
	wordcount *a1=array;
	wordcount *a2=array;
	
		a2 = new wordcount[size*2];
	
		for(int i = 0; i < size; i++){
			a2[i] = a1[i];
			a2[size+i] = empty;
		}
	
	delete[] a1;
	return a2;
}

bool checkword(string word0, string avoid[]){
  
	for(int i = 0; i < 50; i++){
		if (word0 == avoid[i]){
			return true;
		}
	}
	return false;		
}	
	
	
int main(int argc, char *argv[]){
	
	wordcount empty;
	empty.number = 0;
	empty.word = ' ';
	
	string avoid[] = {"the","be","to","of","and","a","in","that",
		"have","i","it","for","not","on","with","he","as","you",
		"do","at","this","but","his","by","from","they","we","say",
		"her","she","or","an","will","my","one","all","would","there",
		"their","what","so","up","out","if","about","who","get","which","go","me"}; 
	
	int totalwords = 0;
	
	bool checkcommon;
	
	int numwords = 0;
	
	int arraysize = 100;
	
	bool addentry = true;
	
	int numdoubles = 0;
	
	wordcount *wordarray = new wordcount[arraysize];
	
	for(int i = 0; i < 100; i++){
		wordarray[i] = empty;
	}
	
	ifstream inFile;
    inFile.open(argv[1]);
    string strLine;
    
    while(!inFile.eof()){

		inFile >> strLine;
		
		checkcommon = checkword(strLine,avoid);
		
		if(checkcommon == false){
			
		totalwords ++;
			
			for(int a = 0; a < numwords; a++){
				if (wordarray[a].word == strLine){
					wordarray[a].number ++;
					addentry = false;
				}
			}
			if (addentry == true){
				if (numwords >= arraysize){
					wordarray = doublearray(wordarray, arraysize);
					arraysize = arraysize * 2;
					numdoubles ++;
				}
				wordarray[numwords].number ++; 
				wordarray[numwords].word = strLine;
				numwords ++;
			}
			addentry = true;
		}
	}
	
	BubbleSort(wordarray,numwords);
	
	int n = atoi(argv[2]);
	
	for (int k = 0; k < n; k++){
		cout << wordarray[k].number << " - " << wordarray[k].word << endl;
	}
	cout<<"#"<<endl;
	cout<<"Array doubled: "<<numdoubles<<endl;
	cout<<"#"<<endl;
	cout<<"Unique non-common words: "<<numwords<<endl;
	cout<<"#"<<endl;
	cout<<"Total non-common words: " << totalwords << endl;
	
}
