#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <utility>
#include <functional>
using namespace std;
// Structure to represent a vertex in the graph
struct Vertex {
    int id;
    double distance;
    Vertex(int _id, double _distance) : id(_id), distance(_distance) {}
    };
    // Structure to represent an edge in the graph
struct Edge {
    int source;
    int destination;
    double weight;
    Edge(int _source, int _destination, double _weight) : source(_source), destination(_destination), weight(_weight) {}
    };
class Graph {
    int V;  // number of vertices
    vector<vector<Edge>> adjacencyList;
public:
    Graph(int v) : V(v), adjacencyList(v) {}
    // Add an edge to the graph
    void addEdge(int source, int destination, double weight) {
        adjacencyList[source].emplace_back(source, destination, weight);
        adjacencyList[destination].emplace_back(destination, source, weight);
    }
    // Dijkstra's algorithm implementation
    pair<double, vector<int>> dijkstra(int source, int target) {
        vector<double> distances(V, numeric_limits<double>::max());
        distances[source] = 0.0;
        // Create a min-heap priority queue of vertices (ordered by distance)
        priority_queue<Vertex, vector<Vertex>, function<bool(const Vertex&, const Vertex&)>> pq(
            [](const Vertex& v1, const Vertex& v2) {
                return v1.distance > v2.distance;
            }
        );
        // Add the source vertex to the priority queue
        pq.push(Vertex(source, 0.0));
        // Array to store the previous node in the shortest path
        vector<int> path(V, -1);
        // Dijkstra's algorithm loop
        while (!pq.empty()) {
            int u = pq.top().id;
            pq.pop();
            // Traverse all neighboring vertices of u
            for (const auto& edge : adjacencyList[u]) {
                int v = edge.destination;
                double weight = edge.weight;
                // If a shorter path is found, update the distance and enqueue the vertex
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    path[v] = u;
                    pq.push(Vertex(v, distances[v]));
                }
            }
        }
        //compute path to go to target
        vector<int> path_trace;
        int node = target;
        // Follow the path from the target vertex to the source vertex
        while (node != -1) {
            path_trace.push_back(node);
            node = path[node];
        }
        // Reverse the path to get the correct order
        reverse(path_trace.begin(), path_trace.end());
        // Return the distances and path array
        return make_pair(distances[target], path_trace);
    }

    // Trace the path from the source to the target vertex
    vector<int> getPath(int source, int target, const vector<int>& path) {
        vector<int> path_trace;
        int node = target;
        // Follow the path from the target vertex to the source vertex
        while (node != -1) {
            path_trace.push_back(node);
            node = path[node];
        }
        // Reverse the path to get the correct order
        reverse(path_trace.begin(), path_trace.end());
        return path_trace;
    }
};
/*int main() {
    int V = 28;  // total number of vertices (including the initial position and submission desk)
    Graph g(V);
 
    // Add edges to the graph
    // ...
 
    // Perform Dijkstra's algorithm from the initial position (0)
    pair<vector<double>, vector<int>> result = g.dijkstra(0,10);
    vector<double>& distances = result.first;
    vector<int>& path = result.second;
 
    // Print the shortest distances to all vertices
    for (int i = 0; i < V; ++i) {
        cout << "Distance to vertex " << i << ": " << distances[i] << endl;
    }
 
    // Trace the path from the source to a target vertex (e.g., vertex 10)
    int targetVertex = 10;
    vector<int> shortestPath = g.getPath(0, targetVertex, path);
 
    // Print the shortest path from the source to the target vertex
    cout << "Shortest path from source to vertex " << targetVertex << ":" << endl;
    for (int vertex : shortestPath) {
        cout << vertex << " -> ";
    }
    cout << endl;
 
    return 0;
}
*/
