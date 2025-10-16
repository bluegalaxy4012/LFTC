#include "lexer.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Utilizare: " << argv[0] << " <sursa>\n";
        return 1;
    }


    string filename = argv[1];
    Lexer lexer;
    

    if (lexer.analyze(filename)) {
        lexer.saveResults("FIP.txt", "TS_ID.txt", "TS_CONST.txt");
        cout << "Analiza lexicala finalizata\n";
    } else {
        cerr << "Analiza lexicala a esuat din cauza erorilor\n";
    }

    return 0;
}
