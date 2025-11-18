#include <iostream>
#include <fstream>
#include <vector>
#include "TabelaSimboluri.h"

using namespace std;

extern FILE* yyin;
extern int yylex();
extern vector<pair<int, int>> FIP;
extern TabelaSimboluri TS_ID;
extern TabelaSimboluri TS_CONST;

void saveResults(const string& fipFilename, const string& tsIdFilename, const string& tsConstFilename) {
    ofstream fipFile(fipFilename);
    fipFile << "COD ATOM\t\tINDEX TS\n";
    for (const auto& pair : FIP) {
        fipFile << pair.first << " \t\t" << pair.second << "\n";
    }
    fipFile.close();

    ofstream tsIdFile(tsIdFilename);
    TS_ID.saveToFile(tsIdFile);
    tsIdFile.close();

    ofstream tsConstFile(tsConstFilename);
    TS_CONST.saveToFile(tsConstFile);
    tsConstFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        cout << "eroare: nu s-a putut deschide fisierul " << argv[1] << "\n";
        return 1;
    }

    yylex();

    saveResults("fip.txt", "ts_id.txt", "ts_const.txt");
    cout << "Analiza lexicala finalizata. Rezultate salvate.\n";

    fclose(yyin);
    return 0;
}
