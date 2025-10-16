#include "lexer.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

static map<string, TokenCode> reservedTokens;

Lexer::Lexer() {
    reservedTokens["int"] = INT; reservedTokens["float"] = FLOAT; reservedTokens["std::string"] = STRING;
    reservedTokens["if"] = IF; reservedTokens["else"] = ELSE; reservedTokens["for"] = FOR;
    reservedTokens["while"] = WHILE; reservedTokens["return"] = RETURN;
    
    reservedTokens["std::cin"] = STD_CIN;
    reservedTokens["std::cout"] = STD_COUT;
    
    reservedTokens["+"] = PLUS; reservedTokens["-"] = MINUS; reservedTokens["*"] = MULT;
    reservedTokens["/"] = DIV; reservedTokens["%"] = MOD; reservedTokens["="] = ASSIGN;
    reservedTokens["=="] = EQUAL; reservedTokens["<"] = LESS; reservedTokens["<="] = LESS_EQ;
    reservedTokens[">"] = GREATER; reservedTokens[">="] = GREATER_EQ; reservedTokens["!="] = NOT_EQ;
    reservedTokens["&&"] = LOGIC_AND; reservedTokens["||"] = LOGIC_OR;
    reservedTokens[">>"] = READ; reservedTokens["<<"] = WRITE;
    reservedTokens["("] = LPAREN; reservedTokens[")"] = RPAREN; reservedTokens["{"] = LBRACE;
    reservedTokens["}"] = RBRACE; reservedTokens[";"] = SEMICOLON; reservedTokens[","] = COMMA;
}

void Lexer::reportError(int line, const string& message) {
    cerr << "Eroare lexicala la linia " << line << ": " << message << endl;
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
        cerr << "Eroare: Nu s-a putut deschide fisierul " << inputFilename << endl;
        return false;
    }

    int line = 1;
    bool hasErrors = false;

    string firstLine;
    getline(file, firstLine);
    if (!firstLine.empty() && firstLine.back() == '\r') {
        firstLine.pop_back();
    }
    if (firstLine != "#include <iostream>") {
        reportError(1, "Programul trebuie sa inceapa cu '#include <iostream>'");
        return false;
    }
    FIP.push_back({INCLUDE_DIRECTIVE, -1});

    char ch;
    while (file.get(ch)) {
        if (isspace(ch)) {
            if (ch == '\n') line++;
            continue;
        }

        if (isalpha(ch)) {
            string token;
            token += ch;
            while (isalnum(file.peek()) || file.peek() == ':' || file.peek() == '_') {
                token += file.get();
            }

            if (token.length() > 250) {
                reportError(line, "Identificator prea lung (depaseste 250 de caractere)");
                hasErrors = true;
                continue;
            }
            
            if (reservedTokens.count(token)) {
                FIP.push_back({reservedTokens[token], -1});
            } else if (token.find(":") != string::npos || token.find("_") != string::npos) {
                reportError(line, "Identificator invalid conform MLP incepand cu: '" + token + "'");
                hasErrors = true;
            } else {
                int index = TS_ID.add(token);
                FIP.push_back({ID, index});
            }
        }
        
        else if (isdigit(ch) || ((ch == '+' || ch == '-') && isdigit(file.peek()))) {
            string token;
            token += ch;
            while (isdigit(file.peek())) {
                token += file.get();
            }
            
            if (file.peek() == '.') {
                token += file.get();
                if (!isdigit(file.peek())) {
                    reportError(line, "Constanta float malformata incepand cu: '" + token + "'");
                    hasErrors = true;
                    continue;
                }
                while (isdigit(file.peek())) {
                    token += file.get();
                }
            }

            if (isalpha(file.peek())) {
                reportError(line, "Constanta numerica malformata incepand cu: '" + token + "'");
                hasErrors = true;
                while(isalnum(file.peek())) file.get();
                continue;
            }
            
            int index = TS_CONST.add(token);
            FIP.push_back({CONST, index});
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
        }
        
        else {
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
