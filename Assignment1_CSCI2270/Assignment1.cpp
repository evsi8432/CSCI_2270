// Evan Sidrow
// Assignment 1
// Hoenigman

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// make a struct to describe what it is that we are selling
struct item{
    int price;
    string object;
    bool sell;
};

int main(int argc, char *argv[]){

	// initialize a counter
	int counter = 0;
	
	// initialize dummy variables to hold the current item's
	// price, type, and whether it is being sold or bought.
	string object0;	
	bool sell0;
	int price0;
	
	// make an array of the items
	item array[100];
	
	// right now we have no entries in this array of items
	int i = 0;
	
	// this will tell us whether or not to add to the array
	bool add = true;
	
	// get the command line arguement to be opened by the file reading
	// tool and get a variable (strLine) to hold strings
	ifstream inFile;
    inFile.open(argv[1]);
    string strLine;
        
	// read stuff until we get to the end of the file
    while(!inFile.eof()){
		
		// we will usually add to the array with a new unsold
		// item unless we tell the program otherwise.
		add = true;
		
		// read a line and save the first part as an object
    getline(inFile, strLine, ',');
    // only continue if we got something
    if(!inFile.eof()){
		object0 = strLine;
		
		// save the next part as whether it is bought or sold
		getline(inFile, strLine, ',');
		if(strLine == " wanted"){
			sell0 = false;
		}
		else if(strLine == " for sale"){
			sell0 = true;				
		}
		
		// save the final part of the line as the price
    getline(inFile, strLine, ' ');
    getline(inFile, strLine, '\n');
    price0 = atoi(strLine.c_str());
            
    // reading in the line was one operation
    counter += 1;
            
    //now check against our array of unsold items 
    for(int j = 0; j < i; j++){
				
			//each comparison is an operation
			counter += 1;
			
			// this if statement is that comparison
			if((object0 == array[j].object) and (sell0 != array[j].sell) and ((sell0 == true and price0 <= array[j].price) or (sell0 == false and price0 >= array[j].price))){
				
				// now list what was sold if it was
				cout << array[j].object << " " << min(array[j].price,price0) << endl;
				
				// our array is now smaller by one
				i += -1;
				
				// now shift the array back
				for(; j <= i; j++){
					array[j] = array[j+1];
					// this also counts as an operation
					counter += 1;
				}
				// now we don't need to add it to the array
				add = false;
			}
		}		
		// but if we do need to add it..
		if (add == true){	
			// ...add the darn item in there...			
			array[i].sell = sell0;
			array[i].price = price0;
			array[i].object = object0;		
			// ...and now our array is one bigger.
			i += 1;   
		}
  }
	}
	// now seperate our sections. we are out of the while loop
	// now.
	cout << "#" << endl;
	// This is just printing out what is left in our array.
	for(int k = 0; k < i; k++){
		if(array[k].sell == true){
		cout << array[k].object << ", " << "for sale" << ", " << array[k].price << endl;
		} 
		else{
		cout << array[k].object << ", " << "wanted" << ", " << array[k].price << endl;
		} 	
	}
	// And finally, we print out the final score on our
	// counter. All done!
	cout << "#" << endl;
	cout << "operations:"<< counter << endl;
}
