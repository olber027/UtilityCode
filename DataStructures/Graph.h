//
// Created by molberding on 6/9/2017.
//

#ifndef UTILITYCODE_GRAPH_H
#define UTILITYCODE_GRAPH_H

#include "VertexType.h"
#include <type_traits>

namespace graph {

    template<class T>
    class Vertex {
        static_assert(std::is_base_of<VertexType, T>::value, "T must derive from VertexType");
    private:
        T vertexType;
        Vertex<T>* neighbors;
        int numNeighbors;
    public:
        Vertex(T init) : vertexType(init), numNeighbors(0), neighbors(nullptr) {}
        double getCostTo(T other) {
            return vertexType.getCost((VertexType *) &other);
        }

        Vertex<T>* getNeighbors() {
            return neighbors;
        }

        int getNumNeighbors() {
            return numNeighbors;
        }

        void connect(T* newNeighbor) {

        }
    };

    template<class T>
    class Graph {
    private:
        Vertex<T> *vertices;
        int numVertices;
        int numEdges;
    public:
        Graph() {
            numVertices = 0;
            numEdges = 0;
            vertices = nullptr;
        }
    };
}

#endif //UTILITYCODE_GRAPH_H
