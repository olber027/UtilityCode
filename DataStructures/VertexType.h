//
// Created by molberding on 6/9/2017.
//

#ifndef UTILITYCODE_VERTEX_H
#define UTILITYCODE_VERTEX_H

#include <cmath>

namespace graph {


    class VertexType {
    public:
        virtual double getCost(VertexType *other) = 0;
    };

    class Coordinates2D : public VertexType {
    private:
        double x, y;
    public:
        double getX() { return x; }
        double getY() { return y; }

        Coordinates2D(double i, double j) : x(i), y(j) { }

        double getCost(VertexType *Other) {
            Coordinates2D* other = (Coordinates2D*) Other;
            double squareX = (other->getX() - x) * (other->getX() - x);
            double squareY = (other->getY() - y) * (other->getY() - y);
            return sqrt(squareX + squareY);
        }
    };


};

#endif //UTILITYCODE_VERTEX_H
