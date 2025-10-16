#include "TabelaSimboluri.h"

TabelaSimboluri::TabelaSimboluri() {
    capacity = 8;
    count = 0;
    data = new string[capacity];
}

TabelaSimboluri::~TabelaSimboluri() {
    delete[] data;
}

void TabelaSimboluri::resize() {
    capacity *= 2;
    string* newData = new string[capacity];
    for (int i = 0; i < count; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

int TabelaSimboluri::add(const string& symbol) {
    // sa fie pastrata ordinea lexicografica
    int low = 0;
    int high = count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (data[mid] == symbol) {
            return mid;
        }
        if (data[mid] < symbol) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    int insertPos = low;

    if (count == capacity) {
        resize();
    }

    for (int i = count; i > insertPos; --i) {
        data[i] = data[i - 1];
    }

    data[insertPos] = symbol;
    count++;

    return insertPos;
}

void TabelaSimboluri::saveToFile(ofstream& file) const {
    file << "ATOM\t\tINDEX\n";

    for (int i = 0; i < count; ++i) {
        file << data[i] << "\t\t" << i << "\n";
    }
}
