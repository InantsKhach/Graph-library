#include "AdjacencyMatrixGraph.hpp"

AdjacencyMatrixGraph::AdjacencyMatrixGraph( int size ) 
{
    data.assign( size, std::vector< double >( size, 0 ) );
}

int AdjacencyMatrixGraph::V() const
{
   return data.size();
}

int AdjacencyMatrixGraph::E() const 
{
    int sum = 0;
    for( int i = 0; i < data.size() - 1; ++i )
    {
        for( int j = i + 1; j < data.size(); ++j)
        {
            if(data[i][j] != 0)
              ++sum;
        }
    }
    return sum;
}

bool AdjacencyMatrixGraph::hasEdge( int u, int v ) const
{
   if(data[u][v] != 0)
     return true;
    
    return false;
}

void AdjacencyMatrixGraph::getEdges( std::vector<WeightedEdgeType> &es ) const
{

    es.clear();

   for( int i = 0; i < data.size() - 1; ++i )
   {
       for( int j = i + 1; j < data.size(); ++j )
       {
           if(data[i][j] != 0)
             es.push_back(WeightedEdgeType(i, j, data[i][j]));
       }
   }
}

void AdjacencyMatrixGraph::getEdges( std::vector<EdgeType> &es ) const
{

    es.clear();

   for( int i = 0; i < data.size() - 1; ++i )
   {
       for( int j = i + 1; j < data.size(); ++j )
       {
           if(data[i][j] != 0)
             es.push_back(EdgeType(i, j));
       }
   }
}

int AdjacencyMatrixGraph::getAdjacentVerticesCount( int u ) const
{
    int sum = 0;
    for( int i = 0; i < data.size(); ++i)
    {
        if( data[u][i] != 0)
          sum++;
    }
    return sum;
}

void AdjacencyMatrixGraph::getAdjacentVertices( int u, std::vector<int> &vs ) const
{

    vs.clear();

    for( int i = 0; i < data.size(); ++i )
    {
        if( data[u][i] != 0 )
          vs.push_back( i );
    }
}

void AdjacencyMatrixGraph::clear()
{
    //for( int i = 0; i < data.size(); ++i)
    //{
    //    data[i].clear();
    //}

    data.clear();
}

int AdjacencyMatrixGraph::addVertex()
{
    data.resize( data.size() + 1 );

    for( int i = 0; i < data.size(); ++i )
    {
        data[i].resize( data.size() );
    }

    return data.size();
}

void AdjacencyMatrixGraph::addEdge( int u, int v, double cost )
{
   data[u][v] = cost;
   data[v][u] = cost;
}

void AdjacencyMatrixGraph::removeEdge( int u, int v )
{
    data[u][v] = 0;
    data[v][u] = 0;
}

double AdjacencyMatrixGraph::getEdgeValue( int u, int v ) const
{
    return data[u][v];
}

void AdjacencyMatrixGraph::setEdgeValue( int u, int v, double value )
{
    data[u][v] = value;
    data[v][u] = value;
}


