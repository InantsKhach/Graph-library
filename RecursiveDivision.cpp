#include "RecursiveDivision.hpp"
#include "MazeWithBoxes.hpp"
#include "MazeWithWalls.hpp"
#include <random>
#include <iostream>

void RecursiveDivision::generate( MazeWithBoxes& mz, GenType& gen )
{
    std::vector< std::vector< bool > > used( mz.width(), 
                                                    std::vector< bool >( mz.height(), false ) );
    handle( mz, 0, 0, mz.height() - 1 , mz.width() - 1, used, gen );

    for( int i = 0; i < mz.width(); ++i )
    {
        for( int j = 0; j < mz.height(); ++j )
        {
            if( used[i][j] /* && !mz.canBeOn( Cell( i, j ) ) */ )
            {
                mz.setBlank( Cell( i, j ) );
            }
        }
    }
}

void RecursiveDivision::handle(
        MazeWithBoxes& mz, int start_height, int start_width, int end_height, int end_width,
            std::vector< std::vector< bool > >& used, 
            GenType& gen )
{
    if( end_width - start_width < 2 || end_height - start_height < 2 )
        return;

    std::uniform_int_distribution< int > w_distribution( start_width + 1, end_width - 1 );
    std::uniform_int_distribution< int > h_distribution( start_height + 1, end_height - 1 );

    int vertical_wall = w_distribution( gen );
    int horizontal_wall = h_distribution( gen );
    for( int i = start_height; i <= end_height; ++i )
        if( !used[vertical_wall][i])
            mz.setWall( Cell(vertical_wall, i) );
    
    for(int i = start_width; i <= end_width; ++i )
        if( !used[i][horizontal_wall] )
            mz.setWall( Cell(i, horizontal_wall) );

    std::uniform_int_distribution< int > dist( 4, 7 );
    int box = dist( gen );


    if( box != 0 )
    {
        std::uniform_int_distribution< int > p1_dist( start_width, vertical_wall - 1 );
        int p1 = p1_dist( gen );
        mz.setBlank( Cell( p1, horizontal_wall ) );
        used[p1][horizontal_wall - 1] = true;
        used[p1][horizontal_wall + 1] = true;
    }
    if( box != 1 )
    {
        std::uniform_int_distribution< int > p2_dist( vertical_wall + 1, end_width );
        int p2 = p2_dist( gen );
        mz.setBlank( Cell( p2,  horizontal_wall ) );
        used[p2][horizontal_wall - 1] = true;
        used[p2][horizontal_wall + 1] = true;
    }
    if( box != 2 )
    {
        std::uniform_int_distribution< int > p3_dist( start_height, horizontal_wall - 1 );
        int p3 = p3_dist( gen );
        mz.setBlank( Cell( vertical_wall, p3 ) );
        used[vertical_wall - 1][p3] = true;
        used[vertical_wall + 1][p3] = true;
    }
    if( box != 3 )
    {
        std::uniform_int_distribution< int > p4_dist( horizontal_wall + 1, end_height );
        int p4 = p4_dist( gen );
        mz.setBlank( Cell( vertical_wall, p4 ) );
        used[vertical_wall - 1][p4] = true;
        used[vertical_wall + 1][p4] = true;
    }

    /*
    handle( mz, start_height, start_width, horizontal_wall - 1, vertical_wall - 1, used, gen );
    handle( mz, start_height, vertical_wall + 1, horizontal_wall - 1, end_width, used, gen );
    handle( mz, horizontal_wall + 1, start_height, end_height, vertical_wall - 1, used, gen );
    handle( mz, horizontal_wall + 1, vertical_wall + 1, end_height, end_width, used, gen );
    */
    handle( mz, start_height, start_width, horizontal_wall - 2, vertical_wall - 2, used, gen);
    handle( mz, start_height, vertical_wall + 2, horizontal_wall - 2, end_width, used, gen);
    handle( mz, horizontal_wall + 2, start_height, end_height, vertical_wall - 2, used, gen);
    handle( mz, horizontal_wall + 2, vertical_wall + 2, end_height, end_width, used, gen);
}









void RecursiveDivision::generate( MazeWithWalls& mz, GenType& gen )
{
    handle( mz, 0, 0, mz.height() - 1, mz.width() - 1, gen );
}

void RecursiveDivision::handle( 
                            MazeWithWalls& mz, int start_height, int start_width, int end_height, int end_width, 
                                                                                                GenType& gen )
{
    if( end_width - start_width < 1 || end_height - start_height < 1 )
        return;

    std::uniform_int_distribution< int > w_distribution( start_width, end_width - 1 );
    std::uniform_int_distribution< int > h_distribution( start_height, end_height - 1 );

    int vertical_wall = w_distribution( gen );
    int horizontal_wall = h_distribution( gen );

    for( int i = start_height; i <= end_height; ++i )
        mz.setVerticalWall( vertical_wall, i );
    
    for(int i = start_width; i <= end_width; ++i )
        mz.setHorizontalWall( i, horizontal_wall );

    std::uniform_int_distribution< int > dist( 0, 3 );
    int box = dist( gen );


    if( box != 0 )
    {
        std::uniform_int_distribution< int > p1_dist( start_width, vertical_wall );
        mz.setHorizontalBlank( p1_dist( gen ), horizontal_wall );
    }
    if( box != 1 )
    {
        std::uniform_int_distribution< int > p2_dist( vertical_wall + 1, end_width );
        mz.setHorizontalBlank( p2_dist( gen ), horizontal_wall );
    }
    if( box != 2 )
    {
        std::uniform_int_distribution< int > p3_dist( vertical_wall + 1, end_width );
        mz.setVerticalBlank( vertical_wall, p3_dist( gen ) );
    }
    if( box != 3 )
    {
        std::uniform_int_distribution< int > p4_dist( vertical_wall + 1, end_width );
        mz.setVerticalBlank( vertical_wall, p4_dist( gen ) );
    }


    handle( mz, start_height, start_width, horizontal_wall, vertical_wall, gen );
    handle( mz, start_height, vertical_wall + 1, horizontal_wall, end_width, gen );
    handle( mz, horizontal_wall + 1, start_width, end_height, vertical_wall, gen );
    handle( mz, horizontal_wall + 1, vertical_wall + 1, end_height, end_width, gen );

}