#include "Laplacian.h"

// we are writing a function to calculate laplacian for a single point because we have multithreading in mind
double calcLaplacian(const Field& field, const Grid& grid, size_t i, size_t j)
{
    size_t nx = field.get_nx();
    size_t ny = field.get_ny();
    double dx = grid.get_dx();
    double dy = grid.get_dy();
    
    double result = 0.0;
    
    if(i!=0 && i!=nx-1 && j!=0 && j!=ny-1)
    {
        result = (field(i+1,j) - 2*field(i,j) + field(i-1,j) )/(dx*dx) +
        (field(i, j+1) - 2*field(i,j) + field(i,j-1) )/ (dy * dy);
    }
    
    return result;
    
}
