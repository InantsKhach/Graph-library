
#include <iomanip>

#include <QBrush>
#include <QPen>
#include <QString>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include "MazeWithBoxes.hpp"
#include "types.hpp"

MazeWithBoxes::MazeWithBoxes( int w, int h )
{
    maze.assign( w, std::vector< int >( h, 1 ) );
    maze[0][0] = 0;
}

int MazeWithBoxes::height() const
{
    return (maze.size() > 0) ? maze[0].size() : 0;
}

int MazeWithBoxes::width() const
{
    return maze.size();
}

double MazeWithBoxes::cellValue( const Cell& pt ) const 
{
    int x = pt.c, y = pt.r;
    if( x >= width() || y >= height() )
        throw "the point is out from the maze";
    
    return maze[x][y];
}

bool MazeWithBoxes::canBeOn( const Cell& pt ) const
{
    int x = pt.c, y = pt.r; 
    return maze[x][y] != -1;
}  

bool MazeWithBoxes::canGoFrom( const Cell& pt,
                                 Direction dir ) const 
{
    int x = pt.c, y = pt.r;
    switch ( dir )
    {
    case Direction::LEFT :
        if( pt.c == 0 )
          return false;
    
        return maze[x - 1][y] != -1;
    case Direction::RIGHT :
        if( pt.c == maze.size() - 1 )
          return false;

        return maze[x + 1][y] != -1; 
    case Direction::DOWN :
        if( pt.r == height() - 1 )
          return false;

        return maze[x][y + 1] != -1; 
    default:
        if( pt.r == 0 )
          return false;
        
        return maze[x][y - 1] != -1; 
    }
}

void MazeWithBoxes::setWall( Cell pt ) 
{
    int x = pt.c, y = pt.r; 
    maze[x][y] = -1;
}

void MazeWithBoxes::setBlank( Cell pt, int cost )
{
    int x = pt.c, y = pt.r; 
    maze[x][y] = cost;
}


void MazeWithBoxes::setOpen()
{
    maze.assign( width(), std::vector< int >( height(), 0 ) );
}

void MazeWithBoxes::print( std::ostream& ostr ) const 
{
    std::vector< int > digits( width() );

    for( int i = 0; i < width(); ++i )
    {
        int max = *std::max_element( maze[i].begin(), maze[i].end() );
        digits[i] =  digits_count( max );
    }

    for( int i = 0; i < height(); ++i )
    {
        for( int j = 0; j < width(); ++j )
        {
            ostr << std::setw( digits[j] );
            if( maze[j][i] == -1 )
                ostr << '#';
            else 
                ostr << maze[j][i];

            ostr << ' ';
        }        
        ostr << '\n';
    }   
}

void MazeWithBoxes::printWithPath( std::ostream& ostr, 
                                        const PathType& p ) const
{
    std::vector<std::vector<bool> > is_path(
            width(), 
            std::vector<bool>( height(), false ) );

    for ( const auto& path_item : p )
        is_path[ path_item.c ][ path_item.r ] = true;

    
    std::vector< int > digits( width() );

    for( int i = 0; i < width(); ++i )
    {
        int max = *std::max_element( maze[i].begin(), maze[i].end() );
        digits[i] =  digits_count( max );
    }


    for( int i = 0; i < height(); ++i )
    {
        for( int j = 0; j < width(); ++j )
        {
            ostr << std::setw( digits[j] );
            if ( is_path[j][i] )
                ostr << '*';
            else if( maze[j][i] == -1 )
                ostr << '#';
            else  
                ostr << maze[j][i];
            ostr << ' ';
        }        
        ostr << '\n';
    }
}



void MazeWithBoxes::displayOnScene( QGraphicsScene* s, const PathType& p ) const
{
    std::vector<std::vector<bool> > is_path(
            width(), 
            std::vector<bool>( height(), false ) );

    for ( const auto& path_item : p )
        is_path[ path_item.c ][ path_item.r ] = true;


    
    QBrush grayBrush( Qt::lightGray );
    QBrush pathBrush( Qt::darkYellow );
    QBrush closedBrush( Qt::black );
    QPen outlinePen( Qt::black );
    for( int i = 0; i < height(); ++i )
    {
        for( int j = 0; j < width(); ++j )
        {
            int space_w = (j == 0) ? 0 : SPACING;
            int space_h = (i == 0) ? 0 : SPACING;
            if( maze[j][i] == -1 )
            {
                s->addRect( j * CELL_W + space_w, i * CELL_H + space_h, CELL_W, CELL_H, outlinePen, closedBrush );
            }
            else 
            {
                QGraphicsItem* cellItem = 
                        s->addRect( j * CELL_W + space_w, i * CELL_H + space_h, CELL_W, CELL_H, outlinePen, grayBrush );
                QString str = QString::number( maze[j][i] );
                QGraphicsItem* textItem = 
                        s->addText( str, QFont( "Arial", 20 ) );
                textItem->setParentItem( cellItem );
            }
            
        }
    }

    for ( auto cur = p.begin() + 1; cur != p.end(); cur++ )
    {
        auto prev = cur - 1;
        int space_w = ( cur->c == 0 ) ? 0 : SPACING;
        int space_h = ( cur->r == 0 ) ? 0 : SPACING;
        s->addLine( prev->c * CELL_W + space_w, prev->r * CELL_H + space_h,
                                    cur->c * CELL_W + space_w, cur->r * CELL_H + space_h, outlinePen );
    }

}
