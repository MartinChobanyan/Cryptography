#include<string>
#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdio>

using namespace std;

string Czar_Cryption(string&, const int&);

string word;
int key;
char ok;
bool t=false;

int main() {
	do{
		ifstream fin("text.txt"); // main file
		ofstream fout("o.temp"); // temp file
		system("cls"); // clearing console area
		cout << fin.eof();
		//instruction
		cout << "This is realisation of the Czar cryption algorithm!\nBefore using the program, you must create a text file(text.txt) in the same program folder.\nCryption -> + key\nEncryption -> - key\n";
		// key input
		cout << "Input the key: ";
		cin >> key;
		// Crypt part
		//fin >> word;
		//fout << Czar_Cryption(word, key);
		while (!fin.eof())
		{
			fin >> word;
			if (t) fout << " "; else t = true;
			fout << Czar_Cryption(word, key);
		}
		//Closing processes with files
		fin.close();
		fout.close();
		//Operations with files
		if (!remove("text.txt") && !rename("o.temp", "text.txt")) cout << "Succes!"; else cout << "Something had gone wrong!";
		// Repeating? part
		cout << "\n Do you want to repeat?(y/n): ";
		cin >> ok;
	} while (tolower(ok) == 'y');
	system("pause");
	return 0;
}

// Encrypt/Decrypt function
string Czar_Cryption(string& word, const int& key) {
	for (int i = 0; i < (int)word.size(); i++) word[i] = (word[i] > 64 && word[i] < 91) || (word[i] > 96 && word[i] < 123) ? islower(word[i]) ? (word[i] - 19 + key) % 26 + 'a' : (word[i] - 13 + key) % 26 + 'A' : word[i];
	return word;
}
