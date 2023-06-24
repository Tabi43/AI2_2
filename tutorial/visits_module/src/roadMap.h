#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <utility>
#include <functional>
#include <map>
#include <climits>
#include <sstream>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int source;
    int destination;
    double weight;
    Edge(int _source, int _destination, double _weight) : source(_source), destination(_destination), weight(_weight) {}
};

class Graph {
    public:
        Graph(int n);
        ~Graph();

        /*Minimun path from source to target*/
        pair<double, vector<string>> dijkstra(string source, string target);
        void buildRoadMap(map<string, vector<double>> waypoint);
        void print();

    private:

        int number_of_vertices;  // number of vertices
        vector<vector<Edge>> adjacencyList;
        int k;

        int parseWayPoint(string wayPointName);
        void addEdge(int source, int destination, double weight); 
        string convertToWayPoint(int n); 
};