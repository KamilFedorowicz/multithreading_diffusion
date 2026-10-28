#include "BoundaryCondition.h"


void DirichletCondition::apply(Field& field, Wall wall) const
{
    switch(wall)
    {
        case Wall::west:
            for(std::size_t j=0; j < field.get_ny(); j++)
            {
                field(0, j) = value;
            }
            break;
            
        case Wall::east:
            for(std::size_t j=0; j < field.get_ny(); j++)
            {
                field(field.get_nx()-1, j) = value;
            }
            break;
            
        case Wall::south:
            for(std::size_t i=0; i < field.get_nx(); i++)
            {
                field(i, field.get_ny()-1) = value;
            }
            break;
            
        case Wall::north:
            for(std::size_t i=0; i < field.get_nx(); i++)
            {
                field(i, 0) = value;
            }
            break;
            
        default:
            break;
    }

}

void ZeroGradientCondition::apply(Field& field, Wall wall) const
{
    switch(wall)
    {
        case Wall::west:
            for(std::size_t j=0; j < field.get_ny(); j++)
            {
                field(0, j) = field(1, j);
            }
            break;
            
        case Wall::east:
            for(std::size_t j=0; j < field.get_ny(); j++)
            {
                field(field.get_nx()-1, j) = field(field.get_nx()-2, j);
            }
            break;
            
        case Wall::south:
            for(std::size_t i=0; i < field.get_nx(); i++)
            {
                field(i, field.get_ny()-1) = field(i, field.get_ny()-2);
            }
            break;
            
        case Wall::north:
            for(std::size_t i=0; i < field.get_nx(); i++)
            {
                field(i, 0) = field(i, 1);
            }
            break;
            
        default:
            break;
    }
    
}

void BoundaryConditions::set(Wall wall, std::unique_ptr<BoundaryCondition> condition)
{
    conditions[static_cast<std::size_t>(wall)] = std::move(condition);
}

void BoundaryConditions::apply(Field& field) const
{
    for(int i = 0; i < conditions.size(); i++)
    {
        // check if the boundary condition exists
        if(conditions[i])
        {
            conditions[i]->apply(field, static_cast<Wall>(i));
        }
    }
}
