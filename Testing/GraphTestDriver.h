//
// Created by molberding on 6/14/2017.
//

#ifndef UTILITYCODE_GRAPHTESTDRIVER_H
#define UTILITYCODE_GRAPHTESTDRIVER_H

#include "../DataStructures/Graph.h"
#include "TestDriver.h"

using namespace graph;

class GraphTestDriver : public TestDriver {

private:

public:

    GraphTestDriver() {
        init("Graph");
    }

    void run() {
        Graph<Grid> graph;
        Vertex<Grid>* grid[10][10];
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                grid[i][j] = new Vertex<Grid>(Grid(i,j));
                graph.addVertex(grid[i][j]);
            }
        }

        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                if(i-1 >= 0) {
                    graph.addBidirectionalEdge(grid[i][j],grid[i-1][j]);
                }
                if(i+1 < 10) {
                    graph.addBidirectionalEdge(grid[i][j],grid[i+1][j]);
                }
                if(j-1 >= 0) {
                    graph.addBidirectionalEdge(grid[i][j],grid[i][j-1]);
                }
                if(j+1 < 10) {
                    graph.addBidirectionalEdge(grid[i][j],grid[i][j+1]);
                }
            }
        }

        Vertex<Grid>* start = grid[0][0];
        Vertex<Grid>* end   = grid[9][9];

        Path<Grid> path = graph.AStar(start, end);
        assert(18.0, path.getPathCost());
    }

};

#endif //UTILITYCODE_GRAPHTESTDRIVER_H
