//
// Created by molberding on 6/9/2017.
//

#ifndef UTILITYCODE_VERTEX_H
#define UTILITYCODE_VERTEX_H

#include <cmath>
#include <sstream>

namespace graph {

    class VertexType {
    public:
        virtual double getCostTo(VertexType *other) = 0;
        virtual std::string getRepresentation() = 0;
    };

    class Coordinates2D : public VertexType {
    private:
        double x, y;
    public:
        Coordinates2D() : x(0), y(0) {}
        Coordinates2D(double i, double j) : x(i), y(j) { }

        double getX() { return x; }
        double getY() { return y; }

        double getCostTo(VertexType* Other) {
            Coordinates2D* other = (Coordinates2D*) Other;
            double squareX = (other->getX() - x) * (other->getX() - x);
            double squareY = (other->getY() - y) * (other->getY() - y);
            return sqrt(squareX + squareY);
        }

        std::string getRepresentation() {
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

        double getX() { return x; }
        double getY() { return y; }
        double getZ() { return z; }

        double getCostTo(VertexType* Other) {
            Coordinates3D* other = (Coordinates3D*) Other;
            double squareX = (other->getX() - x) * (other->getX() - x);
            double squareY = (other->getY() - y) * (other->getY() - y);
            double squareZ = (other->getZ() - z) * (other->getZ() - z);
            return sqrt(squareX + squareY + squareZ);
        }

        std::string getRepresentation() {
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

        double getX() { return x; }
        double getY() { return y; }

        double getCostTo(VertexType* Other) {
            Grid* other = (Grid*) Other;
            return abs(other->getX() - x) + (abs(other->getY() - y));
        }

        std::string getRepresentation() {
            std::stringstream result;
            result << "(" << x << ", " << y << ")";
            return result.str();
        }
    };
};

#endif //UTILITYCODE_VERTEX_H
