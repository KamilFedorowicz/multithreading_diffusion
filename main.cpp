#include <iostream>
#include <vector>
#include "Grid.h"
#include "Field.h"
#include "BoundaryCondition.h"
#include "Laplacian.h"
#include "DiffusionSolver.h"

int main(int argc, const char * argv[]) {

    int nx = 50;
    int ny = 50;

    double xStart = 0.0;
    double yStart = 0.0;
    double xEnd = 1.0;
    double yEnd = 1.0;

    Grid grid(xStart, yStart, xEnd, yEnd, nx, ny);
    
    Field field(grid);

    
    BoundaryConditions bcs;
    bcs.set(Wall::west, std::make_unique<DirichletCondition>(1.0));
    bcs.set(Wall::east, std::make_unique<DirichletCondition>(0.0));
    bcs.set(Wall::north, std::make_unique<DirichletCondition>(1.0));
    bcs.set(Wall::south, std::make_unique<ZeroGradientCondition>());
    //bcs.set(Wall::south, std::make_unique<DirichletCondition>(0.0));
    
    field.setQuadraticField(grid);
    
    field.printField();

    
    DiffusionSolver solver = DiffusionSolver(1, 1e-5, 10000);
    solver.iterate(field, grid, bcs);
    
    std::string path = "/Users/Kamil/Desktop/cpp_projects/diffusion_multithreading/diffusion_multithreading/res.vtk";
    
    writeVTK(field, grid, path);
    
    
    return 0;
}
