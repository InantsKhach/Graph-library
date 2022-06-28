#include "Algorithms.hpp"
#include <queue>
#include <climits>
#include <iostream>

#define INF DBL_MAX



void dijkstra_worker( const AbstractGraphStorage& g, int s, int t, std::vector< int >& prev, std::vector< int >& path)
{
	if(s != t)
	{
		dijkstra_worker( g, s, prev[t], prev, path );
	}
	path.push_back(t);
}


void dijkstra( const AbstractGraphStorage& g, int s, int t, 
		std::vector< int >& path, 
		double& cost )
{

	typedef std::pair< double, int > TravelType;

	
    std::priority_queue< 
			TravelType, 
			std::vector< TravelType >, 
			std::greater< TravelType > > pq;

    std::vector< double > dist( g.V(), INF );

	std::vector< int > prev(g.V());
    

	dist[ s ] = 0;

	pq.push( std::make_pair( 0, s ) );

    while( !pq.empty() )
	{
		int u = pq.top().second;

		if( u == t )
		  break;
		
		pq.pop();

		std::vector< int > adj;
	    g.getAdjacentVertices( u, adj );
		std::vector< int >::iterator elem;
		for( elem = adj.begin(); elem != adj.end(); ++elem)
		{
			int v = *elem;
			double weigth = g.getEdgeValue( u, v );
			if( dist[v] > dist[u] + weigth)
			{
                dist[v] = dist[u] + weigth;
				pq.push( std::make_pair( dist[v], v ));
				prev[v] = u;
			}
		}
	}
    
	cost = dist[t];
	dijkstra_worker( g, s, t, prev, path );
}







void bfs( const AbstractGraphStorage& g, int s, int t, 
		std::vector< int >& path, double& cost )
{
    std::vector< bool > used(g.V(), false); 

	std::vector< int > prev(g.V());

	std::queue< int > q;
    
	used[s] = true;
	q.push( s );


	while( !q.empty() )
    {
		int u = q.front();
		if( u == t )
		  break;
		
		q.pop();
        std::vector< int > adj;
		g.getAdjacentVertices( u, adj );

		std::vector< int >::iterator i;


		for( i = adj.begin(); i != adj.end(); ++i)
		{
			if( !used[*i] )
			{
				used[*i] = true;
				q.push( *i );
				prev[*i] = u;
			}
		}

	}


	while( s != t )
	{
		cost += g.getEdgeValue( t, prev[t] );
		path.push_back( t );
		t = prev[t];
	}
	path.push_back( s );

	std::reverse( path.begin(), path.end() );
}







void dfs_worker( const AbstractGraphStorage& g, int s, int t, 
		std::vector< int >& path,  
		double& cost, 
		std::vector< bool >& visited )
{
	if( s == t ){
		path.push_back( s );
		cost += g.getEdgeValue( *(path.end() - 2), *(path.end() - 1) );
		throw "DFS finish";
	}
	visited[ s ] = true;
	std::vector< int > adj;
	g.getAdjacentVertices( s, adj );
	std::vector< int >::iterator i;
	//std::cout << "Before the for cycle\n";
	for( i = adj.begin(); i != adj.end(); ++i)
	{
		if( ! visited[ *i ] )
		{
			path.push_back( s );
			cost += g.getEdgeValue( s, *i );
			//std::cout << "Cost value is " << cost << "\n we are going to " << *i << '\n';
			dfs_worker( g, *i, t, path,  cost, visited );
			cost -= g.getEdgeValue( s, *i );
			//std::cout << "Cost value is " << cost << "\n left from " << *i << '\n';
			path.pop_back();
		}
	}

}

void dfs( const AbstractGraphStorage& g, int s, int t, 
		std::vector< int >& path, 
		double& cost )
{
	std::vector< bool > visited( g.V(), false ); // ?
	path.clear();
	cost = 0;
	try{
	   dfs_worker( g, s, t, path, cost, visited );
	}
	catch(const char* ){
       
	}

}


void aStar( const AbstractGraphStorage& g, const AbstractVertexPredicate& h, 
		int s, int t, std::vector< int >& path, double& cost )
{
	/// This object represents a partial travel, starting from 's' where
	/// 'first' is current cost of it, and
	/// 'second' is the current-final point.
	typedef std::pair< double, int > TravelType;

	std::priority_queue< 
			TravelType, 
			std::vector< TravelType >, 
			std::greater< TravelType > > pq;

	std::vector< double > dist( g.V(), INF );

	std::vector< int > prev(g.V());

	dist[ s ] = 0;

	pq.push( std::make_pair( 0, s ) );

	while( !pq.empty() )
	{

		int u = pq.top().second;
		pq.pop();

		if( u == t )
			break;

		std::vector< int > adj;
	    g.getAdjacentVertices( u, adj );
		std::vector< int >::iterator elem;
		for( elem = adj.begin(); elem != adj.end(); ++elem)
		{
			int v = *elem;
			// Now we are considering edge (u,v)
			double weigth = g.getEdgeValue( u, v );
			if( dist[v] > dist[u] + weigth )
			{
				dist[v] = dist[u] + weigth;
				double new_cost = dist[v] + h( v );
				pq.push( std::make_pair( new_cost, v ) );
				prev[v] = u;
			}
		}
	}

	cost = dist[t];
	while( s != t )
	{
		path.push_back( t );
		t = prev[t];
	}

	path.push_back( s );
	std::reverse( path.begin(), path.end() );
}

