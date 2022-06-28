#ifndef MAZE_CELL_PREDICATE_STRAIGHT_LINE_HPP
#define MAZE_CELL_PREDICATE_STRAIGHT_LINE_HPP

#include "MazeCellSimplePredicate.hpp"
#include "types.hpp"
#include <utility>

class MazeGraphRepresentation;

class MazeCellPredicateStraightLine : public MazeCellSimplePredicate
{
public:
    /// Constructor
	/// As argument takes the Maze-Graph representation, which will be used when 
	///   providing estimates for different vertices.
	MazeCellPredicateStraightLine( const MazeGraphRepresentation* graphRep )
		: MazeCellSimplePredicate( graphRep )
		{ }

    /// Sets that the start point in maze is assumed to be 'arg'.
    void setStart( const Cell& arg );

    /// Returns the start point in the maze
    Cell getStart() const;

	virtual double operator()( int u ) const;

protected:

    /// Start point in the maze.
    Cell _start;
};


#endif // MAZE_CELL_PREDICATE_STRAIGHT_LINE_HPP