#include "MazeGraphRepresentation.hpp"
#include "MazeCellPredicateStraightLine.hpp"
#include <cstdlib>

void MazeCellPredicateStraightLine::setStart( const Cell& arg  )
{
    _start = arg;
}


Cell MazeCellPredicateStraightLine::getStart() const
{
    return _start;
}

double MazeCellPredicateStraightLine::operator()( int u ) const
{
    double heuristic = MazeCellSimplePredicate::operator()( u );
    Cell point = _graphRep->vertexToCell( u );
    double dx1 = point.c - _target.c;
    double dy1 = point.r - _target.r;
    double dx2 = _start.c - _target.c;
    double dy2 = _start.r - _target.r;
    double cross = abs( dx1 * dy2 - dx2 * dy1 );
    heuristic += cross * 0.001;
    return heuristic;
}