#include <iostream>
#include <vector>
#include "Grid.h"
#include "Field.h"
#include "BoundaryCondition.h"

int main(int argc, const char * argv[]) {

    int nx = 10;
    int ny = 20;

    double xStart = 0.0;
    double yStart = 0.0;
    double xEnd = 1.0;
    double yEnd = 1.0;

    Grid grid(xStart, yStart, xEnd, yEnd, nx, ny);
    
    Field field(grid);

    
    DirichletCondition bcWest(1);
    bcWest.apply(field, Wall::west);
    
    DirichletCondition bcEast(2);
    bcEast.apply(field, Wall::east);
    
    DirichletCondition bcNorth(3);
    bcNorth.apply(field, Wall::north);
    
    DirichletCondition bcSouth(4);
    bcSouth.apply(field, Wall::south);
    
    field.printField();
    

    
    
    
    return 0;
}
