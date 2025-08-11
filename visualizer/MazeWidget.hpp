#ifndef MAZEWIDGET_HPP
#define MAZEWIDGET_HPP

#include <QWidget>
#include <QTimer>
#include <memory>
#include <vector>

#include "MazeWithWalls.hpp"
#include "types.hpp"

class MazeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MazeWidget(QWidget *parent = nullptr);
    void setMaze(const MazeWithWalls &maze, const std::vector<Cell> &path);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void advance();

private:
    std::unique_ptr<MazeWithWalls> maze_;
    std::vector<Cell> path_;
    int progressIndex_;
    QTimer *timer_;
};

#endif // MAZEWIDGET_HPP
