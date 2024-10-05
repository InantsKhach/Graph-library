#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>

#include "AbstractGraphStorage.hpp"
#include "AbstractVertexPredicate.hpp"



/**
 * Runs Dijkstra shortest path algorithm, on graph 'g', from vertex 's' to 't'.
 * Returns the shortes path as sequence of vertices in argument 'path', and 
 * its total cost in argument 'cost'.
 */

void dijkstra( const AbstractGraphStorage& g, int s, int t, 
		std::vector< int >& path, 
		double& cost );



/**
 * Runs breadth-first-search on graph 'g', from vertex 's' to 't'.
 * Assumes that all edges of this graph have same length.
 * Returns the shortes path as sequence of vertices in argument 'path', and
 * its total cost in argument 'cost'.
 */


void bfs( const AbstractGraphStorage& g, int s, int t, 
		std::vector< int >& path, double& cost );



/**
 * Runs depth-first-search on graph 'g', from vertex 's' to 't'.
 * Returns the resulted path as sequence of vertices in argument 'path', and
 * its total cost in argument 'cost'.
 * Note, this is not expected to be the shortest path.
 */


void dfs( const AbstractGraphStorage& g, int s, int t, 
		std::vector< int >& path, 
		double& cost );



/**
 * Runs A* graph search algorithm on 'g', with path cost estimation functor 'h', 
 * from vertex 's' to 't'.
 * Returns the resulted path as sequence of vertices in argument 'path', and
 * its total cost in argument 'cost'.
 */
void aStar( const AbstractGraphStorage& g, const AbstractVertexPredicate& h, 
		int s, int t, 
		std::vector< int >& path,
		double& cost );



#endif // ALGORITHMS_HPP
