#include <iostream>
#include <iomanip>
#include <vector>

#include "Point2D.h"
#include "Rectangle.h"

int main(){
    Point2D lowerLeft (0.0f, 0.0f);
    Point2D upperRight(3.0f, 2.0f);

    Point2D lowerLeft2 (-1.0f, -1.0f);
    Point2D upperRight2( 1.0f,  2.0f);

    Rectangle testRect(lowerLeft, upperRight);
    Rectangle testRect2(lowerLeft2, upperRight2);

    std::vector<Point2D> pointsInRect;
 // Points that should be in the rectangle
    pointsInRect.push_back(Point2D(1.0f, 1.0f)); //basic
    pointsInRect.push_back(Point2D(2.9f, 1.9f)); //if x,y switched, would be out
  //literal corner cases
    pointsInRect.push_back(Point2D(0.0f, 0.0f));
    pointsInRect.push_back(Point2D(3.0f, 2.0f));
    pointsInRect.push_back(Point2D(3.0f, 0.0f));
    pointsInRect.push_back(Point2D(0.0f, 2.0f));
  //literal edge cases
    pointsInRect.push_back(Point2D(1.5f, 2.0f));
    pointsInRect.push_back(Point2D(1.5f, 0.0f));
    pointsInRect.push_back(Point2D(3.0f, 1.0f));
    pointsInRect.push_back(Point2D(0.0f, 1.0f));

    std::vector<Point2D> pointsOutRect;
 // Points that should be outside the rectangle
    pointsOutRect.push_back(Point2D(100.0f, 100.0f)); //basic
    pointsOutRect.push_back(Point2D(2.9f, 1.9f)); //if x,y switched, would be in
  //edges
    pointsOutRect.push_back(Point2D( 1.5f, -1.0f));
    pointsOutRect.push_back(Point2D(-1.0f,  1.0f));
    pointsOutRect.push_back(Point2D( 4.0f,  1.0f));
    pointsOutRect.push_back(Point2D( 1.5f,  3.0f));
  //corners
    pointsOutRect.push_back(Point2D(-0.1f, -0.1f));
    pointsOutRect.push_back(Point2D( 3.1f,  2.1f));
    pointsOutRect.push_back(Point2D(-0.1f,  2.1f));
    pointsOutRect.push_back(Point2D( 3.1f, -0.1f));

    std::cout << std::endl 
              << "The following points should be OUTSIDE the rectangle: "
              << std::endl;
    for (unsigned i = 0; i < pointsOutRect.size(); i++){
        std::cout << "\tPoint #" << std::setw(2) << i+1 << " (" << std::setw(4) 
                  << pointsOutRect[i].x() << ", " << std::setw(4)
                  << pointsOutRect[i].y() << ") is";
        if (testRect.add_point(pointsOutRect[i])){
            std::cout << " inside ";
        } else {
            std::cout << " outside ";
        }
        std::cout << "testRect" << std::endl;
        testRect2.add_point(pointsOutRect[i]);
    }


    std::cout << "The following points should be INSIDE the rectangle: "
              << std::endl;
    for (unsigned i = 0; i < pointsInRect.size(); i++){
        std::cout << "\tPoint #" << std::setw(2) << i+1 << " (" << std::setw(4) 
                  << pointsInRect[i].x() << ", " << std::setw(4) 
                  << pointsInRect[i].y() << ") is";
        if (testRect.add_point(pointsInRect[i])){
            std::cout << " inside ";
        } else {
            std::cout << " outside ";
        }
        std::cout << "testRect" << std::endl;
        testRect2.add_point(pointsInRect[i]);
    }

    std::cout << "----------------------" << std::endl;

    std::cout << "The following points are inside tesRect: "
              << std::endl;
    const std::vector<Point2D>& contained = testRect.points_contained();
    for (unsigned i = 0; i < contained.size(); i++){
        std::cout << "\t (" << std::setw(4) << contained[i].x() << ", " 
                  << std::setw(4) << contained[i].y() 
                  << ")" << std::endl;
    }

    std::cout << "The following points are inside tesRect2: "
              << std::endl;
    const std::vector<Point2D>& contained2 = testRect2.points_contained();
    for (unsigned i = 0; i < contained2.size(); i++){
        std::cout << "\t (" << std::setw(4) << contained2[i].x() << ", " 
                  << std::setw(4) << contained2[i].y() 
                  << ")" << std::endl;
    }


    std::cout << "The following points are in both rectangles: "
              << std::endl;

    std::vector<Point2D> inBoth = points_in_both(testRect, testRect2);
    for (unsigned i = 0; i < inBoth.size(); i++){
        std::cout << "\t (" << std::setw(4) << inBoth[i].x() << ", " 
                  << std::setw(4) << inBoth[i].y() << ")" 
                  << std::endl;
    }
    

    return 0;
}
