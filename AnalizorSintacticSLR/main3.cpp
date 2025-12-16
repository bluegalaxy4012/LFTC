#include <bits/stdc++.h>
using namespace std;



struct Productie {
    int id;
    string stanga;
    vector<string> dreapta;
};

struct Item {
    int idProd;
    int punct;

    bool operator<(const Item& other) const {
        if (idProd != other.idProd) return idProd < other.idProd;
        return punct < other.punct;
    }

    bool operator==(const Item& other) const {
        return idProd == other.idProd && punct == other.punct;
    }
};

struct Actiune {
    char tip;
    int valoare;
};



class SLRParser {
    vector<Productie> productii;

    set<string> terminali;
    set<string> neterminali;

    string startSimbol;

    map<string, set<string>> first;
    map<string, set<string>> follow;

    vector<set<Item>> colectieCanonica;

    map<pair<int, string>, int> tabelaGoto;
    map<pair<int, string>, Actiune> tabelaActiuni;



    set<string> firstSecventa(const vector<string>& seq) {
        set<string> rezultat;
        bool totEps = true;

        for (auto& s : seq) {
            if (s == "EPS") continue;

            if (terminali.count(s)) {
                rezultat.insert(s);
                totEps = false;
                break;
            }

            for (auto& x : first[s]) {
                if (x != "EPS") rezultat.insert(x);
            }

            if (!first[s].count("EPS")) {
                totEps = false;
                break;
            }
        }

        if (totEps) rezultat.insert("EPS");
        return rezultat;
    }



    set<Item> closure(set<Item> items) {
        bool schimbat = true;

        while (schimbat) {
            schimbat = false;
            set<Item> copie = items;

            for (auto& it : items) {
                if (it.punct < productii[it.idProd].dreapta.size()) {
                    string simbol = productii[it.idProd].dreapta[it.punct];

                    if (neterminali.count(simbol)) {
                        for (auto& p : productii) {
                            if (p.stanga == simbol) {
                                Item nou{p.id, 0};
                                if (p.dreapta[0] == "EPS") nou.punct = 1;

                                if (!copie.count(nou)) {
                                    copie.insert(nou);
                                    schimbat = true;
                                }
                            }
                        }
                    }
                }
            }

            items = copie;
        }

        return items;
    }



    set<Item> gotoStare(const set<Item>& items, const string& simbol) {
        set<Item> rezultat;

        for (auto& it : items) {
            if (it.punct < productii[it.idProd].dreapta.size()) {
                if (productii[it.idProd].dreapta[it.punct] == simbol) {
                    rezultat.insert({it.idProd, it.punct + 1});
                }
            }
        }

        return closure(rezultat);
    }



public:
    void incarcaGramatica(const string& numeFisier) {
        ifstream f(numeFisier);
        string linie;

        productii.push_back({0, "S'", {}});
        neterminali.insert("S'");

        int id = 1;

        while (getline(f, linie)) {
            if (linie.empty()) continue;

            stringstream ss(linie);
            string stanga, sageata, simbol;

            ss >> stanga >> sageata;

            if (productii[0].dreapta.empty()) {
                productii[0].dreapta.push_back(stanga);
                startSimbol = stanga;
            }

            neterminali.insert(stanga);

            Productie p;
            p.id = id++;
            p.stanga = stanga;

            while (ss >> simbol) p.dreapta.push_back(simbol);
            if (p.dreapta.empty()) p.dreapta.push_back("EPS");

            productii.push_back(p);
        }

        for (auto& p : productii) {
            for (auto& s : p.dreapta) {
                if (!neterminali.count(s) && s != "EPS") {
                    terminali.insert(s);
                }
            }
        }

        terminali.insert("$");
    }



    void calculeazaFirst() {
        for (auto& nt : neterminali) {
            for (auto& p : productii) {
                if (p.stanga == nt) {
                    if (p.dreapta[0] == "EPS") first[nt].insert("EPS");
                    else if (terminali.count(p.dreapta[0])) first[nt].insert(p.dreapta[0]);
                }
            }
        }

        bool schimbat = true;

        while (schimbat) {
            schimbat = false;

            for (auto& p : productii) {
                auto vechi = first[p.stanga].size();
                auto fs = firstSecventa(p.dreapta);
                first[p.stanga].insert(fs.begin(), fs.end());

                if (first[p.stanga].size() > vechi) schimbat = true;
            }
        }
    }



    void calculeazaFollow() {
        follow[startSimbol].insert("$");
        bool schimbat = true;

        while (schimbat) {
            schimbat = false;

            for (auto& p : productii) {
                for (int i = 0; i < p.dreapta.size(); i++) {
                    string B = p.dreapta[i];

                    if (neterminali.count(B)) {
                        vector<string> beta;
                        for (int k = i + 1; k < p.dreapta.size(); k++)
                            beta.push_back(p.dreapta[k]);

                        auto fBeta = firstSecventa(beta);
                        auto vechi = follow[B].size();

                        for (auto& x : fBeta)
                            if (x != "EPS") follow[B].insert(x);

                        if (fBeta.count("EPS") || beta.empty()) {
                            follow[B].insert(follow[p.stanga].begin(), follow[p.stanga].end());
                        }

                        if (follow[B].size() > vechi) schimbat = true;
                    }
                }
            }
        }
    }



