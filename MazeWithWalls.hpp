#ifndef MAZE_WITH_WALLS_HPP
#define MAZE_WITH_WALLS_HPP

#include <ostream>
#include <vector>
#include <utility>
#include "AbstractMaze.hpp"
#include "utility.hpp"



/// This class represents a 2D rectangular maze, where walls are between his cells




class MazeWithWalls : public AbstractMaze
{

private:

    // Matrix to keep the cells of Maze
    std::vector< std::vector< int > > cells;

    // Matrix to keep the horizontal walls of Maze
    // true - in (i,j) means that there is a wall between cell (i,j) and cell (i,j+1)
    std::vector< std::vector< bool > >hor;
    
    // Matrix to keep the vertical walls of Maze
    // true - in (i,j) means that there is a wall between cell (i,j) and cell (i+1,j)
    std::vector< std::vector< bool > > ver;

public:
    /// Constructor
	/// @param w Width of the maze. Cells will be labeled [0, w).
	/// @param h Height of the maze. Cells will be labeles [0, h).
    MazeWithWalls( int w, int h );

    /// virtual destructor
    virtual ~MazeWithWalls(){};

    /// Returns width of the maze.
	virtual int width() const;

	/// Returns height of the maze.
	virtual int height() const;

    /// Returns the value of cell pt
	virtual double cellValue( const Cell& pt ) const;

    // Sets the value cost in cell pt
    void setval( Cell pt, int cost = 1 );

    /// Returns if cell 'pt' is kind of 'free' and can be walked over.
    virtual bool canBeOn( const Cell& pt ) const;

    /// Returns if inside the maze we can move from cell 'pt' in direction 'dir'.
    virtual bool canGoFrom( const Cell& pt,  Direction dir ) const;


    /// Returns if there is a wall between cell (x,y) and cell (x,y+1)
	bool isHorizontalWall( int x, int y ) const;

    /// Returns if there is a wall between cell (x,y) and cell (x+1,y)
    bool isVerticalWall( int x, int y ) const;


	/// Sets that there would be wall between cell (x,y) and cell (x,y+1)
	void setHorizontalWall( int x, int y );

    /// Sets that there would be wall between cell (x,y) and cell (x+1,y)
	void setVerticalWall( int x, int y );



    /// Sets that there would be blank between cell (x,y) and cell (x,y+1)
	void setHorizontalBlank( int x, int y );

    /// Sets that there would be blank between cell (x,y) and cell (x+1,y)
	void setVerticalBlank( int x, int y );

    /// Sets that all the cells of the maze will be wall
    void setClosed();



    /// Prints the maze into output stream 'ostr'.
	virtual void print( std::ostream& ostr ) const;

	/// Prints the maze and specified 'path' on it intou output stream 'ostr'.
	/// The path is given as a sequence of cells, each identified as (x,y).
	virtual void printWithPath( std::ostream& ostr, const PathType& p ) const;

    //virtual void displayOnScene( QGraphicsScene* s, const PathType& p = PathType() ) const;

};


#endif // MAZE_WITH_WALLS_HPP