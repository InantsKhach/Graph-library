#include "MazeWidget.hpp"

#include <QPainter>
#include <QPaintEvent>

MazeWidget::MazeWidget(QWidget *parent)
    : QWidget(parent), progressIndex_(0)
{
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &MazeWidget::advance);
}

void MazeWidget::setMaze(const MazeWithWalls &maze, const std::vector<Cell> &path)
{
    maze_ = std::make_unique<MazeWithWalls>(maze);
    path_ = path;
    progressIndex_ = 0;
    timer_->start(150);
    update();
}

QSize MazeWidget::sizeHint() const
{
    return QSize(400, 400);
}

void MazeWidget::advance()
{
    if (progressIndex_ < static_cast<int>(path_.size())) {
        ++progressIndex_;
        update();
    } else {
        timer_->stop();
    }
}

void MazeWidget::paintEvent(QPaintEvent *)
{
    if (!maze_)
        return;

    QPainter p(this);
    p.fillRect(rect(), Qt::white);

    int w = maze_->width();
    int h = maze_->height();
    int cellSize = qMin(width() / w, height() / h);

    // draw path progress
    p.setBrush(Qt::yellow);
    for (int i = 0; i < progressIndex_; ++i) {
        const Cell &c = path_[i];
        QRect r(c.c * cellSize, c.r * cellSize, cellSize, cellSize);
        p.fillRect(r, Qt::yellow);
    }

    p.setPen(Qt::black);
    // draw cell borders
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            QRect r(x * cellSize, y * cellSize, cellSize, cellSize);
            p.drawRect(r);
        }
    }

    // draw walls
    p.setPen(QPen(Qt::black, 2));
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            if (x < w - 1 && maze_->isVerticalWall(x, y)) {
                int X = (x + 1) * cellSize;
                p.drawLine(X, y * cellSize, X, (y + 1) * cellSize);
            }
            if (y < h - 1 && maze_->isHorizontalWall(x, y)) {
                int Y = (y + 1) * cellSize;
                p.drawLine(x * cellSize, Y, (x + 1) * cellSize, Y);
            }
        }
    }
}
