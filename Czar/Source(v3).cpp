#include<string>
#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdio>

using namespace std;

char Czar_Cryption(char&, const int&); // Symbol Czar cryption
string Czar_Cryption(string&, const int&); // Word Czar cryption
string Hronsfeld_Cryption(string&, const string&); // Word Hronsfeld Cryption

string word; // file input stream reader var
string keyh; // Hronsfeld key
int keyc; // Czar key
char ok;
char mode; // Crypt/encrypt mode reader

int main() {
	do{
		ifstream fin("text.txt"); // main file
		ofstream fout("o.txt"); // temp file
		system("cls"); // clearing console area
		//instruction
		cout << "This is realisation of the Czar cryption algorithm!\nBefore using the program, you must create a text file(text.txt) in the same program folder.\nCryption -> + key\nEncryption -> - key" << endl;
		// Mode selection
		do {
			cout << "Select mode Czar/Hronsfeld crypt algorithm(c/h): ";
			cin >> mode;
			mode = tolower(mode);
		} while (mode != 'c' && mode != 'h');
		
		cout << "Input the key: ";
		// Crypt part
		switch (mode) {
		case 'c': // Czar
			cin >> keyc; // czar key input

			fin >> word;
			fout << Czar_Cryption(word, keyc);
			while (!fin.eof())
			{
				fin >> word;
				fout << " " << Czar_Cryption(word, keyc);
			}
			break;
		case 'h': // Hronsfeld 
			cin >> keyh; // hronsfeld key input

			fin >> word;
			fout << Hronsfeld_Cryption(word, keyh);
			while (!fin.eof())
			{
				fin >> word;
				fout << " " << Hronsfeld_Cryption(word, keyh);
			}
		}
		//Closing processes with files
		fin.close();
		fout.close();
		//Operations with files
		if (!remove("text.txt") && !rename("o.txt", "text.txt")) cout << "Succes!"; else cout << "Something had gone wrong!";
		// Repeating? part
		cout << "\n Do you want to repeat?(y/n): ";
		cin >> ok;
	} while (tolower(ok) != 'n');
	system("pause");
	return 0;
}

// Encrypt/Decrypt functions

char Czar_Cryption(char& symbol, const int& key) {
	symbol = (symbol > 64 && symbol < 91) || (symbol > 96 && symbol < 123) ? islower(symbol) ? (symbol - 19 + key) % 26 + 'a' : (symbol - 13 + key) % 26 + 'A' : symbol;
	return symbol;
}

string Czar_Cryption(string& word, const int& key) {
	for (int i = 0; i < (int)word.size(); i++) word[i] = (word[i] > 64 && word[i] < 91) || (word[i] > 96 && word[i] < 123) ? islower(word[i]) ? (word[i] - 19 + key) % 26 + 'a' : (word[i] - 13 + key) % 26 + 'A' : word[i];
	return word;
}

string Hronsfeld_Cryption(string& word, const string& key) {
	for (int i = 0; i < (int)word.size(); i++) word[i] = key[0] > 47 && key[0] < 57 || key[0]=='+' || key[0]=='-' ? Czar_Cryption(word[i], key[0]!='+' && key[0]!='-' ? key[i % (int)key.size()] - '0': key[0] == '+' ? key[i % ((int)key.size()-1)+1] - '0': -(key[i % ((int)key.size() - 1) + 1] - '0')):'#';
	return word;
}
