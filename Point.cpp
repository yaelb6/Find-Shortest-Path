//
// Created by jenny on 21/01/2020.
//

#include "Point.h"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int newX) {
    Point::x = newX;
}

void Point::setY(int newY) {
    Point::y = newY;
}

bool Point::Equals(Point* point1) {
    return ((this->x == point1->getX()) && (this->y == point1->getY()));
}
