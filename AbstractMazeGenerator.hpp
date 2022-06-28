
#ifndef ABSTRACT_MAZE_GENERATOR_HPP
#define ABSTRACT_MAZE_GENERATOR_HPP

#include "types.hpp"

// Forward declaration
class MazeWithBoxes;
class MazeWithWalls;


/// This is abstract base class for all maze generators.
class AbstractMazeGenerator
{
public:
	/// Generates content into provided maze 'mz'.
	virtual void generate( MazeWithBoxes& mz, GenType& gen ) = 0;


	/// Generates content into provided maze of version 2
	virtual void generate( MazeWithWalls& mz, GenType& gen ) = 0;
};


#endif // ABSTRACT_MAZE_GENERATOR_HPP
