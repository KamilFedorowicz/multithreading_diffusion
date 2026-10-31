#pragma once
#include "Grid.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

class Field
{
public:
    explicit Field(const Grid& grid);
    void printField();
    double& operator()(std::size_t i, std::size_t j);
    const double& operator()(std::size_t i, std::size_t j) const;
    void setQuadraticField(const Grid& grid);
    
    size_t get_nx() const{ return nx;}
    size_t get_ny() const{ return ny;}
    void saveCSV(const std::string& filename) const;
    double calcFieldAverage(); // just a function to check convergence
    
private:
    std::size_t nx, ny;
    std::vector<double> values;
};

void writeVTK(
    const Field& field,
    const Grid& grid,
              const std::string& filename);
