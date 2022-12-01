#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include <QLabel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_seedSpinBox_valueChanged(int arg1);
    void on_maxPointsSpinBox_valueChanged(int arg1);
    void generate_grid();
    void on_resetButton_clicked();
    void on_startButton_clicked();

    void on_upButton_clicked();
    void on_rightButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();

    void print_gameboard();
    void play_game();
    void disable_arrow_buttons();
    void start_game();

private:
    Ui::MainWindow *ui;
    int seedValue_ = 0;
    int maxPoints_ = 0;
    QGraphicsScene* scene_;

    QGraphicsRectItem *rec;
    GameBoard* board;
    QTimer* timer;

    std::vector<std::vector<QLabel*>> labelPoint;

    void showTime();
    int minutes_ = 0;
    int seconds_ = 0;


};
#endif // MAINWINDOW_HH
