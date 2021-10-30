#include <algorithm>
#include <iostream>
#include <string>
#include "Circle.h"
#include "Cross.h"
#include "Point.h"
#include "printtools.h"
#include "Rectangle.h"
#include "ShapeTwoD.h"
#include "Square.h"

// Print header with optional subtitle
void printHeader(std::string subTitle = "") {
    cpt::printpg();
    cpt::printdiv('-', 53);
    cpt::println("2D-StarFleet Shapeshifter");
    cpt::printdiv('-', 53);
    if (!(subTitle == "")) {
        cpt::println(subTitle);
        cpt::printdiv('-', 53);
    }
    cpt::println();
}

// Displays the main menu and prompts the user for a valid choice
// V2 of implementation from WIPS
//
// Menu indexes:
// 1: Input sensor data
// 2: Compute area for all records
// 3: Print shape report
// 4: Show sort shape data submenu
// 5: Quit
// 6: Sort shape data by area (ascending)
// 7: Sort shape data by area (descending)
// 8: Sort shape data by special type and area
//
int mainMenu() {
    
    int selectedChoice = 0;
    bool showMainMenu = true;
    
    // Prompt user for choice and check the choice
    do {
        
        // Print top menu
        if (showMainMenu) {
            showMainMenu = false;
            printHeader();
            cpt::println("Welcome, captain.");
            cpt::println();
            cpt::println("1) Input sensor data");
            cpt::println("2) Compute area for all shapes");
            cpt::println("3) Print shape report");
            cpt::println("4) Sort shape data");
            cpt::println("5) Quit");
            cpt::println();
        }
        
        cpt::print("Please enter your choice: ");
        std::cin >> selectedChoice;
        std::cin.clear();
        
        if (selectedChoice > 0 && selectedChoice < 6 && selectedChoice != 4) {
            return selectedChoice;
        } else if (selectedChoice == 4) {
            
            // Print sub menu
            printHeader("Sort Shape Data");
            cpt::printdln("Sort shape data by:");
            cpt::println("1) Area (ascending)");
            cpt::println("2) Area (descending)");
            cpt::println("3) Special type and area");
            cpt::println();
            cpt::println("4) Return to main menu");
            cpt::println();
            
            do {
                
                cpt::print("Please enter your preferred sort option: ");
                std::cin >> selectedChoice;
                std::cin.clear();
                
                if (selectedChoice <= 0 || selectedChoice >= 5) {
                    cpt::println("Invalid choice, please try again.");
                    selectedChoice = 0;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if (selectedChoice == 4) {
                    showMainMenu = true;
                }
                
            } while (!(selectedChoice > 0 && selectedChoice < 5));
            
            if (selectedChoice != 4) {
                return selectedChoice + 5;
            } else {
                selectedChoice = 0;
            }
            
        } else {
            cpt::println("Invalid choice, please try again.");
            selectedChoice = 0;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (!(selectedChoice > 0 && selectedChoice < 9));
    
    return selectedChoice;
    
}

// The main entry point of the program
int main() {
    
    // Declarations
    int areaCount,
        choice,
        currentPointX,
        currentPointY,
        pointCount,
        wsShapeCount,
        nsShapeCount,
        minIndex,
        maxIndex;
    int shapeCount = 0;
    bool isEnterKeyPressed,
         isGoingToExit,
         isInputValid,
         isPreviousInputValid;
    double* areas;
    Point** currentPoints;
    std::string strShape,
                strType;
    ShapeTwoD* currentShape;
    ShapeTwoD** shapes = nullptr;
    ShapeTwoD** shapesSortedArea = nullptr;
    ShapeTwoD** shapesSortedAreaWS = nullptr;
    ShapeTwoD** shapesSortedAreaNS = nullptr;
    
    cpt::println("Loading...");
    
    do {
        
        choice = mainMenu();
        
        // Menu indexes:
        // 1: Input sensor data
        // 2: Compute area for all records
        // 3: Print shape report
        // 4: Show sort shape data submenu
        // 5: Quit
        // 6: Sort shape data by area (ascending)
        // 7: Sort shape data by area (descending)
        // 8: Sort shape data by special type and area
        //
        switch (choice) {
            case 1:
                
                isInputValid = false;
                isPreviousInputValid = true;
                
                do {
                    
                    printHeader("Input Sensor Data");
                    cpt::println("Shape selected: ");
                    cpt::println("Shape type: ");
                    cpt::println("Points: ");
                    cpt::println();
                    
                    // Read in name of shape
                    if (isPreviousInputValid == false) {
                        cpt::print("Invalid shape, please try again (valid shapes: 'circle', 'cross', 'rectangle', 'square'). Enter the name of the shape: ");
                    } else {
                        cpt::print("Enter the name of the shape: ");
                    }
                    std::cin >> strShape;
                    std::cin.clear();
                    
                    // Make input lowercase
                    std::transform(strShape.begin(),
                                   strShape.end(),
                                   strShape.begin(),
                                   tolower);
                    
                    // Validate input
                    if (strShape == "circle" ||
                        strShape == "cross" ||
                        strShape == "rectangle" ||
                        strShape == "square") {
                        isInputValid = true;
                        isPreviousInputValid = true;
                        if (strShape == "circle") {
                            pointCount = 2;
                        } else if (strShape == "cross") {
                            pointCount = 12;
                        } else if (strShape == "rectangle" || strShape == "square") {
                            pointCount = 4;
                        }
                    } else {
                        isInputValid = false;
                        isPreviousInputValid = false;
                        strShape = false;
                    }
                    
                } while (!isInputValid);
                
                isInputValid = false;
                isPreviousInputValid = true;
                
                do {
                    
                    printHeader("Input Sensor Data");
                    cpt::println("Shape selected: " + strShape);
                    cpt::println("Shape type: ");
                    cpt::println("Points: ");
                    cpt::println();
                    
                    // Read in type of shape
                    if (isPreviousInputValid == false) {
                        cpt::print("Invalid type, please try again (valid types: 'ns', 'ws'). Enter the name of the shape: ");
                    } else {
                        cpt::print("Enter the type of the shape: ");
                    }
                    std::cin >> strType;
                    std::cin.clear();
                    
                    // Make input lowercase
                    std::transform(strType.begin(),
                                   strType.end(),
                                   strType.begin(),
                                   tolower);
                    
                    // Validate input
                    if (strType == "ns" ||
                        strType == "ws") {
                        
                        isInputValid = true;
                        isPreviousInputValid = true;
                    } else {
                        isInputValid = false;
                        isPreviousInputValid = false;
                        strType = false;
                    }
                    
                } while (!isInputValid);
                
                isInputValid = false;
                currentPoints = new Point*[pointCount];
                
                // Read in all required points
                for (int i = 0; i < pointCount; ++i) {
                    
                    printHeader("Input Sensor Data");
                    cpt::println("Shape selected: " + strShape);
                    cpt::println("Shape type: " + strType);
                    cpt::print("Points: ");
                    for (int j = 0; j < i; ++j) {
                        if (currentPoints[j]) {
                            cpt::print(currentPoints[j] -> toString());
                            if (j < i - 1) {
                                cpt::print(", ");
                            }
                        }
                    }
                    cpt::println();
                    cpt::println();
                    cpt::println("Point " + std::to_string(i + 1) + " of " + std::to_string(pointCount));
                    
                    // Read in X coordinate of current point
                    cpt::print("Enter the X coordinate of the point: ");
                    std::cin >> currentPointX;
                    std::cin.clear();
                    
                    // Read in Y coordinate of current point
                    cpt::print("Enter the Y coordinate of the point: ");
                    std::cin >> currentPointY;
                    std::cin.clear();
                    
                    currentPoints[i] = new Point(currentPointX, currentPointY);
                    
                }
                
                // Create the shape
                strShape[0] = toupper(strShape[0]);
                if (strShape == "Circle") {
                    currentShape = new Circle(strShape,
                                              (strType == "ws" ? true : false),
                                              currentPoints);
                } else if (strShape == "Cross") {
                    currentShape = new Cross(strShape,
                                             (strType == "ws" ? true : false),
                                             currentPoints);
                } else if (strShape == "Rectangle") {
                    currentShape = new Rectangle(strShape,
                                                 (strType == "ws" ? true : false),
                                                 currentPoints);
                } else if (strShape == "Square") {
                    currentShape = new Square(strShape,
                                              (strType == "ws" ? true : false),
                                              currentPoints);
                } else {
                    currentShape = nullptr;
                }
                
                // Add the shape to the coordinate system
                
                if (shapes) {
                    
                    // Create a new array with 1 more space
                    ShapeTwoD** newShapes = new ShapeTwoD*[shapeCount + 1];
                    
                    // Copy existing array to new array
                    for (int i = 0; i < shapeCount; ++i) {
                        newShapes[i] = shapes[i];
                    }
                    
                    // Add new element to new array
                    newShapes[shapeCount] = currentShape;
                    
                    // Set new array to old array
                    shapes = newShapes;
                    
                    ++shapeCount;
                    
                } else {
                    
                    ++shapeCount;
                    
                    // Initialize the array
                    shapes = new ShapeTwoD*[shapeCount];
                    
                    shapes[0] = currentShape;
                    
                }
                
                // Print the final results
                printHeader("Input Sensor Data");
                cpt::println("Shape selected: " + strShape);
                cpt::println("Shape type: " + strType);
                cpt::print("Points: ");
                for (int i = 0; i < pointCount; ++i) {
                    if (currentPoints[i]) {
                        cpt::print(currentPoints[i] -> toString());
                        if (i < pointCount - 1) {
                            cpt::print(", ");
                        }
                    }
                }
                cpt::println();
                cpt::println();
                cpt::println("The above shape has been successfully added to the coordinate system.");
                cpt::println();
                cpt::println("Total number of shapes: " + std::to_string(shapeCount) + " shape(s)");
                
                break;
                
            case 2:
                printHeader("Shape Areas");
                
                // Check if there are any shapes
                if (shapes) {
                    
                    // Reinitialize area array
                    if (areas) {
                        delete[] areas;
                    }
                    areas = new double[shapeCount];
                    
                    // Store the count of areas calculated up till this time to prevent segmentation fault later on
                    areaCount = shapeCount;
                    
                    // Store areas for every shape thus far into the array
                    for (int i = 0; i < areaCount; ++i) {
                        areas[i] = shapes[i] -> computeArea();
                    }
                    
                    cpt::println("Computation completed for " + std::to_string(shapeCount) + " shape(s).");
                    
                } else {
                    cpt::println("No shapes were found in the coordinate system.");
                }
                
                break;
            case 3:
                printHeader("Shape Report");
                
                cpt::println("Total number of shapes: " + std::to_string(shapeCount));
                cpt::println();
                
                cpt::printshapes(shapes, shapeCount);
                
                break;
            case 5:
                isGoingToExit = true;
                break;
            case 6:
                
                printHeader("Sort Shape Data - By Area (Ascending)");
                
                if (shapes) {
                    
                    shapesSortedArea = new ShapeTwoD*[shapeCount];
                    
                    // Copy unsorted array
                    for (int i = 0; i < shapeCount; ++i) {
                        shapesSortedArea[i] = shapes[i];
                    }
                    
                    std::sort(shapesSortedArea, shapesSortedArea + shapeCount, <);
                    
                    cpt::println("Total number of shapes: " + std::to_string(shapeCount));
                    cpt::println();
                    
                    cpt::printshapes(shapesSortedArea, shapeCount);
                    
                } else {
                    cpt::println("No shapes have been added yet. Please run 'Input sensor data' at least once and then try again.");
                }

                break;
            case 7:
                printHeader("Sort Shape Data - By Area (Descending)");
                
                if (shapes) {
                    
                    shapesSortedArea = new ShapeTwoD*[shapeCount];
                    
                    // Copy unsorted array
                    for (int i = 0; i < shapeCount; ++i) {
                        shapesSortedArea[i] = shapes[i];
                    }
                    
                    std::sort(shapesSortedArea, shapesSortedArea + shapeCount, >);
                    
                    cpt::println("Total number of shapes: " + std::to_string(shapeCount));
                    cpt::println();
                    
                    cpt::printshapes(shapesSortedArea, shapeCount);
                    
                } else {
                    cpt::println("No shapes have been added yet. Please run 'Input sensor data' at least once and then try again.");
                }
                
                break;
            case 8:
                printHeader("Sort Shape Data - By Special Type and Area");
                
                if (shapes) {
                    
                    // Zero out initial count
                    wsShapeCount = 0;
                    nsShapeCount = 0;
                    
                    // Separate shapes into NS and WS
                    for (int i = 0; i < shapeCount; ++i) {
                        
                        if (shapes[i] -> getContainsWarpSpace()) {
                            
                            if (shapesSortedAreaWS) {
                                
                                // Create a new array with 1 more space
                                ShapeTwoD** newWSShapesSortedAreaWS = new ShapeTwoD*[wsShapeCount + 1];
                                
                                // Copy existing array to new array
                                for (int i = 0; i < wsShapeCount; ++i) {
                                    newWSShapesSortedAreaWS[i] = shapesSortedAreaWS[i];
                                }
                                
                                // Add new element to new array
                                newWSShapesSortedAreaWS[wsShapeCount] = shapes[i];
                                
                                // Set new array to old array
                                shapesSortedAreaWS = newWSShapesSortedAreaWS;
                                
                                ++wsShapeCount;
                                
                            } else {
                                
                                ++wsShapeCount;
                                
                                // Initialize the array
                                shapesSortedAreaWS = new ShapeTwoD*[wsShapeCount];
                                
                                shapesSortedAreaWS[0] = shapes[i];
                                
                            }
                            
                        } else {
                            
                            if (shapesSortedAreaNS) {
                                
                                // Create a new array with 1 more space
                                ShapeTwoD** newNSShapesSortedAreaNS = new ShapeTwoD*[nsShapeCount + 1];
                                
                                // Copy existing array to new array
                                for (int i = 0; i < nsShapeCount; ++i) {
                                    newNSShapesSortedAreaNS[i] = shapesSortedAreaNS[i];
                                }
                                
                                // Add new element to new array
                                newNSShapesSortedAreaNS[nsShapeCount] = shapes[i];
                                
                                // Set new array to old array
                                shapesSortedAreaNS = newNSShapesSortedAreaNS;
                                
                                ++nsShapeCount;
                                
                            } else {
                                
                                ++nsShapeCount;
                                
                                // Initialize the array
                                shapesSortedAreaNS = new ShapeTwoD*[nsShapeCount];
                                
                                shapesSortedAreaNS[0] = shapes[i];
                                
                            }
                            
                        }
                        
                    }
                    
                    minIndex = 0;
                    
                    // Sort WS array
                    std::sort(shapesSortedAreaWS, shapesSortedAreaWS + wsShapeCount, >);
                    
                    // Sort NS array
                    std::sort(shapesSortedAreaNS, shapesSortedAreaNS + nsShapeCount, >);
                    
                    cpt::println("NON WARP-SPACE SHAPES");
                    cpt::println();
                    cpt::printshapes(shapesSortedAreaNS, nsShapeCount);
                    cpt::println("WARP-SPACE SHAPES");
                    cpt::println();
                    cpt::printshapes(shapesSortedAreaWS, wsShapeCount);
                    
                } else {
                    cpt::println("No shapes have been added yet. Please run 'Input sensor data' at least once and then try again.");
                }
                
                break;
            default: break;
        }
        
        if (0 < choice && choice < 9 && choice != 5) {
            std::cout << std::endl << "Press Enter to return to the main menu.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            isEnterKeyPressed = false;
            while (!isEnterKeyPressed) {
                if (std::cin.get() == '\n') {
                    isEnterKeyPressed = true;
                }
            }
        }
        
    } while (!isGoingToExit);
    
    printHeader("Program Exiting");
    cpt::println("Cleaning up before exiting... ");
    
    // Throw away anything we don't need anymore
    
    if (areas) {
        cpt::println("Removing calculated areas...");
        delete[] areas;
    }
    
    if (shapes) {
        cpt::println("Removing shapes...");
        delete[] shapes;
    }
    
    if (shapesSortedArea) {
        cpt::println("Removing sorted shapes...");
        delete[] shapesSortedArea;
    }
    
    if (shapesSortedAreaWS) {
        cpt::println("Removing sorted WS shapes...");
        delete[] shapesSortedAreaWS;
    }
    
    if (shapesSortedAreaNS) {
        cpt::println("Removing sorted NS shapes...");
        delete[] shapesSortedAreaNS;
    }
    
    // Finished
    
    printHeader();
    cpt::println("Thank you for using Shapeshifter. Bon voyage.");
    cpt::println();
    
    return 0;
    
}


