#include "MainWindow.hpp"
#include "MazeWidget.hpp"

#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "RandomizedDFS.hpp"
#include "RecursiveDivision.hpp"
#include "AdjacencyListGraph.hpp"
#include "AdjacencyMatrixGraph.hpp"
#include "Algorithms.hpp"
#include "MazeGraphRepresentation.hpp"
#include "MazeCellPredicateStraightLine.hpp"
#include <memory>
#include <vector>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mazeWidget_ = new MazeWidget(this);

    generatorBox_ = new QComboBox(this);
    generatorBox_->addItem("Randomized DFS");
    generatorBox_->addItem("Recursive Division");

    graphBox_ = new QComboBox(this);
    graphBox_->addItem("Adjacency List");
    graphBox_->addItem("Adjacency Matrix");

    algorithmBox_ = new QComboBox(this);
    algorithmBox_->addItem("DFS");
    algorithmBox_->addItem("BFS");
    algorithmBox_->addItem("Dijkstra");
    algorithmBox_->addItem("A*");

    runButton_ = new QPushButton("Run", this);
    connect(runButton_, &QPushButton::clicked, this, &MainWindow::run);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(mazeWidget_, 1);

    QHBoxLayout *controls = new QHBoxLayout;
    controls->addWidget(generatorBox_);
    controls->addWidget(graphBox_);
    controls->addWidget(algorithmBox_);
    controls->addWidget(runButton_);
    layout->addLayout(controls);

    setCentralWidget(central);
    setWindowTitle("Maze Visualizer");
}

void MainWindow::run()
{
    int width = 20;
    int height = 20;

    MazeWithWalls maze(width, height);
    GenType gen(time(0));

    std::unique_ptr<AbstractMazeGenerator> generator;
    if (generatorBox_->currentIndex() == 0)
        generator = std::make_unique<RandomizedDFS>();
    else
        generator = std::make_unique<RecursiveDivision>();
    generator->generate(maze, gen);

    std::unique_ptr<AbstractGraphStorage> graph;
    if (graphBox_->currentIndex() == 0)
        graph = std::make_unique<AdjacencyListGraph>(width * height);
    else
        graph = std::make_unique<AdjacencyMatrixGraph>(width * height);

    MazeGraphRepresentation mg(&maze, graph.get());

    int start = 0;
    int end = width * height - 1;
    std::vector<int> gPath;
    double cost = 0.0;

    switch (algorithmBox_->currentIndex()) {
    case 0:
        dfs(*graph, start, end, gPath, cost);
        break;
    case 1:
        bfs(*graph, start, end, gPath, cost);
        break;
    case 2:
        dijkstra(*graph, start, end, gPath, cost);
        break;
    case 3: {
        MazeCellPredicateStraightLine h(&mg);
        h.setStart({0,0});
        h.setTarget({height-1,width-1});
        aStar(*graph, h, start, end, gPath, cost);
        break; }
    }

    std::vector<Cell> mazePath = mg.verticesToCells(gPath);
    mazeWidget_->setMaze(maze, mazePath);
}
