#include <iostream>
using namespace std;

int main() {
    int n;
    int s;

    s = 0;

    cout << "Introdu n: ";
    cin >> n;

    do {
        s = s + 1;
        n = n - 1;
    } while (n > 0);

    cout << "s = " << s;

    return 0;
}
