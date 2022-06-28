
#ifndef MAZE_GRAPH_REPRESENTATION_HPP
#define MAZE_GRAPH_REPRESENTATION_HPP

#include <vector>
#include <utility>
#include <algorithm>

#include "types.hpp"

// Forward declaration

class AbstractMaze;
class AbstractGraphStorage;


/// This class links together Maze and Graph objects.
class MazeGraphRepresentation
{
public:
	typedef std::vector< int > GraphPath;

	typedef std::vector< Cell > MazePath;

public:
	/// Constructor
	/// Constructs graph from given maze 'mz', and stores it in 'g'.
	MazeGraphRepresentation( const AbstractMaze* mz, AbstractGraphStorage* g );

	/// Returns the maze, from which the graph was generated.
	const AbstractMaze* getMaze() const;

	/// Returns the generated graph.
	const AbstractGraphStorage* getGraph() const;

	/// Returns cell of the maze, corresponding to graph vertex 'u'.
	Cell vertexToCell( int u ) const;

	/// Returns vertex of the graph, corresponding to maze cell 'c'.
	int cellToVertex( const Cell& c ) const;

	GraphPath cellsToVertices( const MazePath& p ) const
	{
		GraphPath result( p.size() );
		std::transform( p.cbegin(), p.cend(), 
				result.begin(), 
			  [this](int u) { return vertexToCell(u); } );
	}

	MazePath verticesToCells( const GraphPath& p ) const 
	{
		MazePath result(p.size());
		std::transform(p.cbegin(), p.cend(),
			result.begin(),
			[this](const Cell& c) { return cellToVertex(c);});
	}

	// ...

protected:
	/// The maze, from which the graph was generated.
	const AbstractMaze* _maze;

	/// The generated graph.
	AbstractGraphStorage* _graph;
};


#endif // MAZE_GRAPH_REPRESENTATION_HPP
