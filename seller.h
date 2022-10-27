#ifndef SELLER_H
#define SELLER_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Seller;
}

class RegisterationWindow;

class Seller : public QWidget
{
    Q_OBJECT

public:
    explicit Seller(QWidget *parent = nullptr);
    void setSellerInformation(QString name, QString email, QString address, QString number);
    ~Seller();

private slots:
    void on_sellerBackButton_clicked();

    void on_addProductButton_clicked();

private:
    Ui::Seller *ui;
    RegisterationWindow* regWindow;
    QString name;
    QString email;
    QString address;
    QString number;
};


#endif // SELLER_H
