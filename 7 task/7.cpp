#include "7.h"

int polygon::case_(const Point& p, const Vector& v, const bool flag) const{
    List<Point> onLine; bool check = true;
    for (auto iter = vertex.begin(); iter != vertex.end(); ++iter) {
        int curr1 = aroundLine(p, v, *iter), curr2 = aroundLine(p, v, (*(iter+1)));
        if (curr1*curr2 < 0) {
            Point tmp;
            intersectLine(p, v, *iter, (*iter) - (*(iter+1)), tmp);
            if (onLine.empty()) onLine.pushBack(tmp);
            else { 
                for (auto it = onLine.begin(); it != onLine.end(); ++it) {
                    if ((flag) ? ((*it).X() < tmp.X()) : ((*it).Y() < tmp.Y())) continue;
                    if ((*it) == tmp) {check = false; break;}
                    onLine.pushIn(it, tmp);
                    check = false;
                    break;
                }
                if (check) onLine.pushBack(tmp);
                else check = true;
            }
        }
    }

    if (onLine.empty()) return 0;
    int res = -1;
    for (auto iter = onLine.begin(); iter != onLine.end(); ++iter) {
        if ((flag) ? ((*iter).X() < p.X()) : ((*iter).Y() < p.Y())) res *= -1;
        else if ((*iter) == p) return 2;
        else return res;
    }
    return res;
}


bool polygon::paral_polygon (const Vector& p) const {
    for (auto iter = vertex.begin(); iter != vertex.end(); ++iter) {
        if (p.paral(*(iter+1)-(*iter))) return true;
    }
    return false;
}
int polygon::isInPolygon (const Point& p) const {
    double phi = M_PI/2; phi /= vertex.length()+1;
    Vector v(1, 0);
    while (paral_polygon(v)) v.rotate(phi);
    int res = case_(p, v, true);
    if (res != 0) return res;
    phi *= -1; Vector u = Vector(-1, 0);
    while (paral_polygon(u) || u.paral(v)) u.rotate(phi);
    res = case_(p, Vector(0, 1), !(u.paral(Vector(0, 1))));
    if (res != 0) return res;
    for (auto iter = vertex.begin(); iter != vertex.end(); ++iter) if (*iter == p) return 2;
    return -1;
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
            int res = P.isInPolygon(p); std::string word;
            switch (res) {
                case -1: word = "outside"; break;
                case 1: word = "inside"; break;
                case 2: word = "on border"; break;
            }
            std::cout <<"Point " << p << " is " + word + " polygon" << std::endl;
        }
    }
}

