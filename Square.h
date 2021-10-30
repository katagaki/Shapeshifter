#include <string>
#include "ShapeTwoD.h"

#ifndef SQUARE_CLASS
#define SQUARE_CLASS

class Square: public ShapeTwoD {
    
    // Squares contain 4 points
    // Points are equidistant
    //
    // [0]    [1]
    //   +----+
    //   |    |
    //   +----+
    // [2]    [3]
    
public:
    
    // Constructors
    Square();
    Square(std::string name, bool containsWarpSpace);
    Square(std::string name, bool containsWarpSpace, Point* points[]);
    
    // Destructors
    ~Square();
    
    // Operator overloads
    friend bool operator<(const Square& l, const Square& r);
    friend bool operator>(const Square& l, const Square& r);
    
    // Indirect accessors
    std::string toString();
    double computeArea();
    bool isPointInShape(int x, int y);
    bool isPointOnShape(int x, int y);
    
private:
    
    double height();
    double width();
    
};

#endif
