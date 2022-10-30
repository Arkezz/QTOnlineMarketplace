#include "customer.h"
#include "ui_customer.h"
#include "registerationwindow.h"
#include "product.h"
#include "emptycart.h"
#include "noavailablequantity.h"

QVector<Product*> products;
QVector<Product*> cart;

Customer::Customer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
}

Customer::~Customer()
{
    delete ui;
}

void Customer::addProduct(Product* a){
    //Checks if the product already exists and if so only increases the quantity
    for (int i = 0; i < products.size(); i++) {
        if(products[i]->getName() == a->getName()){
            products[i]->setQuantity(products[i]->getQuantity() + a->getQuantity());
            return;
        }
    }
    products.append(a);
}

void Customer::setCustomerInformation(QString name, QString email, QString address, QString number)
{
    this->name = name;
    this->email = email;
    this->address = address;
    this->number = number;
}

void Customer::on_searchProductButton_clicked()
{

}

void Customer::on_addToCartButton_clicked()
{
    QMessageBox err;
    QString total = "";
    try {
        //Always take strings in lower case to remove case sensetive situations
        QString addProduct = ui->addProductText->text().toLower();
        //Absolute value so negative numbers dont break it
        int addQuantity = abs(ui->addQuantityText->text().toInt());

        for (int i = 0; i < products.size(); i++) {
            if(addProduct == products[i]->getName()){
                if(products[i]->getQuantity() < addQuantity && addQuantity != 0){
                    throw NoAvailableQuantity();
                } else {
                    for (int i = 0; i < cart.size(); i++) {
                        if(cart[i]->getName() == addProduct){
                            cart[i]->setQuantity(cart[i]->getQuantity() + addQuantity);
                            products[i]->setQuantity(products[i]->getQuantity() - addQuantity);
                            return;
                        }
                    }
                    cart.append(new Product(products[i]));
                    cart[cart.size() - 1]->setQuantity(addQuantity);
                    products[i]->setQuantity(products[i]->getQuantity() - addQuantity);
                    ui->cartListText->addItem(cart[i]->getName());
                }
            }
        }
    } catch (NoAvailableQuantity& e){
        err.setText(e.what());
        err.exec();
    }
}

void Customer::on_confirmBuyingButton_clicked()
{
    QMessageBox msg, err;
    int total = 0;
    QString receipt = "Product:\tPrice:\tQuantity:\n";
    try {
        if(cart.empty()){
            throw EmptyCart();
        } else {
            for (int i = 0; i < cart.size(); i++) {
                receipt += cart[i]->getName() + "\t" + QString::number(cart[i]->getPrice()) + "\t" + QString::number(cart[i]->getQuantity()) + "\n";
                total+= cart[i]->getPrice() * cart[i]->getQuantity();
            }
            msg.setText(receipt + "Total Price: " + QString::number(total));
            msg.exec();
        }
    } catch(EmptyCart& e){
        err.setText(e.what());
        err.exec();
    }
}

void Customer::on_customerBackButton_clicked()
{
    regWindow = new RegisterationWindow();
    regWindow->setWindowTitle("Customer Registeration");
    regWindow->show();
    this->close();
}

