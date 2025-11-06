#include "lexer.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

map<string, AtomCode> reservedTokens;

Lexer::Lexer() {
    reservedTokens["int"] = INT; reservedTokens["float"] = FLOAT; reservedTokens["string"] = STRING;
    reservedTokens["if"] = IF; reservedTokens["else"] = ELSE;
    reservedTokens["while"] = WHILE; reservedTokens["return"] = RETURN;
    
    reservedTokens["cin"] = CIN;
    reservedTokens["cout"] = COUT;
    
    reservedTokens["+"] = PLUS; reservedTokens["-"] = MINUS; reservedTokens["*"] = MULT;
    reservedTokens["/"] = DIV; reservedTokens["%"] = MOD; reservedTokens["="] = ASSIGN;
    reservedTokens["=="] = EQUAL; reservedTokens["<"] = LESS; reservedTokens["<="] = LESS_EQ;
    reservedTokens[">"] = GREATER; reservedTokens[">="] = GREATER_EQ; reservedTokens["!="] = NOT_EQ;
    reservedTokens["&&"] = LOGIC_AND; reservedTokens["||"] = LOGIC_OR;
    reservedTokens[">>"] = READ; reservedTokens["<<"] = WRITE;
    reservedTokens["("] = LEFT_PAREN; reservedTokens[")"] = RIGHT_PAREN; reservedTokens["{"] = LEFT_BRACE;
    reservedTokens["}"] = RIGHT_BRACE; reservedTokens[";"] = SEMICOLON; reservedTokens[","] = COMMA;

    af_id.citesteFisier("af_id.txt");
    af_int.citesteFisier("af_int.txt");
    af_float.citesteFisier("af_float.txt");
}

void Lexer::reportError(int line, const string& message) {
    cout << "Eroare lexicala la linia " << line << ": " << message << "\n";
}

void Lexer::saveResults(const string& fipFilename, const string& tsIdFilename, const string& tsConstFilename) {
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

bool Lexer::analyze(const string& inputFilename) {
    ifstream file(inputFilename);
    if (!file.is_open()) {
        cout << "Eroare: Nu s-a putut deschide fisierul " << inputFilename << "\n";
        return false;
    }

    int line = 3;
    bool hasErrors = false;

    string firstLine;
    getline(file, firstLine);
    if (firstLine != "#include <iostream>") {
        reportError(1, "Programul trebuie sa inceapa cu '#include <iostream>'");
        return false;
    }
    FIP.push_back({INCLUDE_DIRECTIVE, -1});

    string secondLine;
    getline(file, secondLine);
    if (secondLine != "using namespace std;") {
        reportError(2, "A doua linie trebuie sa fie directiva pentru folosirea std: 'using namespace std;'");
        return false;
    }
    FIP.push_back({STD_DIRECTIVE, -1});

    char ch;
while (file.get(ch)) {
        if (isspace(ch)) {
            if (ch == '\n') line++;
            continue;
        }

        if (isalpha(ch)) {
            string token = "";
            string stare_curenta = af_id.getStareInitiala();
            bool valid = true;
            file.unget();
            while (valid) {
                char next;
                if (!file.get(next)) break;
                string noua_stare = af_id.getTranzitie(stare_curenta, next);
                if (!noua_stare.empty()) {
                    stare_curenta = noua_stare;
                    token += next;
                } else {
                    file.unget();
                    valid = false;
                }
            }
            if (af_id.esteStareFinala(stare_curenta) && !token.empty()) {
                if (token.length() > 250) {
                    reportError(line, "Identificator prea lung (> 250 caractere)");
                    hasErrors = true;
                    continue;
                }


                if (reservedTokens.count(token)) {
                    FIP.push_back({reservedTokens[token], -1});
                } else {
                    int index = TS_ID.add(token);
                    FIP.push_back({ID, index});
                }
            } else {
                reportError(line, "Identificator invalid incepand cu: '" + token + "'");
                hasErrors = true;
            }
        } 
        else if (isdigit(ch) || ((ch == '+' || ch == '-') && isdigit(file.peek()))) {
            string token;
            file.unget();

            AutomatFinit* af_intreg = &af_int;
            AutomatFinit* af_real = &af_float;
            string s_int = af_intreg->getStareInitiala();
            string s_real = af_real->getStareInitiala();
            bool alive_int = true, alive_real = true;
            string lastFinalToken;
            bool intFinal = false, realFinal = false;

            while (true) {
                char c;
                if (!file.get(c)) break;
                token += c;

                string next_int = alive_int ? af_intreg->getTranzitie(s_int, c) : "";
                string next_real = alive_real ? af_real->getTranzitie(s_real, c) : "";

                if (!next_int.empty()) s_int = next_int;
                else alive_int = false;

                if (!next_real.empty()) s_real = next_real;
                else alive_real = false;

                if (alive_int && af_intreg->esteStareFinala(s_int)) {
                    lastFinalToken = token;
                    intFinal = true;
                    realFinal = false;
                }
                if (alive_real && af_real->esteStareFinala(s_real)) {
                    lastFinalToken = token;
                    realFinal = true;
                    intFinal = false;
                }

                if (!alive_int && !alive_real) break;
            }

            if (intFinal || realFinal) {
                int index = TS_CONST.add(lastFinalToken);
                FIP.push_back({CONST, index});
            } else {
                reportError(line, "Constanta numerica malformata incepand cu: '" + token + "'");
                hasErrors = true;
            }
        }
 else if (ch == '"') {
            string token;
            bool stringClosed = false;
            while (file.get(ch)) {
                if (ch == '"') {
                    stringClosed = true;
                    break;
                }
                if (ch == '\n') {
                    line++;
                    break;
                }
                token += ch;
            }
            if (!stringClosed) {
                reportError(line, "String neterminat");
                hasErrors = true;
            } else {
                int index = TS_CONST.add("\"" + token + "\"");
                FIP.push_back({CONST, index});
            }
        } else {
            string token;
            token += ch;
            char nextChar = file.peek();
            if ((ch == '<' || ch == '>' || ch == '=' || ch == '!') && nextChar == '=') {
                token += file.get();
            } else if (ch == '<' && nextChar == '<') {
                token += file.get();
            } else if (ch == '>' && nextChar == '>') {
                token += file.get();
            } else if (ch == '&' && nextChar == '&') {
                token += file.get();
            } else if (ch == '|' && nextChar == '|') {
                token += file.get();
            }
            if (reservedTokens.count(token)) {
                FIP.push_back({reservedTokens[token], -1});
            } else {
                reportError(line, "Caracter sau secventa invalida incepand cu: '" + token + "'");
                hasErrors = true;
            }
        }
    }

    return !hasErrors;
}
