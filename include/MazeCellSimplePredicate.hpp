
#ifndef MAZE_CELL_SIMPLE_PREDICATE_HPP
#define MAZE_CELL_SIMPLE_PREDICATE_HPP

#include "AbstractVertexPredicate.hpp"
#include "types.hpp"
#include <utility>

class MazeGraphRepresentation;


/// This is the simplest predicate for shortest path estimation, for graphs, 
///   which were constructed from maze.
/// Returns estimation based on manhattan distance of current point and 
///   target point.
class MazeCellSimplePredicate : public AbstractVertexPredicate
{
public:
	/// Constructor
	/// As argument takes the Maze-Graph representation, which will be used when 
	///   providing estimates for different vertices.
	MazeCellSimplePredicate( const MazeGraphRepresentation* graphRep )
		: _graphRep( graphRep )
		{ }

    /// virtual destructor
    virtual ~MazeCellSimplePredicate(){};


	/// Sets that the target point in maze is assumed to be 'arg'.
	void setTarget( const Cell& arg );

	/// Returns the target point in the maze.
	Cell getTarget() const;

	virtual double operator()( int u ) const;

protected:
	const MazeGraphRepresentation* _graphRep;

	/// The target point in the maze.
	Cell _target;
};


#endif // MAZE_CELL_SIMPLE_PREDICATE_HPP
