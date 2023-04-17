#include "gradecounter.hh"
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>

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
    void on_spinBoxN_valueChanged(int arg1);

    void on_spinBoxG_valueChanged(int arg1);

    void on_spinBoxP_valueChanged(int arg1);

    void on_spinBoxE_valueChanged(int arg1);

    void on_countPushButton_clicked();

private:
    Ui::MainWindow *ui;
    void printText();
    int valueN_ = 0;
    int valueG_ = 0;
    int valueP_ = 0;
    int valueE_ = 0;
    int finalGrade = 0;
};
#endif // MAINWINDOW_HH
