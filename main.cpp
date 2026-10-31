#include <iostream>
#include <vector>
#include "Grid.h"
#include "Field.h"
#include "BoundaryCondition.h"
#include "Laplacian.h"
#include "DiffusionSolver.h"
#include <chrono>

int main(int argc, const char * argv[]) {

    int nx = 1000;
    int ny = 1000;
    double dt = 1e-1;
    int iterations  = 100;

    double xStart = 0.0;
    double yStart = 0.0;
    double xEnd = 1.0;
    double yEnd = 1.0;

    Grid grid(xStart, yStart, xEnd, yEnd, nx, ny);

    
    BoundaryConditions bcs;
    bcs.set(Wall::west, std::make_unique<DirichletCondition>(1.0));
    bcs.set(Wall::east, std::make_unique<DirichletCondition>(0.0));
    bcs.set(Wall::north, std::make_unique<DirichletCondition>(1.0));
    bcs.set(Wall::south, std::make_unique<ZeroGradientCondition>());
    //bcs.set(Wall::south, std::make_unique<DirichletCondition>(0.0));
    
    //field.setQuadraticField(grid);

    // SERIAL CALCULATION
    Field fieldSerial(grid);
    DiffusionSolver serialSolver = DiffusionSolver(1, dt, iterations);
    auto ts0 = std::chrono::steady_clock::now();
    serialSolver.iterate(fieldSerial, grid, bcs);
    auto ts1 = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> serialElapsed = ts1 - ts0;
    
    std::cout << "Serial calculation time: "
              << serialElapsed.count()
              << " s\n";
    
    std::string path = "/Users/Kamil/Desktop/cpp_projects/diffusion_multithreading/diffusion_multithreading/resSerial.vtk";
    writeVTK(fieldSerial, grid, path);
    
    // MULTITHREAD CALCULATION
    Field fieldMultithread(grid);
    DiffusionSolver multithreadSolver = DiffusionSolver(1, dt, iterations);
    ts0 = std::chrono::steady_clock::now();
    multithreadSolver.iterateMultithread(fieldMultithread, grid, bcs, 3);
    ts1 = std::chrono::steady_clock::now();

    std::chrono::duration<double> multithreadElapsed = ts1 - ts0;
    
    std::cout << "Multithread calculation time: "
              << multithreadElapsed.count()
              << " s\n";
    
    path = "/Users/Kamil/Desktop/cpp_projects/diffusion_multithreading/diffusion_multithreading/resMultithread.vtk";
    writeVTK(fieldMultithread, grid, path);
    
    std::cout << "Serial, multithread averages: " << fieldSerial.calcFieldAverage() << " " << fieldMultithread.calcFieldAverage() << std::endl;
    
    return 0;
}
