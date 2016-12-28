#include "Graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}

bool Graph::validpath (string startcity, string endcity){
    bool startexist = false;
    bool endexist = false;
    vertex origin;
    vertex destination;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == startcity){
            startexist = true;
            origin = vertices[i];
        }
        if(vertices[i].name == endcity){
            endexist = true;
            destination = vertices[i];
        }
    }
    if(!startexist or !endexist){
        cout << "One or more cities doesn't exist" << endl;
        return false;
    }
    if(origin.district != destination.district){
        cout << "No safe path between cities" << endl;
        return false;
    }
    if(origin.district == -1){
        cout << "Please identify the districts before checking distances" << endl;
        return false;
    }

    return true;

}

void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.district = -1;
        v.prev = NULL;
        v.visited = false;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    int k = 0;
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<< vertices[i].district<< ":" <<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(vertices[i].name != vertices[i].adj[j].v->name){
                k++;
                cout<<vertices[i].adj[j].v->name;
                if (k != vertices[i].adj.size()-1){
                        cout<<"***";
                }
            }
        }
        cout<<endl;
        k = 0;
    }
}

void Graph::finddist(){
    bool done = false;
    int dist = 1;
    vertex *Q[10];
    int head = 0;
    int tail = 0;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].visited = false;
    }

    vertex *start = &vertices[0];
    start->visited = true;
    start->district = dist;

    while(!done){
        Q[tail] = start;
        tail++;
        while(head != tail){
            for(int i = 0; i < Q[head]->adj.size(); i++){
                vector <adjVertex> a = Q[head]->adj;
                if(a[i].v->visited == false){
                    a[i].v->visited = true;
                    a[i].v->district = dist;
                    Q[tail] = a[i].v;
                    tail++;
                }
            }
            head++;
        }
        head = 0;
        tail = 0;
        done = true;
        for(int i = 0; i < vertices.size(); i++){
            if(vertices[i].visited == false){
                start = &vertices[i];
                dist++;
                done = false;
                break;
            }
        }
    }
}


void Graph::shortpath(string startingCity, string endingCity){

    if(validpath(startingCity, endingCity)){

    vertex *current;
    vertex *Q[10];
    int head = 0;
    int tail = 0;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].visited = false;
        vertices[i].prev = NULL;
        if(vertices[i].name == startingCity){
            vertices[i].visited = true;
            vertices[i].prev = NULL;
            vertices[i].distance = 0;
            Q[0] = &vertices[i];
            tail++;
        }
    }

    while(Q[head]->name != endingCity){
        for(int i = 0; i < Q[head]->adj.size(); i++){
            vector <adjVertex> a = Q[head]->adj;
            if(a[i].v->visited == false){
                a[i].v->visited = true;
                a[i].v->distance = Q[head]->distance + 1;
                a[i].v->prev = Q[head];
                Q[tail] = a[i].v;
                tail++;
            }
        }
        head++;
    }

    current = Q[head];

    cout << current->distance;

    while(current != NULL){
        cout<< "," << current->name;
        current = current->prev;
    }

    cout << endl;
    }
}

void Graph::shortdist(string startcity,string endcity){
    int dist = 0;
    vertex *start;
    vertex *finish;
    vertex *minnodes;
    vertex *minnodef;
    if(validpath(startcity, endcity)){
        vertex *current;
        vertex *destination;
        vertex *solved[10];
        int head = 0;
        int tail = 0;

        for(int i = 0; i < vertices.size(); i++){
            vertices[i].visited = false;
            vertices[i].distance = INT_MAX;
            vertices[i].prev = NULL;
            if(vertices[i].name == startcity){
                vertices[i].visited = true;
                vertices[i].distance = 0;
                solved[tail] = &vertices[i];
                tail++;
            }
            if(vertices[i].name == endcity){
                destination = &vertices[i];
            }
        }

        while(destination->visited == false){
            int mindist = INT_MAX;
            for(int i = 0; i < tail; i++){
                for(int j = 0; j < solved[i]->adj.size(); j++){
                    finish = solved[i]->adj[j].v;
                    start = solved[i];
                    if(finish->visited == false){
                        dist = start->adj[j].weight + start->distance;
                        if(dist < mindist){
                            mindist = dist;
                            minnodes = start;
                            minnodef = finish;
                        }
                    }
                }
            }
            solved[tail] = minnodef;
            minnodef->visited = true;
            minnodef->distance = mindist;
            minnodef->prev = minnodes;

            tail++;
        }

        cout<< destination->distance;

        while(destination != NULL){
            cout<< "," << destination->name;
            destination = destination->prev;
        }

        cout << endl;
    }
}

void Graph::extracredit(string start){

if(validpath(start,start)){

int mindist = INT_MAX;
int distance = 0;
int j = 0;
int test = 0;
int mintest = INT_MAX;
int myints[9];
int solution[9];
int starterind;
vertex *starter;

for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].name != start){
        myints[j] = i;
        j++;
    }
    else{
        starter = &vertices[i];
        starterind = i;
    }
}


while(next_permutation(myints,myints+9)){
    distance += starter->adj[myints[0]].weight;
    for(int i = 0; i < 9; i++){
        if(i == 8){
            distance += vertices[starterind].adj[myints[i]].weight;
        }
        else{
            distance += vertices[myints[i]].adj[myints[i+1]].weight;
        }
    }
    if(distance < mindist){
        mindist = distance;
        mintest = test;
        for(int k = 0; k < 9; k++){
            solution[k] = myints[k];
        }
    }
    distance = 0;
}

cout<< mindist << endl;

cout<< mindist;

cout << "," << starter->name;

for(int k = 0; k < 9; k++){
    cout<< "," << vertices[solution[k]].name;
}

cout << "," << starter->name;
cout << endl;

}
}
