#include "MazeGraphRepresentation.hpp"
#include "AbstractGraphStorage.hpp"
#include "AbstractMaze.hpp"

MazeGraphRepresentation::MazeGraphRepresentation( const AbstractMaze* mz, AbstractGraphStorage* g )
{
    g->clear();

    int w = mz->width(), h = mz->height();

    for( int i = 0; i < w * h; ++i )
    {
        g->addVertex();
    }


    for( int i = 0; i < w ; ++i )
    {
        for( int j = 0; j < h ; ++j )
        {
            if( mz->canBeOn( Cell( i, j ) ) )
            {
                if( j != (h - 1) && mz->canGoFrom( Cell( i, j ), AbstractMaze::Direction::DOWN ) )
                {
                   double value = mz->cellValue( Cell( i, j + 1 ) ) + mz->cellValue( Cell( i, j ) );
                   g->addEdge( ( (i * h) + j ), ( ( i * h ) + j + 1 ), (value / 2) );
                }
                if( i != (w - 1) && mz->canGoFrom( Cell( i, j ), AbstractMaze::Direction::RIGHT ) )
                {
                   double value = mz->cellValue( Cell( i, j ) ) + mz->cellValue( Cell( i + 1, j ) );
                   g->addEdge( ( (i * h) + j ), (  ( (i + 1) * h ) + j ), (value / 2) ); 
                }
            }
        }
    }

    _maze = mz;
    _graph = g;
}


const AbstractMaze* MazeGraphRepresentation::getMaze() const
{
    return this->_maze;
}

const AbstractGraphStorage* MazeGraphRepresentation::getGraph() const 
{
    return this->_graph;
}

Cell MazeGraphRepresentation::vertexToCell( int u ) const 
{
    return Cell( ( u / _maze->height() ) , ( u % _maze->height() ) );
}

int MazeGraphRepresentation::cellToVertex( const Cell& c ) const 
{
    return (c.c * _maze->height() + c.r);
}