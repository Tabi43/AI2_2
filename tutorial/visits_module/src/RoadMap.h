#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

class RoadMap{
    public:
        RoadMap();
        ~RoadMap();
        
        void buildMap(map<string, vector<double>> waypoint);
        vector<string> findPath(string from, string to);
        
    private:
        double** graph;
        int dimension;
        double k;

        bool isLinked(int a, int b);

};