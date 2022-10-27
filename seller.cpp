#include "seller.h"
#include "ui_seller.h"
#include "registerationwindow.h"
#include "customer.h"
#include "product.h"

Seller::Seller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Seller)
{
    ui->setupUi(this);
}

void Seller::setSellerInformation(QString name, QString email, QString address, QString number)
{
    this->name = name;
    this->email = email;
    this->address = address;
    this->number = number;
}

Seller::~Seller()
{
    delete ui;
}

void Seller::on_sellerBackButton_clicked()
{
    regWindow = new RegisterationWindow();
    regWindow->setWindowTitle("Seller Registeration");
    regWindow->show();
    this->close();
}


void Seller::on_addProductButton_clicked()
{
    if(ui->productNameText->text() == ""){
        QMessageBox msg;
        msg.setText("Product needs to atleast have a name");
        msg.exec();
    } else {
        Product* temp = new Product(ui->productNameText->text().toLower(),ui->priceText->text().toInt(), ui->categoryText->text().toLower(), ui->quantityText->text().toInt());
        Customer* customer = new Customer;
        customer->addProduct(temp);
    }
}

