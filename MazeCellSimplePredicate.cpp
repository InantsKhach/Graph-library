#include "MazeCellSimplePredicate.hpp"
#include "MazeGraphRepresentation.hpp"
#include <cstdlib>

void MazeCellSimplePredicate::setTarget( const Cell& arg  )
{
    _target = arg;
}

Cell MazeCellSimplePredicate::getTarget() const
{
    return _target;
}

double MazeCellSimplePredicate::operator()( int u ) const 
{
    Cell point = _graphRep->vertexToCell( u );
    return point.manhattenDistance( _target );
}



