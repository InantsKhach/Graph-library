#include "MazeWithWalls.hpp"
//#include <QBrush>
//#include <QPen>
//#include <QString>
//#include <QFont>
//#include <QGraphicsItem>
//#include <QGraphicsScene>

#include <algorithm>
#include <iomanip>

MazeWithWalls::MazeWithWalls( int w, int h )
{
    cells.assign( w, 
              std::vector< int >( h , 1 ) );
    cells[0][0] = 0;

    hor.assign( w, 
            std::vector< bool >( h-1, false ) );

    ver.assign( w - 1, 
            std::vector< bool >( h, false ) );
}

int MazeWithWalls::height() const
{
    return (cells.size() > 0) ? cells[0].size() : 0;
}

int MazeWithWalls::width() const
{
    return cells.size();
}

double MazeWithWalls::cellValue( const Cell& pt ) const 
{
    int x = pt.c, y = pt.r;
    if( x >= width() || y >= height() )
        throw "the point is out from the maze";
    
    return cells[x][y];
}

void MazeWithWalls::setval( Cell pt, int cost )
{
    int x = pt.c, y = pt.r;
    if( x >= width() || y >= height() )
        throw "the point is out from the maze";

    cells[x][y] = cost;
}


bool MazeWithWalls::isHorizontalWall( int x, int y ) const
{
    return hor[x][y];
}

bool MazeWithWalls::isVerticalWall( int x, int y ) const 
{
    return ver[x][y];
}


void MazeWithWalls::setHorizontalWall( int x, int y )
{
    hor[x][y] = true;
}

void MazeWithWalls::setHorizontalBlank( int x, int y )
{
    hor[x][y] = false;
}

void MazeWithWalls::setVerticalWall( int x, int y )
{
    ver[x][y] = true;
}

void MazeWithWalls::setVerticalBlank( int x, int y )
{
    ver[x][y] = false;
} 

void MazeWithWalls::setClosed()
{
    hor.assign( width(), 
            std::vector< bool >( height() - 1, true ) );

    ver.assign( width() - 1, 
            std::vector< bool >( height(), true ) );
}


bool MazeWithWalls::canBeOn( const Cell& ) const 
{
    return true;
}


bool MazeWithWalls::canGoFrom( const Cell& pt, 
                                            Direction dir ) const 
{
    int x = pt.c, y = pt.r;

    switch( dir )
    {
        case Direction::LEFT:
            if( pt.c == 0 )
              return false;
            
            return !isVerticalWall( x - 1, y );
        case Direction::RIGHT:
            if( pt.c == width() - 1 )
              return false;
            
            return !isVerticalWall( x, y );
        case Direction::DOWN:
            if( pt.r == height() - 1 )
              return false;
            
            return !isHorizontalWall( x, y );
        case Direction::UP:
            if( pt.r == 0 )
              return false;
            
            return !isHorizontalWall( x, y - 1 );
        default:
            return true;
    }
}

void MazeWithWalls::print( std::ostream& ostr ) const 
{

    std::vector< int > digits( width() );
    for( int i = 0; i < width(); ++i )
    {
        int max = *std::max_element( cells[i].begin(), cells[i].end() );
        digits[i] =  digits_count( max );
    }

    for( int  i = 0; i < height(); ++i )
    {
        for( int j = 0; j < width(); ++j )
        {
            ostr << std::setw( digits[j] );
            ostr << cells[j][i];   
            if( j != width() - 1 && ver[j][i] )
                ostr << '|';
            else 
                ostr << ' ';
        }
        ostr << '\n';

        for( int j = 0; j < width(); ++j )
        {
            if( i != height() - 1 && hor[j][i])
                ostr << std::string(digits[j], '-');
            else 
                ostr << std::string(digits[j], ' ');

            ostr << ' ';
        }

        ostr << '\n';
    }
    
}



void MazeWithWalls::printWithPath( std::ostream& ostr, 
                                        const PathType& p ) const
{
    std::vector<std::vector<bool> > is_path(
            width(), 
            std::vector<bool>( height(), false ) );

    for ( const auto& path_item : p )
        is_path[ path_item.c ][ path_item.r ] = true;

    
    for( int i = 0; i < height(); ++i )
    {
        for( int j = 0; j < width(); ++j )
        {
            if( is_path[j][i] )
                ostr << '*';
            else 
                ostr << cells[j][i];

            if( j != width() - 1 && ver[j][i] )
                ostr << '|';
            else 
                ostr << ' ';
        }
        ostr << '\n';

        for( int j = 0; j < width(); ++j )
        {
            if( i != height() - 1 && hor[j][i])
                ostr << '-';
            else 
                ostr << ' ';

            ostr << ' ';
        }

        ostr << '\n';
    }
}

//void MazeWithWalls::displayOnScene(QGraphicsScene* s, const PathType& p ) const
//{
//    std::vector<std::vector<bool> > is_path(
//        width(),
//        std::vector<bool>(height(), false));
//
//    for (const auto& path_item : p)
//        is_path[path_item.c][path_item.r] = true;
//
//    QBrush grayBrush(Qt::lightGray);
//    QBrush pathBrush(Qt::darkYellow);
//    QBrush closedBrush(Qt::black);
//    QPen outlinePen(Qt::black);
//
//    //int space_w = 0, space_h = 0;
//
//
//    for (int i = 0; i < height(); ++i)
//    {
//        for (int j = 0; j < width(); ++j)
//        {
//            QGraphicsItem* cellItem =
//                s->addRect(j * CELL_W + SPACING, i * CELL_H + SPACING,
//                                                    CELL_W, CELL_H, outlinePen, grayBrush);
//            QString str = QString::number(cells[j][i]);
//            QGraphicsItem* textItem =
//                s->addText(str, QFont("Arial", 20));
//            textItem->setParentItem(cellItem);
//
//            if(j != width() - 1 && ver[j][i])
//            {
//                s->addLine(j * CELL_W, i * CELL_H, j * CELL_W + SPACING, i * CELL_H + SPACING);
//            }
//        }
//
//        for (int j = 0; j < width(); ++j)
//        {
//            if (i != height() - 1 && hor[j][i])
//            {
//                s->addLine(j * CELL_W, i * CELL_H, j * CELL_W + SPACING, i * CELL_H + SPACING);
//            }
//        }
//    }
//
//
//    /// Same with MazeWithBoxes
//}