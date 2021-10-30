// Console printing tool library

#include <iomanip>
#include <iostream>
#include <string>
#include "ShapeTwoD.h"

namespace cpt {
    
    void print(std::string text) {
        std::cout << text;
    }
    
    void println() {
        std::cout << std::endl;
    }
    
    void println(std::string text) {
        print(text);
        std::cout << std::endl;
    }
    
    void printdln(std::string text) {
        println(text);
        std::cout << std::endl;
    }
    
    void printdiv(char divchar, int width) {
        std::cout << std::setfill(divchar) << std::setw(width) << "-" << std::endl;
    }
    
    void printpg() {
        std::cout << "\033[2J\033[1;1H";
    }
    
    void printshapes(ShapeTwoD** shapes, int shapeCount) {
        
        long numberOfPointsInShape,
        numberOfPointsOnShape;
        int totalNumberOfPointsToCheck;
        Point** boundingPoints = nullptr;
        Point** pointsInShape = nullptr;
        Point** pointsOnShape = nullptr;
        
        for (int i = 0; i < shapeCount; ++i) {
            
            // Print basc information provided by ShapeTwoD class
            println("-------- Shape " + std::to_string(i + 1) + " --------");
            println();
            println(shapes[i] -> toString());
            println();
            
            // Get bounding points for shape
            boundingPoints = shapes[i] -> getBoundingRectPoints();
            totalNumberOfPointsToCheck = ((boundingPoints[1] -> x) - (boundingPoints[0] -> x)) * ((boundingPoints[0] -> y) - (boundingPoints[2] -> y));
            
            // Initialize counts to 0
            numberOfPointsInShape = 0;
            numberOfPointsOnShape = 0;
            
            // Run through every point in an on bounding rectangle and check role
            for (int x = (boundingPoints[0] -> x); x <= (boundingPoints[1] -> x); ++x) {
                for (int y = (boundingPoints[2] -> y); y <= (boundingPoints[0] -> y); ++y) {
                    if (shapes[i] -> isPointInShape(x, y)) {
                        
                        // Add a point in the shape to the array
                        if (pointsInShape) {
                            Point** newPointsInShape = new Point*[numberOfPointsInShape + 1];
                            for (int z = 0; z < numberOfPointsInShape; ++z) {
                                newPointsInShape[z] = pointsInShape[z];
                            }
                            newPointsInShape[numberOfPointsInShape] = new Point(x, y);
                            pointsInShape = newPointsInShape;
                            ++numberOfPointsInShape;
                        } else {
                            pointsInShape = new Point*[1];
                            numberOfPointsInShape = 1;
                            pointsInShape[0] = new Point(x, y);
                        }
                        
                    } else if (shapes[i] -> isPointOnShape(x, y)) {
                        
                        // Add a point on the shape to the array
                        if (pointsOnShape) {
                            Point** newPointsOnShape = new Point*[numberOfPointsOnShape + 1];
                            for (int z = 0; z < numberOfPointsOnShape; ++z) {
                                newPointsOnShape[z] = pointsOnShape[z];
                            }
                            newPointsOnShape[numberOfPointsOnShape] = new Point(x, y);
                            pointsOnShape = newPointsOnShape;
                            ++numberOfPointsOnShape;
                        } else {
                            pointsOnShape = new Point*[1];
                            numberOfPointsOnShape = 1;
                            pointsOnShape[0] = new Point(x, y);
                        }
                        
                    }
                }
            }
            
            // Print points on perimeter
            print("Points on perimeter: ");
            for (int i = 0; i < numberOfPointsOnShape; ++i) {
                if (pointsOnShape[i]) {
                    print(pointsOnShape[i] -> toString());
                    if (i < numberOfPointsOnShape - 1) {
                        print(", ");
                    }
                }
            }
            
            println();
            
            // Print points in shape
            print("Points in shape: ");
            for (int i = 0; i < numberOfPointsInShape; ++i) {
                if (pointsInShape[i]) {
                    print(pointsInShape[i] -> toString());
                    if (i < numberOfPointsInShape - 1) {
                        print(", ");
                    }
                }
            }
            
            // Free up used memory
            delete[] pointsOnShape;
            delete[] pointsInShape;
            
            println();
            println();
            
        }
        
    }
    
}
