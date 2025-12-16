#include <bits/stdc++.h>

using namespace std;

struct Regula {
    char stanga;
    string dreapta;
};

class Gramatica {
private:
    vector<Regula> reguli;

public:
    void citeste(string filename) {
        ifstream fin(filename);

        char stanga;
        string sageata, dreapta;
        // presupun format de tip A -> aB
    
        while (fin >> stanga >> sageata >> dreapta) reguli.push_back({stanga, dreapta});
        fin.close();
    }

    void afiseazaRecursiveDreapta() {
        for (auto regula : reguli) {
            if (regula.stanga == regula.dreapta.back()) {
                cout << regula.stanga << " -> " << regula.dreapta << "\n";
            }
        }
    }
};

int main() {
    Gramatica g;
    g.citeste("gramatica.txt");
    g.afiseazaRecursiveDreapta();
    return 0;
}
