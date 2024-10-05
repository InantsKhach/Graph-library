#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <string>
#include <memory>

// #include <QApplication>
// #include <QGraphicsScene>
// #include <QGraphicsView>

#include "../include/AbstractGraphStorage.hpp"
#include "../include/AdjacencyListGraph.hpp"
#include "../include/AdjacencyMatrixGraph.hpp"
#include "../include/AbstractMazeGenerator.hpp"
#include "../include/AbstractMaze.hpp"
#include "../include/MazeWithBoxes.hpp"
#include "../include/Algorithms.hpp"
#include "../include/MazeGraphRepresentation.hpp"
#include "../include/MazeCellSimplePredicate.hpp"
#include "../include/MazeWithWalls.hpp"
#include "../include/RandomizedDFS.hpp"
#include "../include/RecursiveDivision.hpp"
#include "../include/MazeCellPredicateStraightLine.hpp"


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
    std::cout << "\nThe dijkstra algorithm\n" << "Cost value is " << cost << '\n';
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
}

void generate_maze_with_boxes(MazeWithBoxes& m, GenType& gen, 
        AbstractMazeGenerator* eng)
{
    std::cout << m.width() << ' ' << m.height() << "\n\n";
    m.print( std::cout );
    std::cout << "\n\n";
    eng->generate(m, gen);
    m.print(std::cout);
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

struct Config {
    int width = 10;               // Default maze width
    int height = 10;              // Default maze height
    std::string mazeType = "walls"; // Type of maze (e.g., "walls" or "boxes")
    std::string graphType = "list"; // Graph type (e.g., "list" or "matrix")
    std::string genType = "dfs";    // Maze generation algorithm (e.g., "dfs" or "rec_div")
    std::string algorithm = "bfs";  // Algorithm type (e.g., "dfs", "bfs", "dijkstra", or "astar")
    std::string display = "console"; // Output display (e.g., "console")
};


Config parseArguments(int argc, char* argv[]) {
    Config config;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-maze") {
            if (i + 3 >= argc) {
                throw std::runtime_error("Insufficient arguments for -maze");
            }
            config.width = std::stoi(argv[++i]);
            config.height = std::stoi(argv[++i]);
            config.mazeType = argv[++i];
        }
        else if (arg == "-gen") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Insufficient arguments for -gen");
            }
            config.genType = argv[++i];
        }
        else if (arg == "-graph") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Insufficient arguments for -graph");
            }
            config.graphType = argv[++i];
        }
        else if (arg == "-run") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Insufficient arguments for -run");
            }
            config.algorithm = argv[++i];
        }
        else if (arg == "-display") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Insufficient arguments for -display");
            }
            config.display = argv[++i];
        }
        else {
            throw std::runtime_error("Unknown argument: " + arg);
        }
    }

    return config;
}

std::vector<Cell> runAlgorithm(
        const std::string& algorithm,
        AbstractGraphStorage* graph,
        MazeGraphRepresentation& mazeGraph,
        AbstractMaze* maze,
        AbstractVertexPredicate* heuristic,
        int start, int end)
{
    if (algorithm == "dfs") return dfs_algorithm(graph, mazeGraph, maze, start, end);
    if (algorithm == "bfs") return bfs_algorithm(graph, mazeGraph, maze, start, end);
    if (algorithm == "dijkstra") return dijkstra_algorithm(graph, mazeGraph, maze, start, end);
    if (algorithm == "astar") return astar_algorithm(graph, mazeGraph, maze, heuristic, start, end);
    throw std::runtime_error("Unknown algorithm type");
}

AbstractMaze* initializeMaze(int width, int height, const std::string& type) {
    if (type == "walls")
        return new MazeWithWalls(width, height);
    else if (type == "boxes")
        return new MazeWithBoxes(width, height);
    throw std::runtime_error("Unknown maze type");
}

AbstractGraphStorage* initializeGraph(const std::string& type) {
    if (type == "list")
        return new AdjacencyListGraph(0);
    else if (type == "matrix")
        return new AdjacencyMatrixGraph(0);
    throw std::runtime_error("Unknown graph type");
}


int main( int argc, char* argv[] )
{
    //QApplication app(argc, argv);

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

    try {
        Config config = parseArguments(argc, argv);

        auto maze = std::unique_ptr<AbstractMaze>(initializeMaze(config.width, config.height, config.mazeType));
        auto graph = std::unique_ptr<AbstractGraphStorage>(initializeGraph(config.graphType));

        GenType gen(time(0));
        //std::unique_ptr<AbstractMazeGenerator> eng = (config.genType == "dfs") ? std::make_unique<RandomizedDFS>() : std::make_unique<RecursiveDivision>();
        std::unique_ptr<AbstractMazeGenerator> eng;
        if(config.genType == "dfs")
        {
            eng = std::make_unique<RandomizedDFS>();
        }
        else
        {
            eng = std::make_unique<RecursiveDivision>();
        }

        if (config.mazeType == "boxes") {
            auto mazeWithBoxes = dynamic_cast<MazeWithBoxes*>(maze.get());
            if (mazeWithBoxes) {
                eng->generate(*mazeWithBoxes, gen);
            } else {
                std::cerr << "Maze type mismatch!" << std::endl;
            }
        } else if (config.mazeType == "walls") {
            auto mazeWithWalls = dynamic_cast<MazeWithWalls*>(maze.get());
            if (mazeWithWalls) {
                eng->generate(*mazeWithWalls, gen);
            } else {
                std::cerr << "Maze type mismatch!" << std::endl;
            }
        }

        MazeGraphRepresentation mazeGraph(maze.get(), graph.get());
        std::unique_ptr<AbstractVertexPredicate> heuristic = std::make_unique<MazeCellPredicateStraightLine>(&mazeGraph);

        std::vector<Cell> mazePath = runAlgorithm(config.algorithm, graph.get(), mazeGraph, maze.get(), heuristic.get(), 0, config.width * config.height - 1);

        if (config.display == "console") {
            maze->printWithPath(std::cout, mazePath);
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
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

 
    //return app.exec();
}