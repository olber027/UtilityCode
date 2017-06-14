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
    Graph<Coordinates2D> graph;
    Vertex<Coordinates2D> vertex;

public:

    GraphTestDriver() : vertex(Coordinates2D(1,1)), graph(Graph<Coordinates2D>()) {
        passed = 0;
        failed = 0;
        total = 0;
    }

    void run() {

    }

};

#endif //UTILITYCODE_GRAPHTESTDRIVER_H
