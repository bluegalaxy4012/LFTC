#include <iostream>

int main() {
    float r;
    std::cout << "Raza: ";
    std::cin >> r;

    float perimetru = 2 * 3.1415 * r;
    float arie = 3.1415 * r * r;

    std::cout << "Perimetru: ";
    std::cout << perimetru;
    std::cout << "\nArie: ";
    std::cout << arie;

    return 0;
}