    void construiesteTabela() {
        colectieCanonica.push_back(closure({{0, 0}}));
        bool schimbat = true;

        while (schimbat) {
            schimbat = false;

            for (int i = 0; i < colectieCanonica.size(); i++) {
                set<string> simboluri;

                for (auto& it : colectieCanonica[i]) {
                    if (it.punct < productii[it.idProd].dreapta.size()) {
                        string s = productii[it.idProd].dreapta[it.punct];
                        if (s != "EPS") simboluri.insert(s);
                    }
                }

                for (auto& s : simboluri) {
                    auto stareNoua = gotoStare(colectieCanonica[i], s);
                    if (stareNoua.empty()) continue;

                    int index = -1;
                    for (int k = 0; k < colectieCanonica.size(); k++) {
                        if (colectieCanonica[k] == stareNoua) {
                            index = k;
                            break;
                        }
                    }

                    if (index == -1) {
                        colectieCanonica.push_back(stareNoua);
                        index = colectieCanonica.size() - 1;
                        schimbat = true;
                    }

                    if (neterminali.count(s))
                        tabelaGoto[{i, s}] = index;
                    else
                        tabelaActiuni[{i, s}] = {'s', index};
                }
            }
        }

        for (int i = 0; i < colectieCanonica.size(); i++) {
            for (auto& it : colectieCanonica[i]) {
                bool final =
                    it.punct == productii[it.idProd].dreapta.size() ||
                    (productii[it.idProd].dreapta[0] == "EPS" && it.punct == 1);

                if (final) {
                    if (it.idProd == 0) {
                        tabelaActiuni[{i, "$"}] = {'a', 0};
                    } else {
                        for (auto& f : follow[productii[it.idProd].stanga]) {
                            tabelaActiuni[{i, f}] = {'r', it.idProd};
                        }
                    }
                }
            }
        }

        cout << "tabela SLR construita. nr stari: " << colectieCanonica.size() << '\n';
    }



    void parseaza(vector<string> input) {
        input.push_back("$");

        stack<int> st;
        st.push(0);

        int poz = 0;


        while (true) {
            int stare = st.top();
            string simbol = input[poz];

            cout << "stare/simbol " << stare << '/' << simbol << '\n';

            if (!tabelaActiuni.count({stare, simbol})) {
                cout << "eroare la simbolul " << simbol << '\n';
                return;
            }

            auto act = tabelaActiuni[{stare, simbol}];
            cout << "actiune " << act.tip << ' ' << act.valoare << '\n';

            if (act.tip == 's') {
                st.push(act.valoare);
                poz++;
            }
            else if (act.tip == 'r') {
                auto& p = productii[act.valoare];

                if (p.dreapta[0] != "EPS") {
                    for (int i = 0; i < p.dreapta.size(); i++) st.pop();
                }

                int top = st.top();
                st.push(tabelaGoto[{top, p.stanga}]);
            }
            else {
                cout << "ACCEPTAT\n";
                return;
            }
        }
    }
};


string atomCodToString(int cod) {
    static map<int, string> mapping = {
        {0, "ID"},
        {1, "CONST_INT"},

        {2, "KEY_INT"},
        {3, "KEY_FLOAT"},
        {4, "KEY_STRING"},
        {5, "KEY_IF"},
        {6, "KEY_ELSE"},
        {7, "KEY_WHILE"},
        {8, "KEY_RETURN"},
        {9, "KEY_MAIN"},

        {10, "KEY_CIN"},
        {11, "KEY_COUT"},

        {12, "OP_PLUS"},
        {13, "OP_MINUS"},
        {14, "OP_MULT"},
        {15, "OP_DIV"},
        {16, "OP_MOD"},

        {17, "OP_ASSIGN"},
        {18, "OP_EQ"},
        {19, "OP_LT"},
        {20, "OP_LTE"},
        {21, "OP_GT"},
        {22, "OP_GTE"},
        {23, "OP_NEQ"},
        {24, "OP_AND"},
        {25, "OP_OR"},

        {26, "OP_READ"},
        {27, "OP_WRITE"},

        {28, "DELIM_LPAREN"},
        {29, "DELIM_RPAREN"},
        {30, "DELIM_LBRACE"},
        {31, "DELIM_RBRACE"},
        {32, "DELIM_SEMICOLON"},
        {33, "DELIM_COMMA"},

        {34, "DIR_INCLUDE"},
        {35, "DIR_USING"},

        {36, "KEY_DO"},
        {37, "KEY_DOEND"}
    };

    if (mapping.count(cod)) return mapping[cod];
    
    return "IDK";
}


int main() {
    SLRParser parser;

    parser.incarcaGramatica("gramatica3.txt");
    parser.calculeazaFirst();
    parser.calculeazaFollow();
    parser.construiesteTabela();

    ifstream fipFile("fip.txt");

    vector<string> input;
    int codAtom, pozTS;

    while (fipFile >> codAtom) {
        fipFile >> pozTS; 

        string tokenName = atomCodToString(codAtom);
        if (tokenName == "IDK") {
            cerr << "cod atom necunoscut in fip: " << codAtom << endl;
            return 1;
        }
        cout << "fip: " << codAtom << " -> " << tokenName << endl;
        input.push_back(tokenName);
    }
    fipFile.close();

    parser.parseaza(input);

    
    return 0;
}