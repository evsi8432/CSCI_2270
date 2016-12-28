#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    std::vector<adjVertex> adj;
    bool visited;
    vertex *prev;
    int district;
    int distance;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void shortpath(std::string start, std::string ending);
        void finddist();
        void shortdist(std::string startcity,std::string endcity);
        void extracredit(std::string start);
        bool validpath(std::string startcity,std::string endcity);
        std::vector<vertex> vertices;

    protected:
    private:
        //vector<edge> edges;
        //std::vector<vertex> vertices;

};

#endif // GRAPH_H
