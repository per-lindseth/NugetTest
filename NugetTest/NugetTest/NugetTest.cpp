#include <iostream>

#include "MyDll.h"

int main() {
    std::cout << MyDll::getWrappedMessage() << std::endl;
    return 0;
}
