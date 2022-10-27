#ifndef PRODUCT_H
#define PRODUCT_H
#include <QObject>

class Product : public QObject
{
public:
    Product();
    Product(QString name, int price, QString category, int quantity);
    Product(const Product* p);
    QString getName() const;
    QString getCategory() const;
    int getPrice() const;
    int getQuantity() const;
    void setQuantity(int quantity);
private:
    QString name;
    int price;
    QString category;
    int quantity;

};

#endif // PRODUCT_H
