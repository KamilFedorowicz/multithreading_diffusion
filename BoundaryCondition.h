#pragma once
#include "Field.h"

// this file (and the corresponding cpp file stores different implementation of the boundary condition class)

enum class Wall
{
    east = 0,
    west = 1,
    north = 2,
    south = 3
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

class ZeroGradientCondition: public BoundaryCondition
{
public:
    // ZeroGradientCondition(){}; // default constructor is not needed
    void apply(Field& field, Wall wall) const override;
};

class BoundaryConditions
{
public:
    void set(Wall wall, std::unique_ptr<BoundaryCondition> condition);
    void apply(Field& field) const;
    
private:
    std::array<std::unique_ptr<BoundaryCondition>, 4> conditions;
};
