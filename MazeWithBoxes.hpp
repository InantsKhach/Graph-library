#ifndef MAZE_WITH_BOXES_HPP
#define MAZE_WITH_BOXES_HPP

#include <ostream>
#include <vector>
#include <utility>
#include "types.hpp"
#include "utility.hpp"
#include "AbstractMaze.hpp"

// Forward declarations
class QGraphicsScene;


/// This class represents a 2D rectangular maze.
class MazeWithBoxes : public AbstractMaze
{

private:

	// Matrix to keep the Maze
	// 0 is the value of the starting point of the Maze, or the points which do not any resource 
	// -1 value means that in that point there is a Wall
	std::vector< std::vector< int > > maze;
public:
	/// Constructor
	/// @param w Width of the maze. Cells will be labeled [0, w).
	/// @param h Height of the maze. Cells will be labeles [0, h).
	MazeWithBoxes( int w, int h );

    /// virtual destructor
    virtual ~MazeWithBoxes(){};

	/// Returns width of the maze.
	virtual int width() const;

	/// Returns height of the maze.
	virtual int height() const;

	/// Returns value of cell 'pt'.
    virtual double cellValue( const Cell& pt ) const;

	/// Returns if cell 'pt' is kind of 'free' and can be walked over.
    virtual bool canBeOn( const Cell& pt ) const;

	/// Returns if inside the maze we can move from cell 'pt' in direction 'dir'.
    virtual bool canGoFrom( const Cell& pt,  Direction dir ) const;

	/// Sets that cell pt will be a wall.
	void setWall( Cell pt );

	/// Sets that cell pt will be blank.
	void setBlank( Cell pt, int cost = 1 );

	/// Sets that there will be no walls in the maze
	void setOpen();

	/// Prints the maze into output stream 'ostr'.
	virtual void print( std::ostream& ostr ) const;

	/// Prints the maze and specified 'path' on it intou output stream 'ostr'.
	/// The path is given as a sequence of cells, each identified as (x,y).
	virtual void printWithPath( std::ostream& ostr, 
									const PathType& p ) const;

	//virtual void displayOnScene( QGraphicsScene* s,
	//		const PathType& p = PathType() ) const;
};


#endif // MAZE_WITH_BOXES_HPP
