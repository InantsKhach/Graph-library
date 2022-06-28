
#ifndef ABSTRACT_MAZE_HPP
#define ABSTRACT_MAZE_HPP

#include <ostream>
#include <vector>

#include "types.hpp"

// Forward declarations
class QGraphicsScene;

class AbstractMaze
{
public:
    /// In which directions moves are possible.
    enum class Direction : unsigned char {
        LEFT, 
        RIGHT,
        DOWN,
        UP
    };

    /// How a path in the maze is represented.
    typedef std::vector< Cell > PathType;

public:
    /// Returns width of the maze.
    virtual int width() const = 0;

    /// Returns height of the maze.
    virtual int height() const = 0;

    /// Returns if cell 'pt' is kind of 'free' and can be walked over.
    virtual bool canBeOn( const Cell& pt ) const = 0;

    /// Returns if inside the maze we can move from cell 'pt' in direction 'dir'.
    virtual bool canGoFrom( const Cell& pt,  Direction dir ) const = 0;

    /// Returns value of cell 'pt'.
    virtual double cellValue( const Cell& pt ) const = 0;

    /// Outputs maze into console stream 'ostr'.
    virtual void print( std::ostream& ostr ) const = 0;

    /// Outputs maze into console stream 'ostr', with path 'p'.
    virtual void printWithPath( std::ostream& ostr, const PathType& p ) const = 0;

    virtual void displayOnScene( QGraphicsScene* s, 
            const PathType& p = PathType() ) const = 0;
};

#endif // ABSTRACT_MAZE_HPP
