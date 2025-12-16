#include <iostream>
#include <fstream>
#include <vector>
#include "TabelaSimboluri.h"

using namespace std;

extern FILE* yyin;
extern int yyparse();

int currentLine = 1;
bool hasLexicalErrors = false;

vector<pair<int, int>> FIP;
TabelaSimboluri TS_ID;
TabelaSimboluri TS_CONST;

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
        cout << "Eroare: ./parser <sursa>\n";
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        cout << "Eroare: nu s-a putut deschide fisierul " << argv[1] << "\n";
        return 1;
    }

    int rezultat = yyparse();

    if (rezultat == 0 && !hasLexicalErrors) {
        cout << "Analiza sintactica finalizata cu succes!\n";
        saveResults("fip.txt", "ts_id.txt", "ts_const.txt");
    } else {
        cout << "Analiza esuata ( Erori ";
        if (hasLexicalErrors) cout << "lexicale ";
        if (rezultat != 0) cout << "sintactice ";
        cout << ").\n";
    }

    fclose(yyin);
    return 0;
}
