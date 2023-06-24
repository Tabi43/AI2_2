#include "roadMap.h"

// Structure to represent a vertex in the graph
struct Vertex {
    int id;
    double distance;
    Vertex(int _id, double _distance) : id(_id), distance(_distance) {}
};

//Structure to represent a waypoint
struct Waypoint {
    int index;
    double x;
    double y;
    double theta;
    Waypoint(int _index, double _x, double _y, double _theta) : index(_index), x(_x), y(_y), theta(_theta) {} 
};

Graph::Graph(int n){
    number_of_vertices = n;        
    adjacencyList = vector<vector<Edge>>(number_of_vertices);
    k = 6;
}

Graph::~Graph(){

}

// Add an edge to the graph
void Graph::addEdge(int source, int destination, double weight) {
    adjacencyList[source].emplace_back(source, destination, weight);
}

// Dijkstra's algorithm implementation
pair<double, vector<string>> Graph::dijkstra(string s, string t) {
    int source = parseWayPoint(s);
    int target = parseWayPoint(t);
    vector<double> distances(number_of_vertices, numeric_limits<double>::max());
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
    vector<int> path(number_of_vertices, -1);
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
    vector<string> path_trace;
    int node = target;
    // Follow the path from the target vertex to the source vertex
    while (node != -1) {
        path_trace.push_back(convertToWayPoint(node));
        node = path[node];
    }
    // Reverse the path to get the correct order
    reverse(path_trace.begin(), path_trace.end());
    // Return the distances and path array
    return make_pair(distances[target], path_trace);
}

void Graph::print() {
    for(int i = 0; i < number_of_vertices; i++){
       for(int j = 0; j < (int)adjacencyList[i].size(); j++){
            cout << adjacencyList[i][j].source << " " << adjacencyList[i][j].destination << " " << adjacencyList[i][j].weight << endl;
       }
    }
}

/*Method to create the graph*/
void Graph::buildRoadMap(map<string, vector<double>> waypoint){
    int number_of_nodes = (int)waypoint.size();
    for (std::map<string, vector<double>>::iterator it = waypoint.begin(); it != waypoint.end(); ++it) {
        string wayPointName = it->first;
        vector<double> position = it->second;
        map<string, double> distances;
        for (std::map<string, vector<double>>::iterator et = waypoint.begin(); et != waypoint.end(); ++et) {
            string name = et->first;
            vector<double> pos = et->second;
            double dst = INT_MAX; 
            if(name != wayPointName) dst = sqrt(pow(position[0] - pos[0], 2) + pow(position[1] - pos[1], 2));
            distances[name] = dst;
        }      
        
        // Order the distances map by value (ascending order)
        vector<pair<string, double>> sortedDistances(distances.begin(), distances.end());
        sort(sortedDistances.begin(), sortedDistances.end(),
            [](const pair<string, double>& a, const pair<string, double>& b) {
                return a.second < b.second;
            });

        // Take the first k nearest waypoints and add edges to the graph
        int count = 0;
        for (const auto& pair : sortedDistances) {
            if (count >= k) break;
            string index = pair.first;
            int source = parseWayPoint(wayPointName);
            int destination = parseWayPoint(index);
            addEdge(source, destination, distances[index]);
            count++;
        }

    }
} 

/*Function which return the waypoint index by its name*/
int Graph::parseWayPoint(string wayPointName){
    string name = wayPointName.erase(0,2);
    std::istringstream iss(name);
    int result;
    iss >> result;
    return result;
}

string Graph::convertToWayPoint(int n) {
    std::string result = "wp" + std::to_string(n);
    return result;
}
