#include "AdjacencyListGraph.hpp"
#include <sstream>


AdjacencyListGraph::AdjacencyListGraph( int V ) {
    adj.resize(adj.size()); 
}

int AdjacencyListGraph::V() const{
    return adj.size();
}

int AdjacencyListGraph::E() const{
   int sum = 0;
   for( int v = 0; v < adj.size(); v++ )
   {
     sum += adj[v].size();   
   }
   return sum / 2;
}

bool AdjacencyListGraph::hasEdge( int u, int v ) const
{
    for( auto elem = adj[u].begin(); elem != adj[u].end(); elem++ )
    {
        if( (*elem).target == v ) 
          return true;
    }
    return false;
}

void AdjacencyListGraph::getEdges(std::vector<WeightedEdgeType> &es) const
{

    es.clear();
    for( int v = 0; v < adj.size(); v++ )
    {
       for( auto elem = adj[v].begin(); elem != adj[v].end(); ++elem )
       {
            int u =  elem->target;
            if( u < v )
            {  
                WeightedEdgeType(v, u, elem->cost);
            }
       }
    }
}

void AdjacencyListGraph::getEdges(std::vector<EdgeType> &es) const
{

    es.clear();
    for( int v = 0; v < adj.size(); v++ )
    {
       for( auto elem = adj[v].begin(); elem != adj[v].end(); ++elem )
       {
            int u =  elem->target;
            if( u < v )
            {  
               EdgeType w(v, u);
               es.push_back( w ); 
            }
       }
    }
}


int AdjacencyListGraph::getAdjacentVerticesCount( int u ) const
{
    return adj[u].size();
}

void AdjacencyListGraph::getAdjacentVertices( int u, std::vector< int > &vs )const
{
    vs.clear();
    for( auto elem = adj[u].begin(); elem != adj[u].end(); ++elem )
    {
        vs.push_back((*elem).target);
    }
}

void AdjacencyListGraph::clear()
{
   //for( int v = 0; v < adj.size(); ++v )
   //    adj[v].clear();
    adj.clear();
}

int AdjacencyListGraph::addVertex()
{
    std::list<WeightedEdgeType> dummy;
    adj.push_back( dummy );
    return adj.size();
}

void AdjacencyListGraph::addEdge( int u, int v, double cost ) // added cost argument
{
    WeightedEdgeType w1(u, v, cost), w2(v, u, cost);

    // w1.source = u;
    // w1.target = v; // made change here
    // w1.cost = cost;

    // WeightedEdgeType w2;

    // w2.source = v;
    // w2.target = u;
    // w2.cost = cost;
    
    adj[u].push_back( w1 );
    adj[v].push_back( w2 );


//    v.erase( 
//            std::remove( v.begin(), v.end(), 5 ), 
//            v.end() );

//    l.remove( 5 );
} 

void AdjacencyListGraph::removeEdge( int u, int v )
{
//    for(std::list<WeightedEdgeType>::iterator i = adj[u].begin(); i != adj[u].end(); ++i) 
//    {
//        if((*i).second == v)
//         {
//          adj[u].erase(i);
//          break; // made this change
//         }
//    }

   adj[u].remove_if(
            [v]( const WeightedEdgeType& e ) {
                return e.target == v;
            } );

    adj[v].remove_if(
            [u]( const WeightedEdgeType& e ) {
                return e.target == u;
            } );

//    for(std::list<WeightedEdgeType>::iterator i = adj[v].begin(); i != adj[v].end(); ++i) 
//    {
//        if((*i).second == u)
//         {
//          adj[v].erase(i);    
//          break; // made this change
//         }
//    }
}

double AdjacencyListGraph::getEdgeValue( int u, int v )const
{
    for( auto elem = adj[u].begin(); elem != adj[u].end(); ++elem)
    {
        if( (*elem).target == v)
          return (*elem).cost;
    }


    // made those changes
    {
        std::ostringstream oss;
        oss << "There is no connection between " << u << " and " << v;
        throw oss.str();
    }
}

void AdjacencyListGraph::setEdgeValue( int u, int v, double value )
{
   for( auto elem = adj[u].begin(); elem != adj[u].end(); ++elem)
   {
        if( (*elem).target == v )
        {
         (*elem).cost = value;
           break; // made this change
        }
   }

   for( auto elem = adj[v].begin(); elem != adj[v].end(); ++elem)
   {
        if( (*elem).target == u )
        {
         (*elem).cost = value;
         return; // made this change 
        }
   }

    // made those changes
   {
      std::ostringstream oss;
      oss << "There is no connection from " << v << " to " << u;
      throw oss.str();
   }
}