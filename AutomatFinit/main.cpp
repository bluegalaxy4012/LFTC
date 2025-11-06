#include "AutomatFinit.h"
#include <iostream>
#include <string>

using namespace std;

void afiseaza_starea_automatului(const AutomatFinit& af) {
    if (af.esteDeterminist) {
        cout << "Automatul este DETERMINIST\n";
    } else {
        cout << "Automatul este NEDETERMINIST\n";
    }
}

void afiseazaMeniu() {
    cout << "\n--- Meniu ---\n";
    cout << "1. Afiseaza multimea starilor\n";
    cout << "2. Afiseaza alfabetul\n";
    cout << "3. Afiseaza tranzitiile\n";
    cout << "4. Afiseaza starile finale\n";
    cout << "5. Verifica o secventa (doar determinist)\n";
    cout << "6. Gaseste cel mai lung prefix acceptat (doar determinist)\n";
    cout << "7. Incarca automat din fisier\n";
    cout << "8. Incarca automat de la tastatura\n";
    cout << "0. Iesire\n";
}

int main() {
    AutomatFinit af;
    string numeFisier;
    string secventa;
    int optiune;
    
    cout << "Introduceti numele fisierului pentru automat: ";
    cin >> numeFisier;
    af.citesteFisier(numeFisier);
    cout << "Automat incarcat cu succes\n";
    afiseaza_starea_automatului(af);

    do {
        afiseazaMeniu();
        cin >> optiune;

        switch (optiune) {
            case 1: 
                af.afiseazaStari(); 
                break;
            case 2: 
                af.afiseazaAlfabet(); 
                break;
            case 3: 
                af.afiseazaTranzitii(); 
                break;
            case 4: 
                af.afiseazaStariFinale(); 
                break;
            case 5:
                if (!af.esteDeterminist) {
                    cout << "Optiune valida doar pentru automat determinist\n";
                    break;
                }
                cout << "Introduceti secventa: ";

                // cin >> secventa;
                cin.ignore();
                getline(cin, secventa);
                if (af.verificaSecventa(secventa)) {
                    cout << "Secventa acceptata\n";
                } else {
                    cout << "Secventa respinsa\n";
                }
                break;
            case 6:
                if (!af.esteDeterminist) {
                    cout << "Optiune valida doar pentru automat determinist\n";
                    break;
                }
                cout << "Introduceti secventa: ";
                // cin >> secventa;
                cin.ignore();
                getline(cin, secventa);
                cout << "Cel mai lung prefix acceptat este: \"" 
                     << af.celMaiLungPrefixSecventa(secventa) << "\"\n";
                break;
            case 7:
                cout << "Introduceti numele fisierului: ";
                cin >> numeFisier;
                af = AutomatFinit(); 
                af.citesteFisier(numeFisier);
                cout << "Automat incarcat cu succes\n";
                afiseaza_starea_automatului(af);
                break;
            case 8:
                af = AutomatFinit();
                af.citesteTastatura();
                cout << "Automat incarcat cu succes\n";
                afiseaza_starea_automatului(af);
                break;
            case 0:
                break;
            default:
                cout << "Optiune invalida\n";
        }
    } while (optiune != 0);

    return 0;
}