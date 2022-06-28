#ifndef AdjacencyMatrixGraph_HPP
#define AdjacencyMatrixGraph_HPP

#include "AbstractGraphStorage.hpp"

class AdjacencyMatrixGraph : public AbstractGraphStorage{
 private:
   std::vector< std::vector< double > > data;

 public:
   AdjacencyMatrixGraph( int size );

   virtual ~AdjacencyMatrixGraph(){}

   virtual int V() const;

   virtual int E() const;

   virtual bool hasEdge( int u, int v )const;

   virtual void getEdges( std::vector< EdgeType >& es )const;

   virtual void getEdges( std::vector< WeightedEdgeType >& es )const;

   virtual int getAdjacentVerticesCount( int u ) const;

   virtual void getAdjacentVertices( int u, std::vector< int >& vs ) const;

   virtual void clear();

   virtual int addVertex();

   virtual void addEdge( int u, int v, double cost = 1 );

   virtual void removeEdge( int u, int v );

   virtual double getEdgeValue( int u, int v ) const;

   virtual void setEdgeValue( int u, int v, double value );


};

#endif