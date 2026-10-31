#include "DiffusionSolver.h"


DiffusionSolver::DiffusionSolver(double diff_, double dt_, size_t iter_)
{
    diffusivity = diff_;
    dt = dt_;
    iterations = iter_;
}

void DiffusionSolver::step(const Field& current, Field& next, const Grid& grid, const BoundaryConditions& bcs) const
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
}

void DiffusionSolver::iterateMultithread(Field& current, const Grid& grid, const BoundaryConditions& bcs)
{
    Field next = Field(grid);
    
    for(size_t i = 0; i < iterations; i++)
    {
        stepMultithread(current, next, grid, bcs);
        std::swap(current, next);

        avgVals.push_back(next.calcFieldAverage());
    }
}

void DiffusionSolver::stepMultithread(const Field& current, Field& next, const Grid& grid, const BoundaryConditions& bcs) const
{
    int jMiddle = (int)(grid.get_ny()/2);
    
    std::thread thread1([&]()
    {
        updateRows(current, next, grid, 1, jMiddle);
    });
    
    std::thread thread2([&]()
    {
        updateRows(current, next, grid, jMiddle, grid.get_ny()-1);
    });
    
    thread1.join();
    thread2.join();
    
    bcs.apply(next);

}

// calculate rows jBegin up to, but not including jEnd
void DiffusionSolver::updateRows(
    const Field& current,
    Field& next,
    const Grid& grid,
    std::size_t jBegin,
    std::size_t jEnd) const
{
    for(std::size_t j = jBegin; j < jEnd; j++)
    {
        for(std::size_t i=1; i<grid.get_nx()-1; i++)
        {
            next(i,j) = current(i,j) + calcLaplacian(current, grid, i, j) * diffusivity * dt;
        }
    }
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

