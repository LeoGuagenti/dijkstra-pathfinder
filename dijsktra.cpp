/**
 * @file main.cpp
 * 
 * @author Leo Guagenti
 * @date 4/24/19
 * @brief Implementation of Dijksra's shortest path algorithm
 * 
 * Project 5 - CS3610
 * Implementation of Dijksra's shortest path algorithm without using a minheap
*/

#include <iostream>
#include <string>
#include <limits.h>
#include <vector>
#include <unordered_set>
using namespace std;

// large number constant to imitate infinity
const int INFI = LONG_MAX;

//structure to hold the best known path to a given vertex and its cost
struct PATH {
    int cost;
    vector<int> path;
};

/**
 * dijkstra
 * Finds the shortest path to each given vertex given a starting vertex 
 * and stores the paths and costs in an array
 * 
 * @param verticies the number of total verticies
 * @param graph an adjacency matrix of edge costs
 * @param source the location at which each path found will start
 * @param bestPaths an array of the best possible path to each given vertex
*/
void dijkstra(int verticies, vector<vector<int>>& graph, int source, PATH bestPaths[]){
    unordered_set<int> visited; //list of verticies visited

    //sets all the best costs to infinity
    for(int i = 0; i < verticies; i++){
        bestPaths[i].cost = INFI;
    }

    bestPaths[source].cost = 0; //inital bestPath cost is zero because it is the source
    bestPaths[source].path.push_back(source);

    //iterate through each vertex
    for(int numVisited = 0; numVisited < verticies; numVisited++){
        int lowestCost = INFI;
        int lowestCostVertex = -1; //"undefined" initally
        
        //determine vertex with lowest path cost
        for(int vertex = 0; vertex < verticies; vertex++){
            //determine if an unvisited vertex's cost is lower than the current lowestCost
            if((visited.count(vertex) == 0) && (bestPaths[vertex].cost < lowestCost)){
                lowestCost = bestPaths[vertex].cost;
                lowestCostVertex = vertex;
            }
        }

        visited.insert(lowestCostVertex);

        for(int vertex = 0; vertex < verticies; vertex++){
            //determine if vertex is visited
            if((visited.count(vertex) == 0) && (graph[lowestCostVertex][vertex] <  INFI)){
                //determine an extened path cost
                int newPathCost = lowestCost + graph[lowestCostVertex][vertex];
                
                //determine if the new cost is the lowest and update accordingly 
                if(newPathCost < bestPaths[vertex].cost){
                    bestPaths[vertex].cost = newPathCost;
                    bestPaths[vertex].path = bestPaths[lowestCostVertex].path;
                    bestPaths[vertex].path.push_back(vertex);
                }
            }
        }
    }
}

/**
 * displayShortestPath
 * prints the shortest path in order from the origin to end
 * followed by the cost of the path
 * 
 * @param verticies the number of total verticies
 * @param paths an array of the shortest path to each vertex
 * @param locations an array of locations
*/
void displayShortestPath(int verticies, PATH paths[], string locations[]){    
    //find the last location and print its path
    for(int vx = 0; vx < paths[verticies - 1].path.size(); vx++){
        cout << locations[paths[verticies - 1].path[vx]] << " ";
    }
    //printing the final locations cost
    cout << paths[verticies - 1].cost << endl;
}


int main(){
    int numTrials = 0;
    int verticies = 0;

    //read in number of trials
    cin >> numTrials;
    cout << "Number of trials: " << numTrials << endl;

    while(numTrials != 0){
        //read in number of verticies
        cin >> verticies;
        cin.ignore();

        PATH bestPaths[verticies];  //array of best possible path to each vertex
        vector<vector<int>> graph;  //cost matrix
        string locations[verticies];   //vertex names

        //read in city names
        for(int k = 0; k < verticies; k++){ 
            cin >> locations[k];
        }
        
        //read in cost matrix values
        int cost;
        vector<int> subGraph;
        for(int i = 0; i < verticies; i++){
            subGraph.clear();
            for(int j = 0; j < verticies; j++){     
                cin >> cost; 

                //determine if there is an edge between two given verticies
                if(cost == 0 && i != j){
                    subGraph.push_back(INFI);
                }else{
                    subGraph.push_back(cost);
                }
            }
            graph.push_back(subGraph);
        }

        dijkstra(verticies, graph, 0, bestPaths);   //determine shortest path
        displayShortestPath(verticies, bestPaths, locations);

        cout << endl;
        numTrials--;
    }
    return 0;
}