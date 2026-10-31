#pragma once

#include "Field.h"
#include "Grid.h"
#include "Laplacian.h"
#include "BoundaryCondition.h"

class DiffusionSolver
{
public:
    DiffusionSolver(double diff_, double dt_, size_t iter);
    void step(Field& current, Field& next, const Grid& grid, const BoundaryConditions& bcs) const;
    void iterate(Field& current, const Grid& grid, const BoundaryConditions& bcs);
    void printHistory();
    
private:
    double diffusivity, dt;
    size_t iterations;
    std::vector<double> avgVals{};
    
};
