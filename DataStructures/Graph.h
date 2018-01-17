//
// Created by molberding on 6/9/2017.
//

#ifndef UTILITYCODE_GRAPH_H
#define UTILITYCODE_GRAPH_H

#include <type_traits>
#include <sstream>
#include <cmath>
#include <vector>

namespace graph {

    template<typename T, typename = void>
    struct is_equal_comparable : std::false_type { };

    template<typename T>
    struct is_equal_comparable<T, typename std::enable_if<std::is_convertible<decltype(std::declval<T&>() == std::declval<T&>()), bool>{}>::type> : std::true_type {};

    class VertexType {
    public:
        virtual double getCostTo(const VertexType* other) const = 0;
        virtual std::string getRepresentation() const = 0;
    };

    class Coordinates2D : public VertexType {
    private:
        double x, y;
    public:
        Coordinates2D() : x(0), y(0) {}
        Coordinates2D(double i, double j) : x(i), y(j) { }
        Coordinates2D(const Coordinates2D& other) : Coordinates2D() {
            x = other.x;
            y = other.y;
        }

        double getX() const { return x; }
        double getY() const { return y; }

        double getCostTo(const VertexType* Other) const {
            Coordinates2D* other = (Coordinates2D*) Other;
            double squareX = (other->getX() - x) * (other->getX() - x);
            double squareY = (other->getY() - y) * (other->getY() - y);
            return std::sqrt(squareX + squareY);
        }

        bool operator==(const Coordinates2D& other) const {
            return (x == other.x && y == other.y);
        }

        std::string getRepresentation() const {
            std::stringstream result;
            result << "(" << x << ", " << y << ")";
            return result.str();
        }
    };

    class Coordinates3D : public VertexType {
    private:
        double x, y, z;

    public:
        Coordinates3D() : x(0), y(0), z(0) {}
        Coordinates3D(double i, double j, double k) : x(i), y(j), z(k) { }
        Coordinates3D(const Coordinates3D& other) : Coordinates3D() {
            x = other.x;
            y = other.y;
            z = other.z;
        }

        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }

        double getCostTo(const VertexType* Other) const {
            Coordinates3D* other = (Coordinates3D*) Other;
            double squareX = (other->getX() - x) * (other->getX() - x);
            double squareY = (other->getY() - y) * (other->getY() - y);
            double squareZ = (other->getZ() - z) * (other->getZ() - z);
            return std::sqrt(squareX + squareY + squareZ);
        }

        bool operator==(const Coordinates3D& other) const {
            return (x == other.x && y == other.y && z == other.z);
        }

