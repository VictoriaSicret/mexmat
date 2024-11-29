#include "7.h"

int polygon::case_(const Point& p, const Vector& v, const bool flag) const{
    List<Point> onLine;
    for (auto iter = vertex.begin(); iter != vertex.end(); ++iter) {
        int curr1 = aroundLine(p, v, *iter), curr2 = aroundLine(p, v, *(iter+1));
        if (curr1*curr2 < 0) {
            Point tmp;
            intersectLine(p, v, *iter, (*iter)-(*(iter+1)), tmp);
            if (onLine.empty()) onLine.pushBack(tmp);
            else 
                for (auto it = onLine.begin(); it != onLine.end(); ++it) {
                    if (flag) {
                        if ((*it).X() < tmp.X()) continue;
                        onLine.pushIn(it, tmp);
                        break;
                    } else {
                        if ((*it).Y() < tmp.Y()) continue;
                        onLine.pushIn(it, tmp);
                        break;
                    }
                }
        }
    }

    if (onLine.empty()) return 0;
    int res = -1;
    for (auto iter = onLine.begin(); iter != onLine.end(); ++iter) {
        if (flag) {
            if ((*iter).X() < p.X()) res *= -1;
            else return res;
        } else {
            if ((*iter).Y() < p.Y()) res *= -1;
            else return res;
        }
    }

    return res;
}

bool polygon::isInPolygon (const Point& p) const {
    int res = case_(p, Vector(1, 0), true);
    if (res != 0) return (res == 1) ? true : false;
    res = case_(p, Vector(0, 1), false);
    if (res != 0) return (res == 1) ? true : false;
    for (auto iter = vertex.begin(); iter != vertex.end(); ++iter) if (*iter == p) return true;
    return false;
}

void start(void) {
    polygon P; size_t act = 0; double tmp1, tmp2;
    while (true) {
        std::cout << "\nChoose action:\n1)Add point\n2)Print vertexes\n3)Check point" << std::endl;
        std::cin >> act; if (act != 1 && act != 2 && act != 3) break;
        if (act == 1) {
            std::cout << "\nEnter point:" << std::endl;
            std::cin >> tmp1 >> tmp2;
            P.add(Point(tmp1, tmp2));
        } else if (act == 2) {
            std::cout <<P << std::endl;
        } else {
            std::cout << "\nEnter point:" << std::endl;
            std::cin >> tmp1 >> tmp2;
            Point p(tmp1, tmp2);
            bool res = P.isInPolygon(p);
            std::cout <<"Point " << p << " is " << ((res) ? "inside" : "outside") << " polygon" << std::endl;
        }
    }
}

