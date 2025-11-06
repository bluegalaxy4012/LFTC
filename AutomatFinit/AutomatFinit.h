#include <bits/stdc++.h>

using namespace std;

class AutomatFinit {
private:
    set<string> stari;
    set<char> alfabet;
    string stare_initiala;
    set<string> stari_finale;
    map<pair<string, char>, set<string>> functie_tranzitie;

    void verifica_determinism();

public:
    AutomatFinit();

    bool esteDeterminist;

    void citesteTastatura();
    void citesteFisier(const string& filename);

    void afiseazaStari();
    void afiseazaAlfabet();
    void afiseazaTranzitii();
    void afiseazaStariFinale();

    bool verificaSecventa(const string& secventa);
    string celMaiLungPrefixSecventa(const string& secventa);
};
