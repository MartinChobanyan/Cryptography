#include<string>
#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdio>

using namespace std;

inline char Czar_Cryption(char&, const int&); // Czar (En/De)cryption Function
inline char Gronsfeld_Cryption(char&, const string&); // Gronsfeld (En/De)ryption Function
inline bool keychecker(int&); // Czar keychecker
bool keychecker(const string&); // Gronsfeld keychecker

string keyg, filename; // Gronsfeld // (En/De)cryption file name
int keyc; // Czar key
char ch, ok, mode; // file input stream symbols reader // Loop accepter // (En/De)crypt mode reader

unsigned short i; // kostil ((((MAYBE)))) before better realisation of Gronsfeld crypt algorithm // TODO: CHANGE!

int main() {
    cout << "This is the implementation of encryption algorithms Czar and Gronsfeld!\n\nWrite the file name, which must be (En/De)crypted: ";
    getline(cin, filename);
    while (!ifstream(filename)) cout << "You must write the correct file name: ", getline(cin, filename);

    do {
        ::i = -1; // for Gronsfeld char counter RESET OPERATION // TODO:CHANGE!

        cout << endl; // for diferencing texts

        ifstream fin(filename); // Main file
        ofstream fout("o.temp"); // Temp file
        //instruction
        cout << "Select the encrypt algorithm mode -> c(CZAR)/g(GRONSFELD).\nEncryption -> + key\nDecryption -> - key" << endl;
        // Mode selection
        do {
            cout << "Select the encrypt algorithm mode(c/g): ";
            cin >> mode;
            mode = tolower(mode);
        } while (mode != 'c' && mode != 'g');

        cin.exceptions(istream::failbit | istream::badbit); // for catching error inputs

        do {
            cout << "Input the key: ";
            if (mode == 'c') {
                // input type err catcher block
                try {
                    cin >> keyc; // Czar key input
                }
                catch (const istream::failure& e) {
                    cin.clear(); // istream cleaner
                }
            }
            else
                cin >> keyg; // Gronsfeld key input
        } while (mode == 'c' ? !keychecker(keyc) : !keychecker(keyg));
        // Crypt part
        while (!fin.eof()) // Checking for End Of File
            if(fin.get(ch)) // Checking istream chars
                fout.put(mode == 'c' ? Czar_Cryption(ch, keyc) : Gronsfeld_Cryption(ch, keyg)); // puting chars into ostream
        // Closing processes with files
        fin.close();
        fout.close();
        // Operations with files
        if (!remove(filename.c_str()) && !rename("o.temp", filename.c_str())) cout << "Succes!"; else cerr << "Something had gone wrong!";
        // Repeating? part
        cout << "\n Do you want to continue encryption of this file?(y/n): ";
        cin >> ok;
    } while (tolower(ok) != 'n');
    return 0;
}

// Encryption/Decryption Functions

inline char Czar_Cryption(char& symbol, const int& key) {
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') ? islower(symbol) ? (symbol - 19 + key) % 26 + 'a' : (symbol - 13 + key) % 26 + 'A' : symbol;
}

inline char Gronsfeld_Cryption(char& symbol, const string& key) {
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol < 'Z') ? Czar_Cryption(symbol, (key[0] != '+' && key[0] != '-') ? key[::i++ % (int)key.size()] - '0' : (key[0] == '+') ? key[::i++ % ((int)key.size() - 1) + 1] - '0' : -(key[::i++ % ((int)key.size() - 1) + 1] - '0')) : symbol;
}

inline bool keychecker(int& keyc) {
    return keyc %= 26;
}

bool keychecker(const string& keyg) {
    if (keyg.size() < 2 && keyg[0] != '+' && keyg[0] != '-' && (keyg[0]<'0' && keyg[0]>'9')) return false;
    for (int i = 1; i < (int)keyg.size(); i++) if (keyg[i] < '0' || keyg[i] > '9') return false;
    return true;
}
