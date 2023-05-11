#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "factorial.h"
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
    void on_countFactorial_clicked();

    void on_pauseFactorial_clicked();

    void on_stornoFactorial_clicked();

    void on_progressBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    Factorial *factCounting;

};
#endif // MAINWINDOW_H
