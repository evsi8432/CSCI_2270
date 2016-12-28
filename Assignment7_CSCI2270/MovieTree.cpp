#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <json/json.h>
#include "MovieTree.h"


using namespace std;

MovieTree::MovieTree(){
  nil = new MovieNode;
	nil -> parent = NULL;
	nil -> leftChild = NULL;
	nil -> rightChild = NULL;
	nil -> ranking = 0;
	nil -> title = "nil";
	nil -> year = 0;
	nil -> quantity = 100000;
	nil -> isRed = false;
	root = nil;
	counter = 0;
	opCount = 0;
	numtitles = 0;
}

MovieTree::~MovieTree(){

}

void MovieTree::print(MovieNode *root){
  
	if(root->leftChild!= nil){
		print(root->leftChild);
	}
  
	cout << "===========" << endl;
  	cout << "Ranking:" << root->ranking << endl;
  	cout << "Title:" << root->title << endl;
  	cout << "Year:" << root->year << endl;
	cout << "Quantity:" << root->quantity<< endl;
  
 	if(root->rightChild!=nil){
    		print(root->rightChild);
  	}
  
	return;
  
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity){

	titles[numtitles] = title;

 	numtitles++;

	opCount++;

	MovieNode *x = root;
	MovieNode *y = NULL;
	MovieNode *n1 = new MovieNode;
	n1 -> parent = nil;
	n1 -> leftChild = nil;
	n1 -> rightChild = nil;
	n1 -> ranking = ranking;
	n1 -> title = title;
	n1 -> year = releaseYear;
	n1 -> quantity = quantity;
	n1 -> isRed = true;

	if(root == nil){
		root = n1;
		root->parent = nil;
	}
	else{
		while(x != nil){
			y = x;

			if(title > x->title){
				x = x->rightChild;
			}
			else{
				x = x->leftChild;
			}
		}
		n1->parent = y;
		if(y->title > n1->title){
			y->leftChild = n1;
		}
		else{
			y->rightChild = n1;
		}
	}
	root->isRed = false;
	rbAddFixup(n1);
	isValid(root);
	return;
}

void MovieTree::searchMovieTree(MovieNode *x, string title, bool rent, bool del){
	if(x == nil){
		cout << "Movie not found." << endl;
		opCount--;
    		return;
	}
    
	else if(x->title == title){
		if(rent == true){
			x->quantity += -1;
      			cout << "Movie has been rented." << endl;
      			cout << "Movie Info:" << endl;
      			cout << "===========" << endl;
      			cout << "Ranking:" << x->ranking << endl;
      			cout << "Title:" << x->title << endl;
      			cout << "Year:" << x->year << endl;
      			cout << "Quantity:" << x->quantity<< endl;
    		}
    		///////////////Delete////////////
   		if((x->quantity == 0) or (del == true)){

      			if(x->quantity == 0){
        			opCount++;
      			}
        
      			MovieNode *y = x;
      			MovieNode *z = x;
      			bool y_org = y->isRed;
      			if(x->leftChild == nil){
        			z = x->rightChild;
				rbtransplant(x, x->rightChild);
      			}
      			else if(x->rightChild == nil){
        			z = x->leftChild;
        			rbtransplant(x, x->leftChild);
      			}
      			else{
        			y = x->rightChild;
        			while(y->leftChild != nil){
          				y = y->leftChild;
       				}
        			y_org = y->isRed;
        			z = y->rightChild;
        			if(y->parent == x){
          				z->parent = y;
        			}
        			else{
          				rbtransplant(y,y->rightChild);
          				y->rightChild = x->rightChild;
          				y->rightChild->parent = y;
        			}
        			rbtransplant(x,y);
        			y->leftChild = x->leftChild;
        			y->leftChild->parent = y;
        			y->isRed = x->isRed;
      			}
      			if(y_org == false){
        			rbDeleteFixup(z);
      			}
    		}
		return;
  	}
  	else{
    		if(x->title > title){
      			searchMovieTree(x->leftChild, title, rent, del);
    		}
    		else{
      			searchMovieTree(x->rightChild, title, rent, del);
    		}
	}
	return;
}

int MovieTree::countMovieNodes(MovieNode *root){
	
	if(root->leftChild != nil){
    		countMovieNodes(root->leftChild);
  	}
    
  	counter++;
  
  	if(root->rightChild != nil){
    		countMovieNodes(root->rightChild);
  	}
  
  	return counter;
}

void MovieTree::findMovie(string title){
	searchMovieTree(root,title, false, false);
}

void MovieTree::rentMovie(string title){
	searchMovieTree(root,title, true, false);
	opCount++;
}

void MovieTree::deleteMovieNode(string title){
	searchMovieTree(root,title, false, true);
	opCount++;
}

int MovieTree::countMovieNodes(){
	
  int counter = countMovieNodes(root);

  opCount++;

	return counter;
}


void MovieTree::printMovieInventory(){
  
	print(root);  
  
	opCount++;
  
	return;
}

//////////////////////// new material///////////////////////////////////

