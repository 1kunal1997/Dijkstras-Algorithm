#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

/* Defined to keep track of each path taken from a city.
Distance keeps track of the total distance travelled by
this path. City is the integer representation of the 
city the path ends at. Directions keeps track of all
cities passed on this path. */
struct Path {
    int distance;
    int city;
    vector<char> directions;
};
// Used to return the starting and ending points desired by the user.
struct Endpoints {
    int start;
    int dest;
};

const int CITIES = 9;
const int INF = INT_MAX;
/* 2D array to keep track of the distance between each city.
Ex: PATHS[i][j] is the distance from city i to j. INF means
you can't access that city. */
const int PATHS[CITIES][CITIES] = {{0, 4, INF, INF, INF, INF, INF, 8, INF},
                    {4, 0, 8, INF, INF, INF, INF, 11, INF},
                    {INF, 8, 0, 7, INF, 4, INF, INF, 2},
                    {INF, INF, 7, 0, 9, 14, INF, INF, INF},
                    {INF, INF, INF, 9, 0, 10, INF, INF, INF},
                    {INF, INF, 4, INF, 10, 0, 2, INF, INF},
                    {INF, INF, INF, 14, INF, 2, 0, 1, 6},
                    {8, 11, INF, INF, INF, INF, 1, 0, 7},
                    {INF, INF, 2, INF, INF, INF, 6, 7, 0}
                     };

// ***FUNCTION PROTOTYPES***

bool sortHelper (Path i, Path j);
Endpoints promptUser(); 
bool validPath(int p);
void makeDict(map<int,char> &c);
Path findPath(int s, int e);
void printResults(Path answer);
void update(vector<Path> &curr, vector<Path> &next); 
bool checkDone(vector<Path> o, Path ans);

// Used to map the integer and character representations of cities.
map<int,char> citydict;

int main() {

    makeDict(citydict);
    Endpoints e = promptUser();
    Path answer(findPath(e.start, e.dest));
    printResults(answer);

    return 0;
}

/* Asks the user for the starting and ending cities. 
Returns the cities as integers */ 
Endpoints promptUser() {
    char city1, city2;
    cout << "Enter the cities you want to start from and end at (A-I): ";
    cin >> city1 >> city2;
    return {(int)city1 - 65, (int)city2 - 65};
}

// Prints the shortest path and the distance to the screen.
void printResults(Path answer) {
    cout << "Shortest path: ";
    for (int i = 0; i < answer.directions.size(); i++)
         cout << answer.directions[i] << " ";
    cout << endl << "Distance: " << answer.distance << endl;
}

// Helper function for the sort function from algorithm library.
bool sortHelper (Path i, Path j) {
    return (i.distance < j.distance);
}

// Checks if the city is accessible from the current city.
bool validPath(int p) {
    if (p < INF && p != 0)
        return true;
    else
        return false;
}

// Creates the map for the cities.
void makeDict(map<int,char> &c) {
    for (int i = 0; i < CITIES; i++)
        c[i] = (char)(i + 65);
}

/* Checks if the city to travel to has been reached
by a shorter route. */
bool prevVisit(int d, int c) {
    return (c < d);
}

/* Updates the vector of paths, and orders them based on
their distances. */
void update(vector<Path> &curr, vector<Path> &next) {
    curr = next;
    next.clear();
    sort(curr.begin(), curr.end(), sortHelper);
}

/* Returns false if any of the current paths have a 
shorter path than the current answer's path. Else,
returns true, meaning we found the shortest path. */
bool checkDone(vector<Path> o, Path ans) {
    for(auto it = o.begin(); it != o.end(); it++)
        if (it->distance < ans.distance)
            return false;
    return true;
}

/* Returns the shortest path. Iterates through the current
paths ("order") to travel to accessible cities, builds the next 
set of paths ("nextorder"), and sorts them based on smallest 
distance. The "current" vector keeps track of the current shortest
distance to each city. Once the destination is reached, the Path 
is stored in ans, and we check if we are done. Ans is returned. */
Path findPath(int s, int e) {
    vector<Path> order(1), nextorder;
    vector<int> current(CITIES, INT_MAX);
    current[s] = 0;
    vector<char> start(1,citydict[s]);
    Path ans = {INT_MAX, e, start};
    order[0] = {0, s, start};
    bool done = false;

    // handles the case in which the start and end cities are the same.
    if (s == e)
        return {0, s, start};
    
    while(!done) {
        for(auto it = order.begin(); it != order.end(); it++) {
            int currdistance = it->distance;
            int currcity = it->city;
            vector<char> currpath = it->directions;
            for(int i = 0; i < CITIES; i++) {
                int cost = PATHS[currcity][i];
                int distance = currdistance + cost;
                if (validPath(cost) && !prevVisit(distance, current[i]) &&
                    distance < ans.distance) {
                    current[i] = distance;
                    vector<char> addpath = currpath;
                    addpath.push_back(citydict[i]);
                    if (i == e)
                        ans = {distance, i, addpath};
                    else
                        nextorder.push_back({distance, i, addpath});
                }
            }
        }
        update(order, nextorder);
        if (ans.distance != INF)
            done = checkDone(order, ans);
        
        // uncomment below to track the paths with print statements.
        /* cout << "NEXT SET!" << endl << "Current paths:" << endl;
        for(auto it = order.begin(); it != order.end(); it++) {
            for (int i = 0; i < it->directions.size(); i++)
                cout << it->directions[i] << " ";
            cout << "with a distance of " << it->distance << endl;
            if (it->distance < ans.distance)
                done = false;
        }
        if (ans.distance != INF) {
            cout << "Current shortest distance to destination:" << endl;
            for (int i = 0; i < ans.directions.size(); i++)
                cout << ans.directions[i] << " ";
            cout << "with a distance of " << ans.distance << endl;
        }
        cout << "Current shortest distances to each city are:" << endl;
        for (int i = 0; i < CITIES; i++)
            cout << current[i] << endl;
        */
    }
    return ans;
}