        std::string getRepresentation() const {
            std::stringstream result;
            result << "(" << x << ", " << y << ", " << z << ")";
            return result.str();
        }
    };

    class Grid : public VertexType {
    private:
        int x, y;

    public:
        Grid() : x(0), y(0) {}
        Grid(int i, int j) : x(i), y(j) {}
        Grid(const Grid& other) : Grid() {
            x = other.x;
            y = other.y;
        }

        double getX() const { return x; }
        double getY() const { return y; }

        double getCostTo(const VertexType* Other) const {
            Grid* other = (Grid*) Other;
            return std::abs(other->getX() - x) + (std::abs(other->getY() - y));
        }

        bool operator==(const Grid& other) const {
            return (x == other.x && y == other.y);
        }

        std::string getRepresentation() const {
            std::stringstream result;
            result << "(" << x << ", " << y << ")";
            return result.str();
        }
    };

    template<typename T>
    class Vertex {
        static_assert(std::is_base_of<VertexType, T>::value, "T must derive from VertexType");
        static_assert(std::is_default_constructible<T>::value, "T must have a default constructor");
        static_assert(is_equal_comparable<T>::value, "Type T must be comparable with the == operator");
    private:
        T vertexType;
        std::vector<Vertex<T>*> neighbors;

    public:
        Vertex() : vertexType(T()), neighbors(std::vector<Vertex<T>*>()) {}
        Vertex(const T& init) : vertexType(init), neighbors(std::vector<Vertex<T>*>()) {}

        ~Vertex() {
            for(int i = 0; i < getNumNeighbors(); i++) {
                disconnect(neighbors[i]);
            }
        }

        bool operator==(const Vertex<T>& other) const {
            return vertexType == other.getVertexType();
        }

        double getCostTo(const Vertex<T>& other) const {
            return vertexType.getCostTo((VertexType*) &other.vertexType);
        }

        std::vector<Vertex<T>*> getNeighbors() const {
            return neighbors;
        }

        int getNumNeighbors() const {
            return neighbors.size();
        }

        T getVertexType() const {
            return vertexType;
        }

        bool isNeighborsWith(const Vertex<T>* neighbor) const {
            for(int i = 0; i < getNumNeighbors(); i++) {
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
            neighbors.push_back(newNeighbor);
        }

        bool disconnect(Vertex<T>* exNeighbor) {
            for(int i = 0; i < getNumNeighbors(); i++) {
                if(neighbors[i] == exNeighbor) {
                    neighbors.erase(neighbors.begin() + i);
                    return true;
                }
            }
            return false;
        }

        std::string getRepresentation() const {
            std::stringstream result;
            result << vertexType.getRepresentation() << " -> [";
            for(int i = 0; i < getNumNeighbors(); i++) {
                result << "\n\t";
                result << neighbors[i]->getVertexType().getRepresentation();
            }
            if(getNumNeighbors()) {
                result << std::endl;
            }
            result << "]\n";
            return result.str();
        }
    };

    template<typename T>
    class Path {
    private:
        std::vector<Vertex<T>*> path;
        double pathCost;
        Vertex<T>* dest;
        Path() : path(std::vector<Vertex<T>*>()), pathCost(-1), dest(nullptr) {}
    public:
        Path(Vertex<T>* start, Vertex<T>* destination) : Path() {
            addVertex(start);
            dest = destination;
        }
        Path(const Path<T>& other) : Path() {
            if(&other != this) {
                for(int i = 0; i < other.path.size(); i++) {
                    path.push_back(other.path[i]);
                }
                pathCost = other.pathCost;
                dest = other.dest;
            }
        }
        bool operator==(const Path<T>& rhs) {
            if(path.size() != rhs.path.size()) {
                return false;
            }
            for(int i = 0; i < path.size(); i++) {
                if(path[i] != rhs.path[i]) {
                    return false;
                }
            }
            return true;
        }

        void addVertex(Vertex<T>* vertex) {
            int index = path.size() - 1;
            if(index >= 0) {
                pathCost += path[index]->getCostTo(*vertex);
            } else {
                pathCost = 0;
            }
            path.push_back(vertex);
        }
        std::vector<Vertex<T>*> getPath() const { return path; }
        double getPathCost() const { return pathCost; }
        Vertex<T>* getLastVertex() const { return path[path.size()-1]; }
        double getEstimatedCost() const {
            Vertex<T>* vert = getLastVertex();
            double costToDestination = vert->getCostTo(*dest);
            return pathCost + costToDestination;
        }
        std::vector<Vertex<T>*> getNextVertices() const {
            std::vector<Vertex<T>*> neighbors = getLastVertex()->getNeighbors();
            int numNeighbors = getLastVertex()->getNumNeighbors();
            Vertex<T>* prev = nullptr;
            if(path.size()-2 >= 0) {
                prev = path[path.size()-2];
            }
            std::vector<Vertex<T>*> results;
            for(int i = 0; i < numNeighbors; i++) {
                if(prev != neighbors[i]) {
                    results.push_back(neighbors[i]);
                }
            }
            return results;
        }
        static Path<T> getErrorPath() {
            return Path<T>();
        }
    };

    template<typename T>
    class Graph {
    private:
        Vertex<T>** vertices;
        int numVertices;
        int numEdges;
        Vertex<T>* start;
        Vertex<T>* goal;
    public:
        Graph() : numVertices(0), numEdges(0), vertices(nullptr), start(nullptr), goal(nullptr) {}

        ~Graph() {
            for(int i = 0; i < numVertices; i++) {
                delete vertices[i];
            }
            delete vertices;
        }

        Graph(const Graph<T>& graph) {
            if(&graph != this) {
                numVertices = graph.numVertices;
                numEdges = graph.numEdges;
                vertices = new Vertex<T>*[numVertices];
                for(int i = 0; i < numVertices; i++) {
                    vertices[i] = graph.vertices[i];
                }
                start = graph.start;
                goal = graph.goal;
            }
        }

        Graph<T>& operator=(const Graph<T>& rhs) {
            if(&rhs != this) {
                numVertices = rhs.numVertices;
                numEdges = rhs.numEdges;
                vertices = new Vertex<T>*[numVertices];
                for(int i = 0; i < numVertices; i++) {
                    vertices[i] = rhs.vertices[i];
                }
                start = rhs.start;
                goal = rhs.goal;
            }

            return *this;
        }

        // sets the starting vertex to the given vertex, iff the vertex
        // is part of the graph.
        bool setStart(Vertex<T>* startVertex) {
            if(contains(startVertex)) {
                start = startVertex;
                return true;
            }
            return false;
        }

        // sets the goal vertex to the given vertex, iff the vertex
        // is part of the graph.
        bool setGoal(Vertex<T>* goalVertex) {
            if(contains(goalVertex)) {
                goal = goalVertex;
                return true;
            }
            return false;
        }

        bool areAdjacent(const Vertex<T>* a, const Vertex<T>* b) const {
            return a->isNeighborsWith(b) || b->isNeighborsWith(a);
        }

        std::vector<Vertex<T>*> getNeighborsOf(const Vertex<T>* vertex) const {
            return vertex->getNeighbors();
        }

        bool contains(const Vertex<T>* vertex) const {
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

        Path<T> AStar(Vertex<T>* start, Vertex<T>* end) {
            std::vector<Path<T>> openList;
            std::vector<Path<T>> closedList;
            closedList.push_back(Path<T>(start, end));

            for(int i = 0; i < start->getNumNeighbors(); i++) {
                openList.push_back(Path<T>(start, end));
                openList[i].addVertex(start->getNeighbors()[i]);
            }

            while(openList.size() != 0) {
                double shortest = openList[0].getEstimatedCost();
                int index = 0;
                for(int i = 1; i < openList.size(); i++) {
                    if(openList[i].getEstimatedCost() < shortest) {
                        shortest = openList[i].getEstimatedCost();
                        index = i;
                    }
                }

                Vertex<T>* currentVertex = openList[index].getLastVertex();
                if(currentVertex == end) {
                    return openList[index];
                }

                std::vector<Vertex<T>*> nextVertices = openList[index].getNextVertices();
                for(int i = 0; i < nextVertices.size(); i++) {
                    Path<T> temp = openList[index];
                    Vertex<T>* next = nextVertices[i];
                    temp.addVertex(next);
                    bool add = true;

                    for(int j = 0; j < closedList.size(); j++) {
                        if(closedList[j].getLastVertex() == next) {
                            if(temp.getPathCost() < closedList[j].getPathCost()) {
                                closedList.erase(closedList.begin() + j);
                            } else {
                                add = false;
                                break;
                            }
                        }
                    }

                    for(int j = 0; j < openList.size() && add; j++) {
                        if(openList[j].getLastVertex() == next) {
                            if(openList[j].getPathCost() <= temp.getPathCost()) {
                                add = false;
                            } else {
                                openList.erase(openList.begin() + j);
                            }
                            break;
                        }
                    }
                    if(add) {
                        openList.push_back(temp);
                    }
                }

                closedList.push_back(openList[index]);
                openList.erase(openList.begin() + index);
            }

            return Path<T>::getErrorPath();
        }

        Path<T> AStar() {
            if(start != nullptr && goal != nullptr) {
                return AStar(start, goal);
            }
            return Path<T>::getErrorPath();
        }

    };
}

#endif //UTILITYCODE_GRAPH_H
