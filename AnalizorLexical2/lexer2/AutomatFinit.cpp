#include "AutomatFinit.h"

AutomatFinit::AutomatFinit() {}

void AutomatFinit::citesteTastatura() {
    string linie;
    string stare;
    char simbol;

    cout << "Introduceti starile (string-uri separate de spatiu): ";
    getline(cin, linie);
    stringstream ss_stari(linie);
    while (ss_stari >> stare) {
        stari.insert(stare);
    }

    cout << "Introduceti alfabetul (caractere separate de spatiu): ";
    getline(cin, linie);
    stringstream ss_alfabet(linie);
    while (ss_alfabet >> simbol) {
        alfabet.insert(simbol);
    }

    cout << "Introduceti starea initiala: ";
    getline(cin, linie);
    stare_initiala = linie;

    cout << "Introduceti starile finale (string-uri separate de spatiu): ";
    getline(cin, linie);
    stringstream ss_finale(linie);
    while (ss_finale >> stare) {
        stari_finale.insert(stare);
    }

    cout << "Introduceti tranzitiile (format: stare_start simbol stare_rezultat). Scrie 'gata' pentru a termina." << '\n';
    string stare_start, stare_dest;
    while (true) {
        cout << "Tranzitie: ";
        getline(cin, linie);
        if (linie == "gata") {
            break;
        }
        stringstream ss_tranzitie(linie);
        if (ss_tranzitie >> stare_start >> simbol >> stare_dest) {
            functie_tranzitie[{stare_start, simbol}].insert(stare_dest);
        }
    }
    
    verifica_determinism();
}

void AutomatFinit::citesteFisier(const string& filename) {
    ifstream fin(filename);
    string linie;

    getline(fin, linie);
    stringstream ss_stari(linie);
    string stare;

    while (ss_stari >> stare) {
        stari.insert(stare);
    }

    getline(fin, linie);
    stringstream ss_alfabet(linie);
    char simbol;
    while (ss_alfabet >> simbol) {
        alfabet.insert(simbol);
    }

    getline(fin, linie);
    stare_initiala = linie;

    getline(fin, linie);
    stringstream ss_finale(linie);
    while (ss_finale >> stare) {
        stari_finale.insert(stare);
    }

    string stare_start, stare_dest;
    while (fin >> stare_start >> simbol >> stare_dest) {
        functie_tranzitie[{stare_start, simbol}].insert(stare_dest);
    }
    fin.close();

    verifica_determinism();
}

void AutomatFinit::verifica_determinism() {
    esteDeterminist = true;

    for (auto const& [cheie, rezultate] : functie_tranzitie) {
        if (rezultate.size() > 1) {
            esteDeterminist = false;
            return;
        }
    }
}

void AutomatFinit::afiseazaStari() {
    cout << "\nMultimea starilor Q este:\n";
    for (const auto& stare: stari) cout << stare << ' ';
    cout << '\n';
}

void AutomatFinit::afiseazaAlfabet() {
    cout << "\nAlfabetul Sigma este format din:\n";
    for (const auto& simbol: alfabet) cout << simbol << ' ';
    cout << '\n';
}

void AutomatFinit::afiseazaTranzitii() {
    cout << "\nMultimea tranzitiilor delta este:\n";
    for (const auto& [stare_simbol, rezultate] : functie_tranzitie) {
        cout << "delta(" << stare_simbol.first << ", " << stare_simbol.second << ") = { ";
        for (const auto& rezultat : rezultate) cout << rezultat << " ";
        cout << "}\n";
    }
}

void AutomatFinit::afiseazaStariFinale() {
    cout << "\nMultimea starilor finale F este:\n";
    for (const auto& stare: stari_finale) cout << stare << ' ';
    cout << '\n';
}

bool AutomatFinit::verificaSecventa(const string& secventa) {
    if (!esteDeterminist) return false;

    string stare_curenta = stare_initiala;

    for (char simbol: secventa) {
        if (functie_tranzitie.count({stare_curenta, simbol}))
            stare_curenta = *functie_tranzitie.at({stare_curenta, simbol}).begin();
        else return false;
    }

    return stari_finale.count(stare_curenta);
}

string AutomatFinit::celMaiLungPrefixSecventa(const string& secventa) {
    if (!esteDeterminist) return "";

    string stare_curenta = stare_initiala;
    string prefix_curent = "";
    string prefix_acceptat = "";

    if (stari_finale.count(stare_curenta))
        prefix_acceptat = "";

    for (char simbol: secventa) {
        if (functie_tranzitie.count({stare_curenta, simbol})) {
            stare_curenta = *functie_tranzitie.at({stare_curenta, simbol}).begin();
            prefix_curent += simbol;

            if (stari_finale.count(stare_curenta))
                prefix_acceptat = prefix_curent;
        }
        else break;
    }

    return prefix_acceptat;
}

string AutomatFinit::getTranzitie(const string& stare, char simbol) const {
    auto key = make_pair(stare, simbol);
    if (functie_tranzitie.count(key) && !functie_tranzitie.at(key).empty()) {
        return *functie_tranzitie.at(key).begin();
    }
    return "";
}

bool AutomatFinit::esteStareFinala(const string& stare) const {
    return stari_finale.count(stare);
}

string AutomatFinit::getStareInitiala() const {
    return stare_initiala;
}