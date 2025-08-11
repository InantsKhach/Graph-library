#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QComboBox;
class QPushButton;
class MazeWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void run();

private:
    MazeWidget *mazeWidget_;
    QComboBox *generatorBox_;
    QComboBox *graphBox_;
    QComboBox *algorithmBox_;
    QPushButton *runButton_;
};

#endif // MAINWINDOW_HPP
