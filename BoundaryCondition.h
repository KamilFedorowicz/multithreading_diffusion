#pragma once
#include "Field.h"

// this file (and the corresponding cpp file stores different implementation of the boundary condition class)

enum class Wall
{
    east,
    west,
    north,
    south
};

class BoundaryCondition
{
public:
    virtual void apply(Field& field, Wall wall) const = 0;
    virtual ~BoundaryCondition() = default;
};

class DirichletCondition: public BoundaryCondition
{
public:
    DirichletCondition(double val): value(val){}
    
    void apply(Field& field, Wall wall) const override;
    
private:
    double value;
};

