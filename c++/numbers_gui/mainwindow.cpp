/* Game named 2048
 *
 * Desc:
 * This program is made for game called 2048 with board size 4 x 4.
 * Idea of the game is to get 2048 to one square.
 * Game is played by moving gameboard numbers to combine them.
 * To squares with same value are combined together when user moves
 * gameboard numbers. Two twos will become four and two fours
 * will become eight etc. Game is lost if the gameboard is full of
 * numbers, no combinations are possible and none of the squares
 * has the value of 2048.
 *
 * To play the game user has to set up seed value.
 * User can also change maximum points, default is 2048.
 * User has to click "start" button to start the game. Program
 * fills numbers to the gameboard radomly.
 * Game is played with using arrow buttons: up, left, down, right.
 * Timer starts when user has clicked start button.
 *
 * User can reset the game any time. In this case user has to give new
 * seed number and press start to start the game. The timer will start
 * from zero.
 * Program will tell by printing text and changing the main window
 * backgroud color about win or lose situations.
 *
 * Program author
 * Name: Sanna Nykänen
 * Student number: 150384977
 * UserID: tvsany
 * E-Mail: sanna.nykanen@tuni.fi
 *
 * */
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <QGraphicsScene>
#include <QGraphicsRectItem>

const Coords DEFAULT_DIR = {0, 0};
const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};
Coords dir = DEFAULT_DIR;
QString strEmpty = " ";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    board = new GameBoard();
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
    scene_ = new QGraphicsScene(this);
    this->setStyleSheet("background-color: #D3D3D3");

    ui->maxPointsSpinBox->setMaximum(3000);
    ui->maxPointsSpinBox->setStyleSheet("background-color: white");
    ui->seedSpinBox->setStyleSheet("background-color: white");
    ui->maxPointsSpinBox->setValue(2048);

    ui->resetButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->textBrowser->setStyleSheet("background-color: white");

    ui->upButton->setIconSize(QSize(28, 28));
    ui->upButton->setIcon(QIcon(":/arrows/arrow_up.png"));
    ui->downButton->setIconSize(QSize(28, 28));
    ui->downButton->setIcon(QIcon(":/arrows/arrow_down.png"));
    ui->leftButton->setIconSize(QSize(28, 28));
    ui->leftButton->setIcon(QIcon(":/arrows/arrow_left.png"));
    ui->rightButton->setIconSize(QSize(28, 28));
    ui->rightButton->setIcon(QIcon(":/arrows/arrow_right.png"));

    ui->lcdNumberMin->setStyleSheet("background-color: white");
    ui->lcdNumberSec->setStyleSheet("background-color: white");

    disable_arrow_buttons();

    generate_grid();

    board->init_empty();
}

MainWindow::~MainWindow()
{
    delete board;
    delete ui;
}

void MainWindow::on_seedSpinBox_valueChanged(int arg1)
{
    seedValue_ = arg1;
    start_game();
}

void MainWindow::on_maxPointsSpinBox_valueChanged(int arg1)
{
    maxPoints_ = arg1;
    start_game();
}

// Generates empty game grid when game starts
// Empty grid is made with QLabels and
void MainWindow::generate_grid()
{
    for (int i = 0; i<SIZE; i++){
        labelPoint.push_back({});
        for (int j = 0; j<SIZE; j++){
            QLabel* label = new QLabel(this);
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("border: 1px; background: white;");

            label->setText(strEmpty);
            ui->boardLayout->addWidget(label, i, j);
            labelPoint.at(i).push_back(label);
        }
    }
}

// Fills the gameboard with values
void MainWindow::print_gameboard()
{
    int labelValue;
    for (unsigned int i = 0; i<labelPoint.size(); i++){
        for (unsigned int j = 0; j<labelPoint.size(); j++) {
            std::pair<int, int> coordinates = {i , j};
            labelValue = board->get_item(coordinates)->get_value();
            labelPoint.at(i).at(j)->setNum(labelValue);
        }
    }
}

// Moves the numbers to wanted direction
// Check that has game been won or the gameboard full of numbers
// Writes message to textBrowser if game is lost of won,
// changes main window color and stops timer.
void MainWindow::play_game()
{
    if( dir != DEFAULT_DIR )
    {
        if( board->move(dir, ui->maxPointsSpinBox->value()) )
        {
            QString maxPointsStr = QString::number(ui->maxPointsSpinBox->value());
            QString winStr = "You reached the goal value of ";
            winStr.append(maxPointsStr);
            winStr.append("!");
            ui->textBrowser->setText(winStr);
            disable_arrow_buttons();
            this->setStyleSheet("background-color: #11df59");
            timer->stop();

        }
        else if( board->is_full() )
        {
            QString loseStr = "Can't add new tile, you lost!";
            ui->textBrowser->setText(loseStr);
            disable_arrow_buttons();
            this->setStyleSheet("background-color: #FA0781");
            timer->stop();
        }
        board->new_value(false);
        print_gameboard();
    }
}

// Function for disabeling the arrow buttons
void MainWindow::disable_arrow_buttons()
{
    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
}

// Function checks that seed or maximum points
// spinbox values are other than zero and enables
// start button
void MainWindow::start_game()
{
    if (ui->seedSpinBox->value() != 0
            and ui->maxPointsSpinBox->value() !=0){
        ui->startButton->setEnabled(true);
    }
}

// Function that calls function to create game values
// fills the board with them and enables buttons to
// play the game. Disables buttons that are not needed
// during playing.
void MainWindow::on_startButton_clicked()
{
    board->fill(seedValue_);
    print_gameboard();
    timer->start(1000);
    ui->upButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->seedSpinBox->setEnabled(false);
    ui->maxPointsSpinBox->setEnabled(false);
}

// Function sets background color for gray because
// it there is win or lose situatin.
// Timer is stopped, gameboard is filled empty,
// vector is se up with nullpointers and
// seed spinbox and maximum points box are enabled.
void MainWindow::on_resetButton_clicked()
{
    this->setStyleSheet("background-color: #D3D3D3");
    disable_arrow_buttons();
    ui->seedSpinBox->setEnabled(true);
    ui->maxPointsSpinBox->setEnabled(true);
    ui->seedSpinBox->setValue(0);
    ui->maxPointsSpinBox->setValue(2048);
    timer->stop();
    seconds_ = 0;
    minutes_ = 0;

    board->emptyVector();

    for (unsigned int i = 0; i<labelPoint.size(); i++){
        for (unsigned int j = 0; j<labelPoint.size(); j++) {
            labelPoint.at(i).at(j)->setText(strEmpty);
        }
    }
}

// Function to display time in lcdNumber widgets
void MainWindow::showTime()
{
    ui->lcdNumberSec->display(seconds_);
    ui->lcdNumberMin->display(minutes_);
    seconds_++;
    if (seconds_ == 59){
        seconds_ = 0;
        minutes_++;
    }

}

void MainWindow::on_upButton_clicked()
{

    dir = UP;
    play_game();
}


void MainWindow::on_rightButton_clicked()
{
    dir = RIGHT;
    play_game();
}


void MainWindow::on_downButton_clicked()
{
    dir = DOWN;
    play_game();
}

void MainWindow::on_leftButton_clicked()
{
    dir = LEFT;
    play_game();
}

