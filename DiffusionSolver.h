#pragma once

#include "Field.h"
#include "Grid.h"
#include "Laplacian.h"
#include "BoundaryCondition.h"
#include <thread>

class DiffusionSolver
{
public:
    DiffusionSolver(double diff_, double dt_, size_t iter);
    void step(const Field& current, Field& next, const Grid& grid, const BoundaryConditions& bcs) const;
    void iterate(Field& current, const Grid& grid, const BoundaryConditions& bcs);
    void printHistory();
    
    // multuthreading equivalents
    void stepMultithread(const Field& current, Field& next, const Grid& grid, const BoundaryConditions& bcs, int nThreads) const;
    void iterateMultithread(Field& current, const Grid& grid, const BoundaryConditions& bcs, int nThreads);
    void updateRows(const Field& current, Field& next, const Grid& grid, std::size_t jBegin, std::size_t jEnd) const;
    
    
private:
    double diffusivity, dt;
    size_t iterations;
    std::vector<double> avgVals{};
    
};
