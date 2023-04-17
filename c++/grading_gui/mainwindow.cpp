#include "gradecounter.hh"
#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMaximum(MAX_N_POINTS);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    valueN_ = arg1;
            //ui->spinBoxN->value();
}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    valueG_ = arg1;
            //ui->spinBoxG->value();
}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    valueP_ = arg1;
            //ui->spinBoxP->value();
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    valueE_ = arg1;
            //ui->spinBoxE->value();
}


//muuttaa finalGrade muuttujan QStringiksi ja printtaa vastauksen textBrowseriin
void MainWindow::printText()
{
    QString str = "";
    QString grade = "";
    grade = QString::number(finalGrade);
    str.append("Total grade: ");
    str.append(grade);
    ui->textBrowser->setText(str);
}

// Buttonin klikkauksen jälkeen kutsutaan gradecounter luokan metodia,
// lasketaan finaGrade ja kutsutaan print text funktiota
void MainWindow::on_countPushButton_clicked()
{
    finalGrade = count_final_grade(valueN_, valueG_, valueP_, valueE_);
    printText();
}

