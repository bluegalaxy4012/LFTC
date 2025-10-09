#include <iostream>

int main() {
    int n;
    int s = 0;
    int citit;

    std::cout<<"Introdu n si apoi n numere intregi: ";
    std::cin>>n;

    for (int i = 0; i < n; i++) {
        std::cin>>citit;
        s = s + citit;
    }

    std::cout<<"Suma: ";
    std::cout<<s;

    return 0;
}
