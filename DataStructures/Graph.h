//
// Created by molberding on 6/9/2017.
//

#ifndef UTILITYCODE_GRAPH_H
#define UTILITYCODE_GRAPH_H

#include "VertexType.h"
#include <type_traits>
#include <sstream>

namespace graph {

    template<typename T>
    class Vertex {
        static_assert(std::is_base_of<VertexType, T>::value, "T must derive from VertexType");
        static_assert(std::is_default_constructible<T>::value, "T must have a default constructor");
    private:
        T vertexType;
        Vertex<T>** neighbors;
        int numNeighbors;

    public:
        Vertex() : vertexType(T()), numNeighbors(0), neighbors(nullptr) {}
        Vertex(T init) : vertexType(init), numNeighbors(0), neighbors(nullptr) {}

        ~Vertex() {
            for(int i = 0; i < numNeighbors; i++) {
                disconnect(neighbors[i]);
            }
            delete neighbors;
        }

        double getCostTo(T other) {
            return vertexType.getCostTo((VertexType *) &other);
        }

        Vertex<T>** getNeighbors() {
            return neighbors;
        }

        int getNumNeighbors() {
            return numNeighbors;
        }

        T getVertexType() {
            return vertexType;
        }

        bool isNeighborsWith(Vertex<T>* neighbor) {
            for(int i = 0; i < numNeighbors; i++) {
                if(neighbors[i] == neighbor) {
                    return true;
                }
            }
            return false;
        }

        void connect(Vertex<T>* newNeighbor) {
            if(isNeighborsWith(newNeighbor)) {
                return;
            }
            Vertex<T>** temp = new Vertex<T>*[numNeighbors + 1];
            for(int i = 0; i < numNeighbors; i++) {
                temp[i] = neighbors[i];
            }
            temp[numNeighbors++] = newNeighbor;
            delete neighbors;
            neighbors = temp;
        }

        bool disconnect(Vertex<T>* exNeighbor) {
            for(int i = 0; i < numNeighbors; i++) {
                if(neighbors[i] == exNeighbor) {
                    Vertex<T>** temp = new Vertex<T>*[numNeighbors - 1];
                    int flag = 0;
                    for(int j = 0; j < numNeighbors; j++) {
                        if(j == i) {
                            flag = 1;
                            continue;
                        } else {
                            temp[j-flag] = neighbors[j];
                        }
                    }
                    delete neighbors;
                    neighbors = temp;
                    numNeighbors--;
                    return true;
                }
            }
            return false;
        }

        std::string getRepresentation() {
            std::stringstream result;
            result << vertexType.getRepresentation() << " -> [";
            for(int i = 0; i < numNeighbors; i++) {
                result << "\n\t";
                result << neighbors[i]->getVertexType().getRepresentation();
            }
            if(numNeighbors) {
                result << std::endl;
            }
            result << "]\n";
            return result.str();
        }
    };

    template<class T>
    class Graph {
    private:
        Vertex<T>** vertices;
        int numVertices;
        int numEdges;
    public:
        Graph() {
            numVertices = 0;
            numEdges = 0;
            vertices = nullptr;
        }

        ~Graph() {
            for(int i = 0; i < numVertices; i++) {
                delete vertices[i];
            }
            delete vertices;
        }

        Graph(const Graph<T> &graph) {
            if(&graph != this) {
                numVertices = graph.numVertices;
                numEdges = graph.numEdges;
                vertices = new Vertex<T>*[numVertices];
                for(int i = 0; i < numVertices; i++) {
                    vertices[i] = graph.vertices[i];
                }
            }
        }

        Graph<T> operator=(const Graph<T> &rhs) {
            if(&rhs != this) {
                numVertices = rhs.numVertices;
                numEdges = rhs.numEdges;
                vertices = new Vertex<T>*[numVertices];
                for(int i = 0; i < numVertices; i++) {
                    vertices[i] = rhs.vertices[i];
                }
            }

            return *this;
        }

        bool areAdjacent(Vertex<T>* a, Vertex<T>* b) {
            return a->isNeighborsWith(b) || b->isNeighborsWith(a);
        }

        Vertex<T>** getNeighborsOf(Vertex<T>* vertex) {
            return vertex->getNeighbors();
        }

        bool contains(Vertex<T>* vertex) {
            for(int i = 0; i < numVertices; i++) {
                if(vertices[i] == vertex) {
                    return true;
                }
            }
            return false;
        }

        bool addVertex(Vertex<T>* vertex) {
            if(contains(vertex)) {
                return false;
            }
            Vertex<T>** temp = new Vertex<T>*[numVertices + 1];
            for(int i = 0; i < numVertices; i++) {
                temp[i] = vertices[i];
            }
            temp[numVertices++] = vertex;
            delete vertices;
            vertices = temp;

            for(int i = 0; i < vertex->getNumNeighbors(); i++) {
                addVertex(vertex->getNeighbors()[i]);
            }
            return true;
        }

        bool removeVertex(Vertex<T>* vertex) {
            bool result = false;
            for(int i = 0; i < numVertices; i++) {
                if(vertices[i]->isNeighborsWith(vertex)) {
                    vertices[i]->disconnect(vertex);
                }
            }
            for(int i = 0; i < numVertices; i++) {
                if(vertices[i] == vertex) {
                    result = true;
                    Vertex<T>** temp = new Vertex<T>*[numVertices - 1];
                    int flag = 0;
                    for(int j = 0; j < numVertices; j++) {
                        if(i == j) {
                            flag = 1;
                            continue;
                        }
                        temp[j-flag] = vertices[j];
                    }
                    delete vertices;
                    numVertices--;
                    vertices = temp;
                }
            }
            return result;
        }

        void addEdge(Vertex<T>* from, Vertex<T>* to) {
            if(!contains(from)) {
                addVertex(from);
            }
            if(!contains(to)) {
                addVertex(to);
            }
            from->connect(to);
            numEdges++;
        }

        void addBidirectionalEdge(Vertex<T>* a, Vertex<T>* b) {
            addEdge(a,b);
            b->connect(a);
        }

        void removeEdge(Vertex<T>* from, Vertex<T>* to) {
            from->disconnect(to);
            numEdges--;
        }

        void removeEdgeBidirectionally(Vertex<T>* a, Vertex<T>* b) {
            a->disconnect(b);
            b->disconnect(a);
            numEdges--;
        }

        double getCost(Vertex<T>* from, Vertex<T>* to) {
            return from->getCostTo(to);
        }
    };
}

#endif //UTILITYCODE_GRAPH_H
