#include "RandomizedDFS.hpp"
#include "MazeWithBoxes.hpp"
#include "MazeWithWalls.hpp"
#include <stack>
#include <random>
#include <algorithm>

void RandomizedDFS::generate( MazeWithBoxes& maze, GenType& gen )
{
    maze.setOpen();
    std::stack< Cell > s;
    std::vector< std::vector< bool > > visited( maze.width(), std::vector< bool >( maze.height(), false ) );
    s.push( Cell( 0, 0 ) );
    visited[0][0] = true;
    Cell targetCell( maze.width() - 1, maze.height() - 1 );

    while( !s.empty() )
    {
        Cell curCell = s.top();
        s.pop();
        if( curCell == targetCell )
        {
            break;
        }
        std::vector< Cell > neighbours = get_neighbours( curCell, maze );
        
        std::shuffle( neighbours.begin(), neighbours.end(), gen );
        for( int i = 0; i < neighbours.size(); ++i )
        {
            const auto& nb = neighbours[i];
            if( !visited[nb.c][nb.r] )
            {
                s.push( curCell );
                visited[nb.c][nb.r] = true;
                s.push( nb );
                break;
            }
        }
        
    }

    for( int i = 0; i < maze.width(); ++i )
        for( int j = 0; j < maze.height(); ++j )
            if( !visited[i][j] )
                maze.setWall( Cell(i, j) );
}

void RandomizedDFS::generate( MazeWithWalls& maze, GenType& gen )
{
    maze.setClosed();
    std::stack< Cell > s;
    std::vector< std::vector< bool > > visited( maze.width(), std::vector< bool >( maze.height(), false ));
    s.push( Cell( 0, 0 ) );
    visited[0][0] = true;

    while( !s.empty() )
    {
        Cell curCell = s.top();
        s.pop();
        std::vector< Cell > neighbours = get_neighbours( curCell, maze );
        
        std::shuffle( neighbours.begin(), neighbours.end(), gen );
        for( int i = 0; i < neighbours.size(); ++i )
        {
            const auto& nb = neighbours[i];
            if( !visited[nb.c][nb.r] )
            {
                s.push( curCell );
                if( curCell.c > nb.c )
                {
                    maze.setVerticalBlank( nb.c, nb.r );
                }
                else if( curCell.c < nb.c )
                {
                    maze.setVerticalBlank( nb.c - 1, nb.r );
                }
                else if( curCell.r > nb.r )
                {
                    maze.setHorizontalBlank( nb.c, nb.r );
                }
                else 
                {
                    maze.setHorizontalBlank( nb.c, nb.r - 1 );
                }

                visited[nb.c][nb.r] = true;
                s.push( nb );
                break;
            }
        }
    }

}

std::vector< Cell > RandomizedDFS::get_neighbours( Cell& p, MazeWithWalls& mz )
{
    std::vector< Cell > neighbours;

    if( p.c > 0 )
        neighbours.push_back( Cell(p.c - 1, p.r) );
    if( p.r > 0 )
        neighbours.push_back( Cell( p.c, p.r - 1 ) );
    if( p.c < mz.width() - 1 )
        neighbours.push_back( Cell( p.c + 1, p.r ) );
    if( p.r < mz.height() - 1 )
        neighbours.push_back( Cell( p.c, p.r + 1 ) );

    return neighbours;
}

std::vector< Cell > RandomizedDFS::get_neighbours( Cell& p, MazeWithBoxes& mz )
{
    std::vector< Cell > neighbours;

    if( p.c > 0 )
        neighbours.push_back( Cell( p.c - 1, p.r ) );
    if( p.r > 0 )
        neighbours.push_back( Cell( p.c, p.r - 1 ) );
    if( p.c < mz.width() - 1 )
        neighbours.push_back( Cell( p.c + 1, p.r ) );
    if( p.r < mz.height() - 1 )
        neighbours.push_back( Cell( p.c, p.r + 1 ) );

    return neighbours;
}