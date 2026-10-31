#pragma once
#include <iostream>
class Grid{

public:
    Grid(double start_x, double start_y, double end_x, double end_y, std::size_t nx, std::size_t ny);

    std::size_t get_nx() const { return nx; }
    std::size_t get_ny() const { return ny; }

    double get_dx() const { return dx; }
    double get_dy() const { return dy; }

    double get_x(std::size_t i) const { return x[i]; }
    double get_y(std::size_t j) const { return y[j]; }
    
    double get_start_x() const { return start_x;}
    double get_start_y() const { return start_y;}
    
    void printGrid();
    
private:
    std::size_t nx, ny;
    std::vector<double> x, y;
    double start_x=0.0, start_y=0.0; // just some initial values
    double end_x = 1, end_y = 1;
    double dx, dy;
};
