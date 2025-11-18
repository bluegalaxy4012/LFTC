#include <iostream>
using namespace std;

int main() {
    int n;
    int s = 0;
    int citit;

    cout<<"Introdu n si apoi n numere intregi: ";
    cin>>n;

    for (int i = 0; i < n; i++) {
        cin>>citit;
        s = s + citit;
    }

    cout<<"Suma: ";
    cout<<s;

    return 0;
}
