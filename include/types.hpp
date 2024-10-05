#ifndef TYPE_HPP
#define TYPE_HPP

#include <utility>
#include <cstdlib>
#include <random>


/// Type of random-numbers-generator, beign used through the application.
typedef std::default_random_engine GenType;


struct HalfEdgeType
{
    int edge;
};

struct EdgeType
{
    EdgeType( int source, int target ) : source( source ), target( target ) {}
    int source;
    int target;
};

struct HalfWeightedEdgeType : public HalfEdgeType
{
    double cost;
}; 

struct WeightedEdgeType : public EdgeType
{
    WeightedEdgeType( int source, int target, double cost ) : 
       EdgeType( source, target ), cost( cost ) {}
    double cost;
};

struct Cell
{
    Cell( int c, int r ) : c( c ), r( r ) {} 
    Cell( ) {}
    bool operator==( const Cell& comp)
    {
        return this->c == comp.c && this->r == comp.r;
    }

    int manhattenDistance( const Cell& other ) const
    {
        return abs( this->c - other.c ) + abs( this->r - other.r );
    }
    int c;
    int r;
};

const int CELL_W = 20;
const int CELL_H = 20;
const int SPACING = 2;



#endif