#include <bits/stdc++.h>

using namespace std;

class AutomatFinit {
public:
    set<string> stari;
    set<char> alfabet;
    string stare_initiala;
    set<string> stari_finale;
    map<pair<string, char>, set<string>> functie_tranzitie;

    void verifica_determinism();

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

    string getTranzitie(const string& stare, char simbol) const;
    bool esteStareFinala(const string& stare) const;
    string getStareInitiala() const;
};
