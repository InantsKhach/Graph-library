#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "AbstractGraphStorage.hpp"
#include "AdjacencyListGraph.hpp"
#include "AdjacencyMatrixGraph.hpp"
#include "AbstractMaze.hpp"
#include "MazeWithBoxes.hpp"
#include "Algorithms.hpp"
#include "MazeGraphRepresentation.hpp"
#include "MazeCellSimplePredicate.hpp"
#include "MazeWithWalls.hpp"
#include "RandomizedDFS.hpp"
#include "RecursiveDivision.hpp"
#include "MazeCellPredicateStraightLine.hpp"

/*
std::vector< Cell > dfs_algorithm(
        AbstractGraphStorage* g, MazeGraphRepresentation mg, 
        AbstractMaze* m, int start, int end )
{
    std::vector<int> path;
    double cost = 0;

    dfs(*g, start, end, path, cost);
    std::cout << "\nThe dfs algorithm\n" << "Cost value is " << cost << '\n';
    for(auto elem : path)
            std::cout << elem << ' ';

    std::cout << '\n';

    std::vector< Cell > road;

    for(const auto elem : path)
    {
        road.push_back( mg.vertexToCell( elem ) );
    }

    return road;
}

std::vector< Cell > bfs_algorithm(
        AbstractGraphStorage* g, MazeGraphRepresentation mg, 
        AbstractMaze* m, int start, int end )
{
    std::vector<int> path;
    double cost = 0;

    bfs(*g, start, end, path, cost);
    std::cout << "\nThe bfs algorithm\n" <<"Cost value is " << cost << '\n';
    for(auto elem : path)
       std::cout << elem << ' ';

    std::cout << '\n';

    std::vector< Cell > road;

    for(const auto elem : path)
    {
        road.push_back( mg.vertexToCell( elem ) );
    }

    return road;
}

std::vector< Cell > dijkstra_algorithm(
        AbstractGraphStorage* g, MazeGraphRepresentation mg, 
        AbstractMaze* m, int start, int end )
{
    std::vector<int> path;
    double cost = 0;

    dijkstra(*g, start, end, path, cost);
    std::cout << "\nThe bfs algorithm\n" << "Cost value is " << cost << '\n';
    for (auto elem : path)
        std::cout << elem << ' ';

    std::cout << '\n';

    std::vector< Cell > road;

    for (const auto elem : path)
    {
        road.push_back(mg.vertexToCell(elem));
    }

    return road;
}

std::vector< Cell > astar_algorithm( 
        AbstractGraphStorage* g, MazeGraphRepresentation mg, AbstractMaze* m, 
        AbstractVertexPredicate* h, int start, int end )
{
    std::vector< int > path;
    double cost = 0;
    aStar(*g, *h, start, end, path, cost);
    std::cout << "\nThe aStar algorithm\n" << "Cost value is " << cost << '\n';
    for (auto elem : path)
        std::cout << elem << ' ';

    std::cout << '\n';

    std::vector< Cell > road;
    for (const auto& elem : path)
        road.push_back(mg.vertexToCell(elem));

    return road;

    //m->printWithPath(std::cout, road);
}*/

void generate_maze_with_boxes(MazeWithBoxes& m, GenType& gen, 
        AbstractMazeGenerator* eng)
{
    std::cout << m.width() << ' ' << m.height() << "\n\n";
   // m.print( std::cout );
    std::cout << "\n\n";
    eng->generate(m, gen);
    //m.print(std::cout);
}

void generate_maze_with_walls(MazeWithWalls& m, GenType& gen, 
        AbstractMazeGenerator* eng)
{
    std::cout << m.width() << ' ' << m.height() << "\n\n";
    //m.print(std::cout);
    std::cout << "\n\n";
    eng->generate(m, gen);
    //m.print(std::cout);
}




