#include <string>
#include <fstream>

using namespace std;

class TabelaSimboluri {
private:
    string* data;
    int count;
    int capacity;

    void resize();

public:
    TabelaSimboluri();
    ~TabelaSimboluri();

    int add(const string& symbol);
    void saveToFile(ofstream& file) const;
};
