#ifndef RANDOMIZED_DFS_HPP
#define RANDOMIZED_DFS_HPP

#include "AbstractMazeGenerator.hpp"
#include <utility>


class RandomizedDFS : public AbstractMazeGenerator
{

public:
    virtual void generate( MazeWithBoxes& mz, GenType& gen );

    virtual void generate( MazeWithWalls& mz, GenType& gen );

private:

    std::vector< Cell > get_neighbours( Cell& p, MazeWithWalls& mz );

    std::vector< Cell > get_neighbours( Cell& p, MazeWithBoxes& mz );
};

#endif