int main( int argc, char* argv[] )
{
    QApplication app(argc, argv);

    /*
    MazeWithBoxes m(5, 7);
    std::cout << m.width() << ' ' << m.height() << '\n';
    m.print(std::cout);

    m.setWall(Cell(0, 2));
    m.setWall(Cell(2, 0));
    m.setWall(Cell(3, 1));
    m.setWall(Cell(3, 3));
    m.setWall(Cell(4, 5));
    m.setWall(Cell(2, 5));
    m.setWall(Cell(4, 2));
    m.setWall(Cell(0, 6));


    m.setBlank(Cell(1, 3), 8);
    m.setBlank(Cell(2, 4), 6);
    m.setBlank(Cell(1, 2), 4);
    m.setBlank(Cell(3, 4), 333);
    

    std::cout << std::endl;

    m.print(std::cout);

    AbstractGraphStorage* g = new AdjacencyMatrixGraph( 0 );

    MazeGraphRepresentation mg( &m, g );

    //AbstractVertexPredicate* h = new MazeCellSimplePredicate( &mg );

    AbstractVertexPredicate* h = new MazeCellPredicateStraightLine( &mg );

    */
    
    GenType gen(time(0));
    AbstractMaze* m;
    AbstractMazeGenerator* eng;
    AbstractGraphStorage* g;
    
    std::vector< Cell > mazePath;
    std::vector< int > graphPath;
    int w, h;
    double cost = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == "-maze")
        {
            w = atoi(argv[i + 1]);
            h = atoi(argv[i + 2]);
            if (argv[i + 3] == "walls")
                m = new MazeWithWalls(w, h);
            else if (argv[i + 3] == "boxes")
                m = new MazeWithBoxes(w, h);
            else
                throw "Unknown type";
            i += 3;
        }
        else if (argv[i] == "-gen")
        {
            if (argv[i + 1] == "dfs")
                eng = new RandomizedDFS();
            else if (argv[i + 1] == "rec_div")
                eng = new RecursiveDivision();
            else
                throw "Unknown type";
            ++i;
        }
        else if (argv[i] == "-graph")
        {
            if (argv[i + 1] == "list")
                g = new AdjacencyListGraph(0);
            else if (argv[i + 1] == "matrix")
                g = new AdjacencyMatrixGraph(0);
            else
                throw "Unknown type";
            ++i;
        }
        else if(argv[i] == "-run")
        {
            MazeGraphRepresentation mg(m, g);
            AbstractVertexPredicate* heuristic = new MazeCellPredicateStraightLine(&mg);
            if (argv[i + 1] == "dfs"
            {
                dfs(*g, 0, w * h - 1, graphPath, cost);
            }
            else if (argv[i + 1] == "bfs")
                path = bfs_algorithm(g, mg, m, 0, w * h - 1);
            else if (argv[i + 1] == "dijkstra")
                path = dijkstra_algorithm(g, mg, m, 0, h * w - 1);
            else if (argv[i + 1] == "astar")
                path = astar_algorithm(g, mg, m, heuristic, 0, w * h - 1);
            else
                throw "Unknown type";
            ++i;
            mazePath = mg.verticesToCells( graphPath );
        }
        else if (argv[i] == "-display")
        {
            if (argv[i + 1] == "console")
                m->printWithPath(std::cout, mazePath);
            else if (argv[i + 1] == "gui") {
                QGraphicsScene scene;
                QGraphicsView view( &scene );
                view.resize( 800, 600 );

                m->displayOnScene( &scene );
                view.fitInView( 
                        QRectF( 0, 0, m->width() * CELL_W, m->height() * CELL_H ) );

                view.show();
            }
                ;

        }
    }

    // MazeWithWalls m( 4, 4 );
    // m.print( std::cout );

    // m.setVerticalWall( 0, 0 );
    // m.setVerticalWall( 1, 2 );

    // m.setHorizontalWall( 2, 0 );
    // m.setHorizontalWall( 1, 0 );
    // m.setHorizontalWall( 1, 1 );
    // m.setHorizontalWall( 2, 1 );
    // m.setHorizontalWall( 0, 1 );
    // m.setHorizontalWall( 1, 2 );
    // m.setHorizontalWall( 3, 2 );

    // m.setval( Cell(2, 2), 134 );
    // m.setval( Cell(1, 1), 12 );

    

    // std::cout << "\n";

    // m.print( std::cout );

    // AbstractGraphStorage* g = new AdjacencyListGraph( 0 );
    // MazeGraphRepresentation mg( &m, g );
    // AbstractVertexPredicate* h = new MazeCellSimplePredicate( &mg );





    // MazeWithBoxes m(16, 16);
    // std::cout << m.width() << ' ' << m.height() << "\n\n";
    // //m.print(std::cout);

    // RandomizedDFS gen;
    // gen.generate( m );
    // m.print( std::cout );

    // MazeWithWalls m( 6, 8 );
    // std::cout << m.width() << ' ' << m.height() << "\n\n";
    // //m.print( std::cout );



    // RandomizedDFS gen;
    // gen.generate( m );
    // //std::cout << "\n\n";
    // m.print( std::cout );




    // MazeWithBoxes m( 16, 16 );
    // std::cout << m.width() << ' ' << m.height() << "\n\n";
    // m.print( std::cout );
    // std::cout << "\n\n";
    // // RandomizedDFS eng;
    // RecursiveDivision eng;
    // GenType gen( time( 0 ) );
    // eng.generate( m, gen );
    // m.print( std::cout );

    // MazeWithWalls m( 10, 8 );
    // std::cout << m.width() << ' ' << m.height() << "\n\n";
    // m.print( std::cout );
    // std::cout << "\n\n";
    // RecursiveDivision eng;
    // // RandomizedDFS eng;
    // GenType gen( time( 0 ) );
    // eng.generate( m, gen );
    // m.print( std::cout );

 
     return app.exec();
}