#include "DiffusionSolver.h"

DiffusionSolver::DiffusionSolver(double diff_, double dt_)
{
    diffusivity = diff_;
    dt = dt_;
}

void DiffusionSolver::step(const Field& current, Field& next, const Grid& grid, BoundaryConditions& bcs) const
{
    for(int i=1; i<grid.get_nx()-1; i++)
    {
        for(int j=1; j<grid.get_ny()-1; j++)
        {
            next(i,j) = current(i,j) + calcLaplacian(current, grid, i, j) * diffusivity * dt;
        }
    }
    
    
    std::cout << "Printing the next field: " << std::endl;
    next.printField();
}

