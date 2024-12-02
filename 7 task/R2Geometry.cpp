#include "R2Geometry.h"

namespace R2Geometry {
    Vector operator*(const double c, const Vector& v) {return Vector(c*v.X(), c*v.Y());}
    Point operator* (const double c, const Point& p) {return Point(c*p.X(), c*p.Y());}

    Point operator+ (const Point& p, const Vector& v) {return Point(p.X()+v.X(), p.Y()+v.Y());}
    Point operator+ (const Vector& v, const Point& p) {return Point(p.X()+v.X(), p.Y() +v.Y());}

    Vector operator- (const Point& p, const Point& q) {return Vector(p.X()-q.X(), p.Y()-q.Y());}

    Vector RVector (const Point& p) {return Vector(p.X(), p.Y());}
    Point RPoint (const Vector& v) {return Point(v.X(), v.Y());}
    int aroundLine (const Point& p, const Vector& v, const Point& q) {
        double tmp = v.n()*(q-p);
        if (tmp > 0) return 1;
        else if (tmp < 0) return -1;
        return 0;
    }

    bool intersectLine (const Point& p1, const Vector& v1, const Point& p2, const Vector& v2, Point& res) {
        if (fabs(v1*v2.n()) < EPS) {res = p1; return false;}
        double lymbda = (v2.n()*(p2-p1))/(v1*(v2.n()));
        res = p1+lymbda*v1;
        return true;
    }
}
