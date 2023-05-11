#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->progressBar_2->setValue(0);

    factCounting = new Factorial(*ui->progressBar);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countFactorial_clicked()
{
    long double factNumber = ui->factorialInput->text().toDouble();

    long double factResult = factCounting->computeFactorial(factNumber);

    std::string strNumber = std::to_string(factResult);
    ui->factorialResult->setText(QString::fromStdString(strNumber));
}


void MainWindow::on_pauseFactorial_clicked()
{
    factCounting->pause = !factCounting->pause;
}


void MainWindow::on_stornoFactorial_clicked()
{
    factCounting->destroy = true;
}


void MainWindow::on_progressBar_valueChanged(int value)
{
   value = factCounting->progressBarFact;
   int clampedValue = std::clamp(value, 0, value*2-1);
   qDebug() << "progressBarFact++;   is: " << clampedValue << "..." ;

   ui->progressBar->setValue(clampedValue);
}

