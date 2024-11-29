#ifndef R2GEOMETRY
#define R2GEOMETRY

#include <iostream>
#include <cmath>

#define EPS 1e-12

namespace R2Geometry {

    class Point;
    class Vector;

    Point operator+ (const Vector& v, const Point& p);

    Vector operator*(const Vector& v, const double c);
    Vector operator*(const double c, const Vector& v);

    Point operator* (const double c, const Point& p);
    Point operator* (const Point& p, const double c);

    Vector RVector (const Point& p);

    Point operator+ (const Point& p, const Vector& v);
    Point operator+ (const Point& p, const Point& q);
    Vector operator- (const Point& p, const Point& q);

    Point RPoint (const Vector& v);

    int aroundLine (const Point& p, const Vector& v, const Point& q);
    bool intersectLine (const Point& p1, const Vector& v1, const Point& p2, const Vector& v2, Point& res);

    class Point {
        double x;
        double y;
    
        public:
    
        Point(double xx = 0, double yy = 0) {
            if (fabs(xx) < EPS) x = 0;
            else x = xx;

            if (fabs(yy) < EPS) y = 0;
            else y = yy; 
        }
        
        Point(const Point& p) {
            x = p.x;
            y = p.y;
        }

        Point(Point&& p) {
            x = p.x; p.x = 0;
            y = p.y; p.y = 0;
        }

        Point& operator= (const Point& p) {
            x = p.x;
            y = p.y;
            return *this;
        }

        Point& operator= (Point&& p) {
            x = p.x; p.x = 0;
            y = p.y; p.y = 0;
            return *this;
        }
    
        const double& X(void) const {return x;}
        double& X(void) {return x;}

        const double& Y(void) const {return y;}
        double& Y(void) {return y;}

        bool operator== (const Point& p) const {return fabs(x-p.x) < EPS && fabs(y-p.y)< EPS;}
	    bool operator!= (const Point& p) const {return !(*this == p);}
        friend std::ostream& operator<< (std::ostream& os, const Point& p) {
            return os << "(" << p.X() <<" , "<< p.Y() <<")";
        }
    };

    class Vector {
        double x;
        double y;

        public:

        Vector(double xx = 0, double yy = 0) {
            if (fabs(xx) < EPS) x = 0;
            else x = xx;

            if (fabs(yy) < EPS) y = 0;
            else y = yy;
        }

        Vector(const Vector& v) {
            x = v.x;
            y = v.y;
        }

        Vector(Vector&& v) {
            x = v.x; v.x = 0;
            y = v.y; v.y = 0;
        }

        Vector& operator= (const Vector& v) {
            x = v.x;
            y = v.y;
            return *this;
        }
    
        Vector& operator= (Vector&& v) {
            x = v.x; v.x = 0;
            y = v.y; v.y = 0;
            return *this;
        }

        const double& X(void) const{return x;}
        double& X(void) {return x;}

        const double& Y(void) const{return y;}
        double& Y(void) {return y;}

        Vector operator+ (const Vector& v) const {
            return Vector(x+v.x, y+v.y);
        }

        Vector operator- (const Vector& v) const {
            return Vector(x-v.x, y-v.y);
        }

        Point operator+ (const Point& p) const {
            return Point(x+p.X(), y+p.Y());
        }

        Vector operator+(void) const {
            return Vector(x, y);
        }

        Vector operator-(void) const {
            return Vector(-x, -y);
        }

        double operator*(const Vector& v) const {
            return x*v.x+y*v.y;
        }

        Vector operator*(const double c) const {
            return Vector(c*x, c*y);
        }

        double mod(void) const{
            return sqrt(x*x);
        }

        Vector n (void) const {
            return Vector(-y, x);
        }

        Vector unit (void) const {
            return Vector(x/this->mod(), y/this->mod());
        }

        Vector& norm (void) {
            double len = this->mod();
            x /= len; y /= len;
            return *this;
        }

        bool operator== (const Vector& v) const {return fabs(x-v.x) < EPS && fabs(y-v.y) < EPS;}
        bool operator!= (const Vector& v) const {return !(*this == v);}
    };

}

#endif
