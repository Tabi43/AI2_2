#include "RoadMap.h"

/*Contructor*/
RoadMap::RoadMap(){
    /*Set the k-value (How many waypoint can 
    be connected to a single waypoint)*/
    k = 5;
}

/*Destructor*/
RoadMap::~RoadMap(){
    
}

/*This method takes a map obj which contains 
all waypoint used to build up the graph*/
void RoadMap::buildMap(map<string, vector<double>> waypoint){
    int number_of_nodes = (int)waypoint.size();
    dimension = number_of_nodes;
    //Dynamic allocation of the graph and set to zero each cell
    graph = new double*[number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++){
        graph[i] = new double[number_of_nodes];
        for(int j = 0; j < number_of_nodes; j++){
            graph[i][j] = -1.0;
        }
    }
    for (std::map<string, vector<double>>::iterator it = waypoint.begin(); it != waypoint.end(); ++it) {
        string wayPointName = it->first;
        vector<double> position = it->second;
        map<string, double> distances;
        for (std::map<string, vector<double>>::iterator et = waypoint.begin(); et != waypoint.end(); ++et) {
            string name = et->first;
            vector<double> pos = et->second;
            double dst = sqrt(pow(position[0] - pos[0], 2) + pow(position[1] - pos[1], 2));
            distances[name] = dst;
        }
        //dovrebbe essere k non 5       
        for(int i = 0; i < 5; i++){
            double min = INT_MAX;
            string index;
            for (std::map<string, double>::iterator d = distances.begin(); d != distances.end(); ++d) {
                if(min > d->second){
                    min = d->second;
                    index = d->first;
                }  
            }
            int row = parseWayPoint(wayPointName);
            int col = parseWayPoint(index);
            graph[row][col] = min;
            distances[index] = INT_MAX;
        }   
    }
}

vector<string> RoadMap::findPath(string from, string to){
    //from and to sono già waypoint in VisitSolver faremo landmark-waypoint closest
    //usare algoritmo di djikstra
    
    
}

/*Function which return the waypoint index by its name*/
int parseWayPoint(string wayPointName){
    string name = wayPointName.erase(0,2);
    std::istringstream iss(name);
    int result;
    iss >> result;
    return result;
}

bool RoadMap::isLinked(int a, int b){
    return graph[a][b] > 0;    
}
