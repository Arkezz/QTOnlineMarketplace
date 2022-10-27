#ifndef REGISTERATIONWINDOW_H
#define REGISTERATIONWINDOW_H

#include <QWidget>

namespace Ui {
class RegisterationWindow;
}

class Customer;
class Seller;
class MainWindow;

class RegisterationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterationWindow(QWidget *parent = nullptr);
    bool customer;
    ~RegisterationWindow();

private slots:
    void on_registerButton_clicked();

    void on_registerationBackButton_clicked();

private:
    Ui::RegisterationWindow *ui;
    Customer* cusWindow;
    Seller* selWindow;
    MainWindow* mainWindow;
    QString name;
    QString email;
    QString address;
    QString number;
};

#endif // REGISTERATIONWINDOW_H
