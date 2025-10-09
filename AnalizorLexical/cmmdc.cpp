#include <iostream>

int main() {
    int a, b, temp;
    std::cout << "Introdu a, b: ";
    std::cin >> a >> b;

    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    std::cout << "cmmdc: ";
    std::cout << a;

    return 0;
}
