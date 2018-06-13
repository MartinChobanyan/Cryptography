#include<string>
#include<iostream>
#include<cctype>

using namespace std;

string Czar_Cryption(string&,const int&);

int main() {
	string text; int key;
	cout << "This is realisation of the Czar cryption algorithm!\nCryption -> + key\nEncryption -> - key\n";
	cout << "Input the text: ";
	cin >> text;
	cout << "Input the key: ";
	cin >> key;
	cout << Czar_Cryption(text, key) << endl;
	system("pause");
	return 0;
}

string Czar_Cryption(string& text,const int& key) {
	for (int i = 0; i < (int)text.size(); i++) text[i] = islower(text[i]) ? (text[i] - 19 + key) % 26 + 'a':(text[i] - 13 + key) % 26 + 'A';
	return text;
}