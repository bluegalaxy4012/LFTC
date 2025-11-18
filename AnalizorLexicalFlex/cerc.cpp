#include <iostream>
using namespace std;

int main() {
    float r;
    float perimetru, arie;

    cout << "Raza: ";
    cin >> r;

    perimetru = 2 * 3.1415 * r;
    arie = 3.1415 * r * r;

    cout << "Perimetru: ";
    cout << perimetru;
    cout << "\nArie: ";
    cout << arie;

    return 0;
}
