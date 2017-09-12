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
    Graph<Grid> graph;
    Vertex<Grid> vertex;

public:

    GraphTestDriver() : vertex(Grid(0,0)), graph(Graph<Grid>()) {
        init("Graph");
    }

    void run() {

    }

};

#endif //UTILITYCODE_GRAPHTESTDRIVER_H
