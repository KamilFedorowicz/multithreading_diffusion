#include "DiffusionSolver.h"

DiffusionSolver::DiffusionSolver(double diff_, double dt_, size_t iter_)
{
    diffusivity = diff_;
    dt = dt_;
    iterations = iter_;
}

void DiffusionSolver::step(Field& current, Field& next, const Grid& grid, const BoundaryConditions& bcs) const
{
    for(int i=1; i<grid.get_nx()-1; i++)
    {
        for(int j=1; j<grid.get_ny()-1; j++)
        {
            next(i,j) = current(i,j) + calcLaplacian(current, grid, i, j) * diffusivity * dt;
        }
    }
    
    bcs.apply(next);

}

void DiffusionSolver::iterate(Field& current, const Grid& grid, const BoundaryConditions& bcs)
{
    Field next = Field(grid);
    
    for(size_t i = 0; i < iterations; i++)
    {
        step(current, next, grid, bcs);
        std::swap(current, next);

        avgVals.push_back(next.calcFieldAverage());
    }
    printHistory();
}

void DiffusionSolver::printHistory()
{
    std::cout << "Average values: \n";
    for(int i=0; i < avgVals.size(); i++)
    {
        if(i%100 == 0)
        {
            std::cout << avgVals[i] << " ";
        }
    }
    std::cout << std::endl;
}

