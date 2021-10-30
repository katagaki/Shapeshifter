#include <iomanip>
#include <string>
#include "Point.h"

#ifndef SHAPETWOD_CLASS
#define SHAPETWOD_CLASS

class ShapeTwoD {
    
protected:
    std::string name;
    bool containsWarpSpace;
    Point** points = nullptr;
    int pointCount;
    Point** boundingRectPoints = nullptr;
    
public:
    
    // Constructors
    ShapeTwoD();
    ShapeTwoD(std::string name, bool containsWarpSpace);
    ShapeTwoD(std::string name, bool containsWarpSpace, Point* points[]);
    
    // Destructors
    virtual ~ShapeTwoD();
    
    // Operator overloads
    friend bool operator<(const ShapeTwoD& l, const ShapeTwoD& r);
    friend bool operator>(const ShapeTwoD& l, const ShapeTwoD& r);
    
    // Direct accessors
    std::string getName();
    bool getContainsWarpSpace();
    Point** getPoints();
    int getPointCount();
    Point** getBoundingRectPoints();
    
    // Indirect accessors
    virtual std::string toString() = 0;
    virtual double computeArea() = 0;
    virtual bool isPointInShape(int x, int y) = 0;
    virtual bool isPointOnShape(int x, int y) = 0;
    
    // Modifiers
    void setName(std::string name);
    void setContainsWarpSpace(bool containsWarpSpace);
    void setPoints(Point** points);
    
};

#endif
