#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include <QMessageBox>
#include <QMap>

namespace Ui {
	class Customer;
}

class RegisterationWindow;
class Product;

class Customer : public QWidget
{
	Q_OBJECT

public:
	explicit Customer(QWidget* parent = nullptr);
	void setCustomerInformation(QString name, QString email, QString address, QString number);
	~Customer();

	void addProduct(Product*);

private slots:
	void on_searchProductButton_clicked();

	void on_customerBackButton_clicked();

	void on_addToCartButton_clicked();

	void on_confirmBuyingButton_clicked();

private:
	Ui::Customer* ui;
	RegisterationWindow* regWindow;
	QString name;
	QString email;
	QString address;
	QString number;
	QMap<QString, Product*> products;
	QMap<QString, Product*> cart;
};

#endif // CUSTOMER_H
