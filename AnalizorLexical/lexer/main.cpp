#include "lexer.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Nu e bine\n";
        return 1;
    }


    string filename = argv[1];
    Lexer lexer;
    

    if (lexer.analyze(filename)) {
        lexer.saveResults("fip.txt", "ts_id.txt", "ts_const.txt");
        cout << "Analiza lexicala finalizata\n";
    } else {
        cout << "Analiza lexicala a esuat din cauza erorilor\n";
    }

    return 0;
}
