#ifndef UTILITYCODE_ASTAR_H
#define UTILITYCODE_ASTAR_H

#include "Heuristics.h"
#include "Coordinates.h"
#include <vector>
#define vector std::vector

class AStarNode {
public:
    AStarNode();


private:
    double f, g, h;
    CartesianCoordinates coords;
};

class AStar{
public:

private:
    Heuristic* heuristic;
    vector<AStarNode> nodes;
    AStarNode goal;
};

#endif //UTILITYCODE_ASTAR_H