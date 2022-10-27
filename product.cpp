#include "product.h"

Product::Product()
{
    name = "";
    price = 0;
    category = "";
    quantity = 0;
}



Product::Product(QString name, int price, QString category, int quantity)
{
    this->name = name;
    this->price = price;
    this->category = category;
    this->quantity = quantity;
}

Product::Product(const Product* p) {
        name = p->name;
        price = p->price;
        category = p->category;
        quantity = p->quantity;
    };

QString Product::getName() const
{
    return name;
}

QString Product::getCategory() const
{
    return category;
}

int Product::getPrice() const
{
    return price;
}

int Product::getQuantity() const
{
    return quantity;
}

void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}
