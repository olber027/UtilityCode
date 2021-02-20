//
// Created by molberding on 6/14/2017.
//

#ifndef UTILITYCODE_GRAPHTESTDRIVER_H
#define UTILITYCODE_GRAPHTESTDRIVER_H

#include "DataStructures/Graph.h"
#include "TestDriver.h"

using namespace Utilities;

class GraphTestDriver : public TestDriver
{
public:
    GraphTestDriver();
    void run() override;
};

#endif//UTILITYCODE_GRAPHTESTDRIVER_H
