#include <iostream>

int main() {
    int a, b;
    std::cout << "Introdu a, b: ";
    std::cin >> a >> b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    std::cout << "cmmdc: ";
    std::cout << a;

    return 0;
}
