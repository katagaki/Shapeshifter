#include <string>
#include "Rectangle.h"
#include "ShapeTwoD.h"

#ifndef CROSS_CLASS
#define CROSS_CLASS

class Cross: public ShapeTwoD {
    
    // Crosses contain 12 points
    //
    //          [2]    [3]
    //          +------+
    // [0]   [1]|      |
    //   +------+      |[4]
    //   |             +----+[5]
    //   +-----+            |
    // [6]  [7]|    +-------+[11]
    //         |    |[10]
    //         +----+
    //        [8]    [9]
    
protected:
    
    Rectangle* boundingRect = nullptr;
    
private:
    
    double topLeftBoundingRectArea();
    double topRightBoundingRectArea();
    double bottomLeftBoundingRectArea();
    double bottomRightBoundingRectArea();
    
public:
    
    // Constructors
    Cross();
    Cross(std::string name, bool containsWarpSpace);
    Cross(std::string name, bool containsWarpSpace, Point* points[]);
    
    // Destructors
    ~Cross();
    
    // Operator overloads
    friend bool operator<(const Cross& l, const Cross& r);
    friend bool operator>(const Cross& l, const Cross& r);
    
    // Indirect accessors
    std::string toString();
    double computeArea();
    bool isPointInShape(int x, int y);
    bool isPointOnShape(int x, int y);
    
};

#endif
