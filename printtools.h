#include <iomanip>
#include <iostream>
#include <string>
#include "ShapeTwoD.h"

#ifndef PRINTTOOLS
#define PRINTTOOLS

namespace cpt {
    
    // Print to console output
    void print(std::string text);
    
    // Print blank line to console output
    void println();
    
    // Print to console output with new line
    void println(std::string text);
    
    // Print to console output with blank line following
    void printdln(std::string text);
    
    // Print divider of dashes
    void printdiv(char divchar, int width);
    
    // Clears the console
    void printpg();
    
    // Prints the shape report
    void printshapes(ShapeTwoD** shapes, int shapeCount);
    
}

#endif
