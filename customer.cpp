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
    QString total = "";
    QString nameSearch = ui->searchNameText->text().toLower();
    QString categorySearch = ui->searchCategoryText->text().toLower();
    int min = 100;
    int index = 0;
    bool category = false;
    bool autoCorrect = false;

    for (int i = 0; i < products.size(); i++) {
        if (products[i]->getName() == nameSearch) {
            ui->productListText->setText(products[i]->getName());
        }
        else if (products[i]->getCategory() == categorySearch && categorySearch != "") {
            total += products[i]->getName() + "\n";
            category = true;
        } else {
            autoCorrect = true;
            for (int i = 0; i < products.size(); i++) {
                int distance = 0;
                int j = 0;
                int k = 0;
                while (j < nameSearch.length() && k < products[i]->getName().length()) {
                    if (nameSearch[j] != products[i]->getName()[k]) {
                        distance++;
                    }
                    j++;
                    k++;
                }
                distance += abs(nameSearch.length() - products[i]->getName().length());
                if (distance < min) {
                    min = distance;
                    index = i;
                }
            }
        }
    }
    if(autoCorrect){
        QMessageBox msg;
        msg.setText("Did you mean: " + products[index]->getName());
        msg.exec();
    }
    if (category) {
        ui->productListText->setText(total);
    }
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
                }
            }
        }
        for (int i = 0; i < cart.size(); i++) {
            total+= cart[i]->getName() + "\n";
        }
        ui->cartListText->setText(total);
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

