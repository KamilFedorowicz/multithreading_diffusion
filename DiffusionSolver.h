#pragma once

#include "Field.h"
#include "Grid.h"
#include "Laplacian.h"
#include "BoundaryCondition.h"

class DiffusionSolver
{
public:
    DiffusionSolver(double diff_, double dt_);
    void step(const Field& current, Field& next, const Grid& grid, BoundaryConditions& bcs) const;
    
private:
    double diffusivity, dt;
    
};
