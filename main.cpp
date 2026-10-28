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

    
    BoundaryConditions bcs;
    bcs.set(Wall::west, std::make_unique<DirichletCondition>(1.0));
    bcs.set(Wall::east, std::make_unique<DirichletCondition>(2.0));
    bcs.set(Wall::north, std::make_unique<DirichletCondition>(3.0));
    bcs.set(Wall::south, std::make_unique<DirichletCondition>(4.0));
    
    bcs.apply(field);
    field.printField();
    
    bcs.set(Wall::north, std::make_unique<ZeroGradientCondition>());
    bcs.set(Wall::south, std::make_unique<ZeroGradientCondition>());
    bcs.apply(field);
    
    field.printField();
    

    
    
    
    return 0;
}
