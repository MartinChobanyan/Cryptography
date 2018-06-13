#include<string>
#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdio>

using namespace std;

string Czar_Cryption(string&,const int&);

string word;
int key;
ifstream fin("text.txt");
ofstream fout("output.txt");
bool t=false;

int main() {
	cout << "This is realisation of the Czar cryption algorithm!\nBefore using the program, you must create a text file(text.txt) in the same program folder.\nCryption -> + key\nEncryption -> - key\n";
	cout << "Input the key: ";
	cin >> key;
	while (!fin.eof())
	{
		fin >> word;
		if (t) fout << " ";else t = true;
		fout << Czar_Cryption(word, key);
	} 
	fin.close();
	fout.close();
	if (remove("text.txt") & rename("output.txt", "text.txt")) cout << "Something had gone wrong!"; else cout << "Succes!";
	cout << endl;
	system("pause");
	return 0;
}

string Czar_Cryption(string& word,const int& key) {
	for (int i = 0; i < (int)word.size(); i++) word[i] = (word[i] > 64 && word[i] < 91) || (word[i] > 96 && word[i] < 123) ? islower(word[i]) ? (word[i] - 19 + key) % 26 + 'a' : (word[i] - 13 + key) % 26 + 'A':word[i];
	return word;
}
