#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerationwindow.h"

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


void MainWindow::on_sellerButton_clicked()
{
    regWindow = new RegisterationWindow();
    //Seller when false
    regWindow->customer = false;
    regWindow->setWindowTitle("Seller Registeration");
    regWindow->show();
    this->close();
}


void MainWindow::on_customerButton_clicked()
{
    regWindow = new RegisterationWindow();
    //Customer when true
    regWindow->customer = true;
    regWindow->setWindowTitle("Customer Registeration");
    regWindow->show();
    this->close();
}

