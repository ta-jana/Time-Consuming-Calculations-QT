#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countFactorial_clicked()
{
    long double factNumber = ui->factorialInput->text().toDouble();

    long double factResult = factCounting.computeFactorial(factNumber);

    std::string strNumber = std::to_string(factResult);
    ui->factorialResult->setText(QString::fromStdString(strNumber));
}

