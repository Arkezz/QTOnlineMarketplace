#ifndef NOAVAILABLEQUANTITY_H
#define NOAVAILABLEQUANTITY_H
#include <stdexcept>
using namespace std;

class NoAvailableQuantity : public logic_error
{
public:
    NoAvailableQuantity() : logic_error("The amount you entered is greater than the available quantity") {}
};

#endif // NOAVAILABLEQUANTITY_H
