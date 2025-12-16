#include <iostream>
using namespace std;

int main() {
    int n;
    int s;
    int citit;

    s = 0;

    cout<<"Introdu n si apoi n numere intregi: ";
    cin>>n;

    while (n > 0) {
        cin >> citit;
        s = s + citit;
        n = n - 1;
    }

    cout<<"Suma: ";
    cout<<s;

    return 0;
}
