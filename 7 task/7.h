#include "R2Geometry.h"
#include "LIST.h"

using namespace LIST;
using namespace R2Geometry;
class polygon {
    List<Point> vertex;
    
    int case_(const Point& p, const Vector& v, const bool flag) const;
    public:
    polygon(void): vertex() {}
    polygon(const polygon& p): vertex(p.vertex) {}
    polygon(polygon&& p): vertex(std::move(p.vertex)) {}
    ~polygon(void) {}

    polygon& operator= (const polygon& p) {
        vertex = p.vertex; return *this;
    }
    polygon& operator= (polygon&& p) {
        vertex = std::move(p.vertex); return *this;
    }

    void add(const Point& x) {vertex.pushBack(x);}

    bool isInPolygon(const Point& p) const;
    friend std::ostream& operator<< (std::ostream& os, const polygon& p) {
        return os << p.vertex;
    }
};

void start(void);
