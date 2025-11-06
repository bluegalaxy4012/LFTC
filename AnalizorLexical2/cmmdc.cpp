#include <iostream>
using namespace std;

int main() {
    int a, b, temp;
    cout << "Introdu a, b: ";
    cin >> a >> b;

    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    cout << "cmmdc: ";
    cout << a;

    return 0;
}
