//
// Created by jenny on 21/01/2020.
//

#ifndef EX4_POINT_H
#define EX4_POINT_H


class Point {
private:
    int x;
    int y;
public:
    void setX(int x);

    void setY(int y);

    int getX() const;

    int getY() const;
    Point(int x, int y);
    bool Equals(Point* point1);
};


#endif //EX4_POINT_H
