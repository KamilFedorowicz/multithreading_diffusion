#include "Field.h"

Field::Field(const Grid& grid)
: nx(grid.get_nx()),
ny(grid.get_ny()),
values(nx * ny, 0.0)
{}

double& Field::operator()(std::size_t i, std::size_t j)
{
    return values[j * nx + i];
}

const double& Field::operator()(std::size_t i, std::size_t j) const
{
    return values[j * nx + i];
}

void Field::printField()
{
    for(size_t j = 0; j < ny; j++)
    {
        for(size_t i = 0; i< nx; i++)
        {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

void Field::setQuadraticField(const Grid& grid)
{
    for(int i=0; i<grid.get_nx(); i++)
    {
        for(int j=0; j<grid.get_ny(); j++)
        {
            (*this)(i,j) = pow(grid.get_x(i),2) + pow(grid.get_y(j),2);
        }
    }
}
    
    
    
    
    

