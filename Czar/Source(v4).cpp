#include<string>
#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdio>

using namespace std;

inline char Czar_Cryption(char&, const int&); // Czar cryption
inline char Gronsfeld_Cryption(char&, const string&); // Gronsfeld Cryption

string keyg; // Gronsfeld 
int keyc; // Czar key
char ch, ok, mode; // file input stream symbols reader // Loop accepter // Crypt/encrypt mode reader

unsigned long long int i; // kostil ((((MAYBE)))) before better realisation of Gronsfeld crypt algorithm // TODO: CHANGE!

int main() {
	do {
		::i = 0; // for Gronsfeld char counter RESET OPERATION // TODO:CHANGE! 

		system("cls"); // Clearing console area
		while (!ifstream("text.txt")) {
			cout << "WARNING!!!: To continue, you must create a text file \"text.txt\" in the same program folder and press Enter.\n";
			system("pause");
			system("cls"); // Warn clearing
		}
		ifstream fin("text.txt"); // Main file
		ofstream fout("o.temp"); // Temp file
		//instruction
		cout << "This is the implementation of encryption algorithms Czar and Greensfeld!\nSelect the encryption algorithm c(CZAR)/g(GRONSFELD).\nEncryption -> + key\nDecryption -> - key" << endl;
		// Mode selection
		do {
			cout << "Select mode Czar/Gronsfeld crypt algorithm(c/h): ";
			cin >> mode;
			mode = tolower(mode);
		} while (mode != 'c' && mode != 'g');

		cout << "Input the key: ";
		if (mode == 'c')
			cin >> keyc; // Czar key input 
		else
			cin >> keyg; // Gronsfeld key input
		// (En/De)crypt part
		while (!fin.eof() && fin.get(ch))
			fout.put(mode == 'c' ? Czar_Cryption(ch, keyc) : Gronsfeld_Cryption(ch, keyh));
		// Closing processes with files
		fin.close();
		fout.close();
		// Operations with files
		if (!remove("text.txt") && !rename("o.temp", "text.txt")) cout << "Succes!"; else cout << "Something had gone wrong!";
		// Repeating? part
		cout << "\n Do you want to repeat?(y/n): ";
		cin >> ok;
	} while (tolower(ok) != 'n');
	system("pause");
	return 0;
}

// Encrypt/Decrypt functions

inline char Czar_Cryption(char& symbol, const int& key) {
	return (symbol > 64 && symbol < 91) || (symbol > 96 && symbol < 123) ? islower(symbol) ? (symbol - 19 + key) % 26 + 'a' : (symbol - 13 + key) % 26 + 'A' : symbol;
}

inline char Gronsfeld_Cryption(char& symbol, const string& key) {
	return (symbol > 64 && symbol < 91) || (symbol > 96 && symbol < 123) ? (key[0] > 47 && key[0] < 58) || (key[0] == '+' || key[0] == '-') ? Czar_Cryption(symbol, (key[0] != '+' && key[0] != '-') ? key[::i++ % (int)key.size()] - '0' : (key[0] == '+') ? key[::i++ % ((int)key.size() - 1) + 1] - '0' : -(key[::i++ % ((int)key.size() - 1) + 1] - '0')) : '#' : symbol;
}
