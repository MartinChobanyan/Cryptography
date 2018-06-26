#include<string>
#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdio>

using namespace std;

inline char Czar_Cryption(char&, const int&); // Czar cryption
inline char Gronsfeld_Cryption(char&, const string&); // Gronsfeld Cryption
bool keychecker(const int&); // Czar keychecker
bool keychecker(const string&); // Gronsfeld keychecker

string keyg, filename; // Gronsfeld // (En/De)crypt file name 
int keyc; // Czar key
char ch, ok, mode; // file input stream symbols reader // Loop accepter // Crypt/encrypt mode reader

unsigned long long int i; // kostil ((((MAYBE)))) before better realisation of Gronsfeld crypt algorithm // TODO: CHANGE!

int main() {
	cout << "This is the implementation of encryption algorithms Czar and Greensfeld!\n\nWrite the file name, which must be (En/De)crypted: ";
	getline(cin, filename);
	while (!ifstream(filename)) cout << "You must write the correct file name: ", getline(cin, filename);

	do {
		::i = 0; // for Gronsfeld char counter RESET OPERATION // TODO:CHANGE! 

		system("cls"); // Clearing console area
		ifstream fin(filename); // Main file
		ofstream fout("o.temp"); // Temp file
		//instruction
		cout << "Select the encryption algorithm c(CZAR)/g(GRONSFELD).\nEncryption -> + key\nDecryption -> - key" << endl;
		// Mode selection
		do {
			cout << "Select mode Czar/Gronsfeld crypt algorithm(c/g): ";
			cin >> mode;
			mode = tolower(mode);
		} while (mode != 'c' && mode != 'g');

		cin.exceptions(istream::failbit | istream::badbit); // for catching error inputs 
		
		do {
			bool i = true; // temp bool
			cout << "Input the key: ";
			if (mode == 'c') {
				// input type err catcher block
				try {
					cin >> keyc; // Czar key input
				}
				catch (const istream::failure& e) {
					cin.clear(); // istream cleaner
					i = false; // wrong(false) type input
				}
			}
			else
				cin >> keyg; // Gronsfeld key input
		} while (!i && mode == 'c' ? !keychecker(keyc) : !keychecker(keyg));
		// Crypt part
		while (!fin.eof()) // Checking for End Of File
			if(fin.get(ch)) // Checking istream chars
				fout.put(mode == 'c' ? Czar_Cryption(ch, keyc) : Gronsfeld_Cryption(ch, keyg)); // puting chars into ostream
		// Closing processes with files
		fin.close();
		fout.close();
		// Operations with files
		if (!remove("text.txt") && !rename("o.temp", "text.txt")) cout << "Succes!"; else cout << "Something had gone wrong!";
		// Repeating? part
		cout << "\n Do you want to repeat?(y/n): ";
		cin >> ok;
	} while (tolower(ok) != 'n');
	return 0;
}

// Encrypt/Decrypt functions

inline char Czar_Cryption(char& symbol, const int& key) {
	return (symbol > 64 && symbol < 91) || (symbol > 96 && symbol < 123) ? islower(symbol) ? (symbol - 19 + key) % 26 + 'a' : (symbol - 13 + key) % 26 + 'A' : symbol;
}

inline char Gronsfeld_Cryption(char& symbol, const string& key) {
	return (symbol > 64 && symbol < 91) || (symbol > 96 && symbol < 123) ? Czar_Cryption(symbol, (key[0] != '+' && key[0] != '-') ? key[::i++ % (int)key.size()] - '0' : (key[0] == '+') ? key[::i++ % ((int)key.size() - 1) + 1] - '0' : -(key[::i++ % ((int)key.size() - 1) + 1] - '0')) : symbol;
}

bool keychecker(const int& keyc) {
	::keyc = keyc>0 ? keyc % 26 : -(-keyc%26);
	return true;
}

bool keychecker(const string& keyg) {
	for (int i = 0; i < (int)keyg.size(); i++) {
		if (i == 0) {
			if (keyg[i] != '+' || keyg[i] != '-') {
				if (keyg[i] < '0' || keyg[i] > '9') return false;
			}
			else "Good";
		}
		else if (keyg[i] < '0' || keyg[i] > '9') return false;
	}
	return true;
}