int MovieTree::isValid(MovieNode *node){
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1;

    else
    {
        // First check for consecutive red links.
        if (node->isRed)
        {
            if(node->leftChild->isRed || node->rightChild->isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }

        // Check for valid binary search tree.
        if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0))
        {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }

        // Determine the height of left and right children.
        lh = isValid(node->leftChild);
        rh = isValid(node->rightChild);

        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh)
        {
            cout << "This tree contains a black height violation" << endl;
            cout << "left height: " << lh << endl;
            cout << "right height: " << rh << endl;
            return 0;
        }

        // If neither height is zero, increment if it if black.
        if (lh != 0 && rh != 0)
        {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }

        else
            return 0;

    }
}

int MovieTree::LongestPath(){
	int longcount = LongestPath(root);
	opCount++;
	return longcount;
}

int MovieTree::LongestPath(MovieNode *node){
	int counter = 1;
	int counterleft = 0;
	int counterright = 0;
	if(node->leftChild != nil){
		counterleft = LongestPath(node->leftChild);
	}
	if(node->rightChild != nil){
		counterright = LongestPath(node->rightChild);
	}
	if(counterleft > counterright){
		counter += counterleft;
	}
	else{
		counter += counterright;
	}
	return counter;
}

void MovieTree::rightrotate(MovieNode *node){
  MovieNode *x = node;
  MovieNode *y = x->leftChild;
  x->leftChild = y->rightChild;
  if (y->rightChild != nil){
    y->rightChild->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nil){
    root = y;
  }
  else if (x == x->parent->leftChild){
    x->parent->leftChild = y;
  }
  else{
    x->parent->rightChild = y;
  }
  y->rightChild = x;
  x->parent = y;
}

void MovieTree::leftrotate(MovieNode *node){
  MovieNode *x = node;
  MovieNode *y = x->rightChild;
  x->rightChild = y->leftChild;
  if (y->leftChild != nil){
    y->leftChild->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nil){
    root = y;
  }
  else if (x == x->parent->leftChild){
    x->parent->leftChild = y;
  }
  else{
    x->parent->rightChild = y;
  }
  y->leftChild = x;
  x->parent = y;
}

void MovieTree::rbAddFixup(MovieNode *x){
  MovieNode *y = nil;
  while ((x != root) and (x->parent->isRed == true)){
    if (x->parent == x->parent->parent->leftChild ) {
      y = x->parent->parent->rightChild;
      if ( y->isRed == true ) {
        x->parent->isRed = false;
        y->isRed = false;
        x->parent->parent->isRed = true;
        x = x->parent->parent;
      }
      else{
        if ( x == x->parent->rightChild ){
          x = x->parent;
          leftrotate(x);
        }
        x->parent->isRed = false;
        x->parent->parent->isRed = true;
        rightrotate(x->parent->parent);
      }
    }
    else{
      y = x->parent->parent->leftChild;
      if(y->isRed == true){
        x->parent->isRed = false;
        y->isRed = false;
        x->parent->parent->isRed = true;
        x = x->parent->parent;
      }
      else{
        if ( x == x->parent->leftChild ){
          x = x->parent;
          rightrotate(x);
        }
        x->parent->isRed = false;
        x->parent->parent->isRed = true;
        leftrotate(x->parent->parent);
      }
    }
  }
  root->isRed = false;
}

void MovieTree::rbDeleteFixup(MovieNode *x){
  MovieNode *w = nil;
  while((x != root) and (x->isRed = false)){
    if(x == x->parent->leftChild){
      w = x->parent->rightChild;
      if(w->isRed == true){
        w->isRed = false;
        x->parent->isRed = true;
        leftrotate(x->parent);
        w = x->parent->rightChild;
      }
      else if((w->leftChild->isRed == false) and (w->rightChild->isRed == false)){
        w->isRed = true;
        x = x->parent;
      }
      else{
        if(w->rightChild->isRed == false){
          w->leftChild->isRed = false;
          w->isRed = true;
          rightrotate(w);
          w = x->parent->rightChild;
        }
        else{
          w->isRed = x->parent->isRed;
          x->parent->isRed = false;
          w->rightChild->isRed = false;
          leftrotate(x->parent);
          x = root;
        }
      }
    }
    else{
      w = x->parent->leftChild;
      if(w->isRed == true){
        w->isRed = false;
        x->parent->isRed = true;
        rightrotate(x->parent);
        w = x->parent->leftChild;
      }
      else if((w->rightChild->isRed == false) and (w->leftChild->isRed == false)){
        w->isRed = true;
        x = x->parent;
      }
      else{
        if(w->leftChild->isRed == false){
          w->rightChild->isRed = false;
          w->isRed = true;
          leftrotate(w);
          w = x->parent->leftChild;
        }
        else{
          w->isRed = x->parent->isRed;
          x->parent->isRed = false;
          w->leftChild->isRed = false;
          rightrotate(x->parent);
          x = root;
        }
      }
    }
  }
  x->isRed == false;
}

void MovieTree::rbtransplant(MovieNode *u, MovieNode *v){
  if(u->parent == nil){
    root = v;
  }
  else if(u == u->parent->leftChild){
    u->parent->leftChild = v;
  }
  else{
    u->parent->rightChild =v;
  }
  v->parent = u->parent;
}

