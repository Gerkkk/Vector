#include "headers/vector.h"
#include <iostream>
#include <assert.h>

using namespace vector;

struct Shape{
    std::string name;
    std::string parent_shape;
    double r;
    double phi;
};

int main() {
    Vector<std::string> s;

    s.push_back("u");
    s.push_back("0");
    s.push_back("n");
    assert(s.back() == "n" && s.front() == "u");

    Vector<Shape> a;
    assert(a.empty() == 1 && a.size() == 0);

    a.push_back({"A1", "Triangle", 0.245, -2.9});
    a.push_back({"O", "Circle", 0.0, -1.87});
    a.push_back({"P2", "Square", 13.245, 0.867});
    a.push_back({"A4", "Triangle", 0.5, 3.14});

    assert(a[2].name == "P2" && a[0].phi == -2.9);
    assert(a.empty() == 0);

    Vector<Shape> b = std::move(a);
    Vector<Shape> c = b;

    c.push_back({"A4", "Triangle", 0.5, 3.14});

    assert(c.capacity() == 8);

    Vector<double> d;
    assert(d.capacity() == 4 && d.size() == 0 && d.empty());

    auto it1 = s.begin();
    auto it2 = s.end();

    assert(it1 != it2);

    int i = 0;
    while (it1 != s.end()) {
        assert((*it1) == s[i]);
        ++it1;
        ++i;
    }
    assert(it1 == it2);

    --it2;
    --it2;
    i = 2;
    while (it2 != s.begin()) {
        assert((*it2) == s[i]);
        --it2;
        --i;
    }
    assert((*it2) == "u");
    assert(it1 != it2);
    assert(s[s.size() - 1] == "n" && s[s.size() - 2] == "0" && s[s.size() - 3] == "u");
    s.pop_back();
    s.pop_back();
    s.pop_back();
    std::cout << "Tests were successfully completed" << std::endl;
    return 0;
}