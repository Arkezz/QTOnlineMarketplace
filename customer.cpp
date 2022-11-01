#include "customer.h"
#include "ui_customer.h"
#include "registerationwindow.h"
#include "product.h"
#include "emptycart.h"
#include "noavailablequantity.h"

QMap<QString, Product*> products;
QMap<QString, Product*> cart;

Customer::Customer(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Customer)
{
	ui->setupUi(this);
}

Customer::~Customer()
{
	delete ui;
}

void Customer::addProduct(Product* a) {
	//Checks if the product already exists and if so only increases the quantity
	if (products.contains(a->getName())) {
		products[a->getName()]->setQuantity(products[a->getName()]->getQuantity() + a->getQuantity());
	}
	else {
		products[a->getName()] = a;
	}
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
	QString nameSearch = ui->searchNameText->text().toLower();
	QString categorySearch = ui->searchCategoryText->text().toLower();
	QListWidget* list = ui->productListText;
	list->clear();

	//Search for the product by name, category, or both
	if (nameSearch != "" && categorySearch != "") {
		for (auto i = products.begin(); i != products.end(); i++) {
			if (i.value()->getName().toLower().contains(nameSearch) && i.value()->getCategory().toLower().contains(categorySearch)) {
				//Check if the product is already in the list
				if (!list->findItems(i.value()->getName(), Qt::MatchExactly).size()) {
					list->addItem(i.value()->getName());
				}
			}
		}
	}
	else if (nameSearch != "") {
		for (auto i = products.begin(); i != products.end(); i++) {
			if (i.value()->getName().toLower().contains(nameSearch)) {
				if (!list->findItems(i.value()->getName(), Qt::MatchExactly).size()) {
					list->addItem(i.value()->getName());
				}
			}
		}
	}
	else if (categorySearch != "") {
		for (auto i = products.begin(); i != products.end(); i++) {
			if (i.value()->getCategory().toLower().contains(categorySearch)) {
				if (!list->findItems(i.value()->getName(), Qt::MatchExactly).size()) {
					list->addItem(i.value()->getName());
				}
			}
		}
	} //Else if nothing is found send a qmessage box
	else {
		QMessageBox::information(this, "Error", "No products found");
	}
}

void Customer::on_addToCartButton_clicked()
{
	//Always take strings in lower case to remove case sensetive situations
	QString addProduct = ui->addProductText->text().toLower();
	//Absolute value so negative numbers dont break it
	int addQuantity = abs(ui->addQuantityText->text().toInt());
	//Cart list
	QListWidget* list = ui->cartListText;

	try {
		//Display the product added to the cart on the cart list
		if (products.contains(addProduct)) {
			if (products[addProduct]->getQuantity() >= addQuantity && addQuantity != 0) {
				//If the product is already in the cart, increase the quantity
				if (cart.contains(addProduct)) {
					cart[addProduct]->setQuantity(cart[addProduct]->getQuantity() + addQuantity);
				}
				else {
					//If the product is not in the cart, add it
					cart[addProduct] = products[addProduct];
					cart[addProduct]->setQuantity(addQuantity);
				}
				//Display the product added to the cart on the cart list. Do not add it again if it is already in the list
				if (!list->findItems(cart[addProduct]->getName(), Qt::MatchExactly).size()) {
					list->addItem(cart[addProduct]->getName());
				}
				//Decrease the quantity of the product in the store
				products[addProduct]->setQuantity(products[addProduct]->getQuantity() - addQuantity);
			}
			else {
				throw NoAvailableQuantity();
			}
		}
		else {
			throw NoAvailableQuantity();
		}
	}
	catch (NoAvailableQuantity& e) {
		QMessageBox::information(this, "Error", e.what());
	}
}

void Customer::on_confirmBuyingButton_clicked()
{
	//Show the user a receipt of all his products in the cart and the total price
	QString receipt = "Receipt for " + name + ":\n";
	double totalPrice = 0;
	try {
		if (cart.size() == 0) {
			throw EmptyCart();
		}
		for (auto i = cart.begin(); i != cart.end(); i++) {
			//Show the receipt in a product quantity price form
			receipt += i.value()->getName() + " " + QString::number(i.value()->getQuantity()) + " " + QString::number(i.value()->getPrice()) + "\n";
			totalPrice += i.value()->getPrice() * i.value()->getQuantity();
		}
		receipt += "Total Price: $" + QString::number(totalPrice);
		QMessageBox::information(this, "Receipt", receipt);
	}
	catch (EmptyCart e) {
		QMessageBox::information(this, "Error", e.what());
	}
}

void Customer::on_customerBackButton_clicked()
{
	regWindow = new RegisterationWindow();
	regWindow->setWindowTitle("Customer Registeration");
	regWindow->show();
	this->close();
}