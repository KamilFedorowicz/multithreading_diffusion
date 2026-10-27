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
