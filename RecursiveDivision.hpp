#ifndef RECURSIVE_DIVISION_HPP
#define RECURSIVE_DIVISION_HPP


#include "AbstractMazeGenerator.hpp"
#include <utility>

class RecursiveDivision : public AbstractMazeGenerator 
{
public:
    virtual void generate( MazeWithBoxes& mz, GenType& gen );

    virtual void generate( MazeWithWalls& mz, GenType& gen );

private:
    void handle( MazeWithBoxes& mz, int start_height, int start_width, int end_height, int end_width,
                                                        std::vector< std::vector< bool > >& used, GenType& gen );
    void handle( MazeWithWalls& mz, int start_height, int start_width, int end_height, int end_width, GenType& gen );
};

#endif