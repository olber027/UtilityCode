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

        /*
         *   0 1 2 3 4 5 6 j
         * 0 S O O O O O O
         * 1 O O O O X X X
         * 2 X O O X X O X
         * 3 X X O O O O E
         * i
         */
        Graph<Grid> graph;
        Vertex<Grid>* grid[4][7];
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 7; j++) {
                grid[i][j] = new Vertex<Grid>(Grid(i,j));
                graph.addVertex(grid[i][j]);
            }
        }

        graph.addBidirectionalEdge(grid[0][0], grid[0][1]);
        graph.addBidirectionalEdge(grid[0][0], grid[1][0]);
        graph.addBidirectionalEdge(grid[0][1], grid[0][2]);
        graph.addBidirectionalEdge(grid[0][1], grid[1][1]);
        graph.addBidirectionalEdge(grid[0][2], grid[0][3]);
        graph.addBidirectionalEdge(grid[0][2], grid[1][2]);
        graph.addBidirectionalEdge(grid[0][3], grid[0][4]);
        graph.addBidirectionalEdge(grid[0][3], grid[1][3]);
        graph.addBidirectionalEdge(grid[0][4], grid[0][5]);
        graph.addBidirectionalEdge(grid[0][5], grid[0][6]);

        graph.addBidirectionalEdge(grid[1][0], grid[1][1]);
        graph.addBidirectionalEdge(grid[1][1], grid[1][2]);
        graph.addBidirectionalEdge(grid[1][1], grid[2][1]);
        graph.addBidirectionalEdge(grid[1][2], grid[1][3]);
        graph.addBidirectionalEdge(grid[1][2], grid[2][2]);

        graph.addBidirectionalEdge(grid[2][1], grid[2][2]);
        graph.addBidirectionalEdge(grid[2][2], grid[3][2]);
        graph.addBidirectionalEdge(grid[2][5], grid[3][5]);

        graph.addBidirectionalEdge(grid[3][2], grid[3][3]);
        graph.addBidirectionalEdge(grid[3][3], grid[3][4]);
        graph.addBidirectionalEdge(grid[3][4], grid[3][5]);
        graph.addBidirectionalEdge(grid[3][5], grid[3][6]);

        Vertex<Grid>* start = grid[0][0];
        Vertex<Grid>* end   = grid[3][6];

        Path<Grid> path = graph.AStar(start, end);
        assert(9.0, path.getPathCost(), "A* did not come up with the correct path");

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 7; j++) {
                delete grid[i][j];
            }
        }

    }

};

#endif //UTILITYCODE_GRAPHTESTDRIVER_H
