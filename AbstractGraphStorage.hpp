#ifndef ABSTRACT_GRAPH_STORAGE_HPP
#define ABSTRACT_GRAPH_STORAGE_HPP

#include <vector>
#include <utility>
#include "types.hpp"


/// This is the abstract base class for all types of graph representations.

class AbstractGraphStorage
{
public:
	/// How an edge is identified.
	// typedef std::pair< int, int > EdgeType;  
    // after include types.hpp do we need this typedef in the above line?

public:

	
	/// Virtual destructor
	virtual ~AbstractGraphStorage() {}

	/// Returns number of vertices.
	/// The vertices are labeled [0, V).
	virtual int V() const = 0;

	/// Returns number of edges.
	/// The edges are labeled [0, E).
	virtual int E() const = 0;

	/// Returns if there is an edge (u,v) in the graph.
	virtual bool hasEdge( int u, int v ) const = 0;

	/// Returns all edges in argument 'es'.
	virtual void getEdges( std::vector< EdgeType >& es ) const = 0;

	/// Returns all edges and their costs in argument 'es'.
	virtual void getEdges( std::vector< WeightedEdgeType >& es ) const = 0;

	/// Returns number of vertices, adjacent to 'u'.
	virtual int getAdjacentVerticesCount( int u ) const = 0;

	/// Returns all vertices which are adjacent to 'u', in the argument 'vs'.
	virtual void getAdjacentVertices( int u, std::vector< int >& vs ) const = 0;

	/// Erases all edges and vertices.
	virtual void clear() = 0;

	// 
	// Alteration of graph
	//

	/// Adds new vertex, and returns it's number.
	virtual int addVertex() = 0;

	/// Adds edge (u,v).
	virtual void addEdge( int u, int v, double cost = 1 ) = 0;

	/// Removed edge (u,v).
	virtual void removeEdge( int u, int v ) = 0;

	//
	// Methods, related to edge values.
	//

	virtual double getEdgeValue( int u, int v ) const = 0;

	virtual void setEdgeValue( int u, int v, double value ) = 0;

};
 

#endif // ABSTRACT_GRAPH_STORAGE_HPP
