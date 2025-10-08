#include <iostream>

int main() {
    int n;
    std::cout<<"Introdu n si apoi n numere intregi: ";
    std::cin>>n;

    int s = 0;
    int citit;

    for (int i = 0; i < n; i++) {
        std::cin>>citit;
        s = s + citit;
    }

    std::cout<<"Suma: ";
    std::cout<<s;

    return 0;
}
