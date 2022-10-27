#ifndef EMPTYCART_H
#define EMPTYCART_H
#include <stdexcept>
using namespace std;

class EmptyCart : public logic_error {
public:
    EmptyCart() : logic_error("The cart is empty") {}
};

#endif // EMPTYCART_H
