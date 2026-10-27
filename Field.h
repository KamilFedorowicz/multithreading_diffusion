#pragma once
#include "Grid.h"
#include <iostream>

class Field
{
public:
    explicit Field(const Grid& grid);
    void printField();
    double& operator()(std::size_t i, std::size_t j);
    const double& operator()(std::size_t i, std::size_t j) const;
    
    size_t get_nx() const{ return nx;}
    size_t get_ny() const{ return ny;}
    
private:
    std::size_t nx, ny;
    std::vector<double> values;
};
