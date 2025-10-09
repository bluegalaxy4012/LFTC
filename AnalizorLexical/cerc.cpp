#include <iostream>

int main() {
    float r;
    float perimetru, arie;

    std::cout << "Raza: ";
    std::cin >> r;

    perimetru = 2 * 3.1415 * r;
    arie = 3.1415 * r * r;

    std::cout << "Perimetru: ";
    std::cout << perimetru;
    std::cout << "\nArie: ";
    std::cout << arie;

    return 0;
}
