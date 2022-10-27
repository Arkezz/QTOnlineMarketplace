#include "registerationwindow.h"
#include "ui_registerationwindow.h"
#include "seller.h"
#include "customer.h"
#include "mainwindow.h"

RegisterationWindow::RegisterationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterationWindow)
{
    ui->setupUi(this);
}

RegisterationWindow::~RegisterationWindow()
{
    delete ui;
}


void RegisterationWindow::on_registerButton_clicked()
{
    if(customer){
    name = ui->nameText->text();
    email = ui->emailText->text();
    address = ui->addressText->text();
    number = ui->numberText->text();
    cusWindow = new Customer();
    cusWindow->setCustomerInformation(name, email ,address, number);
    cusWindow->show();
    this->close();
    } else if(!customer){
        name = ui->nameText->text();
        email = ui->emailText->text();
        address = ui->addressText->text();
        number = ui->numberText->text();
        selWindow = new Seller();
        selWindow->setSellerInformation(name, email ,address, number);
        selWindow->show();
        this->close();
    }
}


void RegisterationWindow::on_registerationBackButton_clicked()
{
    mainWindow = new MainWindow();
    mainWindow->setWindowTitle("Kewtie Store");
    mainWindow->show();
    this->close();
}

