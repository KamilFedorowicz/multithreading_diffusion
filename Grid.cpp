#pragma once

#include <iostream>
#include <vector>
#include "Grid.h"
#include "Field.h"

Grid::Grid(double start_x, double start_y, double end_x, double end_y, std::size_t nx, std::size_t ny)
    :start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y), nx(nx), ny(ny) {
    dx = (end_x - start_x) / (nx - 1);
    dy = (end_y - start_y) / (ny - 1);

        for (int i = 0; i < nx; ++i){
            x.push_back(start_x + i * dx);
        }
        
        for (int i = 0; i < ny; ++i){
            y.push_back(start_y + i * dy);
        }
}

void Grid::printGrid()
{
    for(size_t i=0; i<x.size(); i++)
    {
        std::cout << "x: " << x[i] << std::endl;
    }
    
    for(size_t i=0; i<y.size(); i++)
    {
        std::cout << "y: " << y[i] << std::endl;
    }
}

