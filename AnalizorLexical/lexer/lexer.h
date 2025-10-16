#include <string>
#include <vector>
#include <utility>
#include "TabelaSimboluri.h"

using namespace std;

enum AtomCode {
    ID = 0, CONST = 1,
    INT = 2, FLOAT = 3, STRING = 4, IF = 5, ELSE = 6, FOR = 7, WHILE = 8,
    RETURN = 9,
    STD_CIN = 10, STD_COUT = 11,
    PLUS = 12, MINUS = 13, MULT = 14, DIV = 15, MOD = 16,
    ASSIGN = 17, EQUAL = 18, LESS = 19, LESS_EQ = 20, GREATER = 21,
    GREATER_EQ = 22, NOT_EQ = 23,
    LOGIC_AND = 24, LOGIC_OR = 25,
    READ = 26, WRITE = 27,
    LPAREN = 28, RPAREN = 29, LBRACE = 30, RBRACE = 31, SEMICOLON = 32, COMMA = 33,
    INCLUDE_DIRECTIVE = 34
};


class Lexer {
public:
    Lexer();
    bool analyze(const string& inputFilename);
    void saveResults(const string& fipFilename, const string& tsIdFilename, const string& tsConstFilename);

private:
    vector<pair<int, int>> FIP;
    TabelaSimboluri TS_ID;
    TabelaSimboluri TS_CONST;

    void reportError(int line, const string& message);
};
