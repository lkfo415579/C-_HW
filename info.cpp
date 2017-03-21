//#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

vector<int> Key(string p) {
	srand(time(NULL));
	vector<int> keys;
	for (size_t i = 0; i < p.size(); i++)
		keys.push_back(rand() % 100 + 1);
	return keys;
}
string V2S(vector<int> keys) {
	string skey = "";
	for (size_t i = 0; i < keys.size(); i++) 
		skey += to_string(keys[i])+ " ";
	return skey;
}
string vernam(vector<int> keys,string p) {
	int char_ID,sum;
	string output = "";
	for (size_t i = 0; i < p.size(); i++)
	{
		//A starts from 65, ends with 122 z,between has 57 letters, case sensitive
		char_ID = int(p[i]) - 65;
		sum = (keys[i] + char_ID) % 57;
		output += static_cast<char>(sum+65);
	}
	return output;
}
string V_vernam(vector<int> keys, string c) {
	int char_ID, output_id,tmp;
	string output = "";
	for (size_t i = 0; i < c.size(); i++)
	{
		char_ID = int(c[i]) - 65;
		for (size_t i2 = 0; i2 < keys[i] + 57; i2++)
		{
			tmp = keys[i] + i2;
			if (tmp % 57 == char_ID) {
				//found x,(x+key) % 57
				output_id = i2;
				break;
			}
		}
		output += static_cast<char>(output_id + 65);
		
	}
	return output;
}
void encryption() {
	cout << "Please enter the plaintext:" << endl;
	string plaintext;
	cin >> plaintext;
	cout << "Please select a key(R is random / U is user input) :" << endl;
	vector<int> keys;
	char option;
	cin >> option;
	if (option == 'R')
		keys = Key(plaintext);
	else {
		cout << "Please enter the Key:" << endl;
		string tmp;
		for (size_t i = 0; i < plaintext.size(); i++)
		{
			cin >> tmp;
			keys.push_back(atoi(tmp.c_str()));
		}
	}
	cout << "Plaintext:" << plaintext << endl;
	cout << "Key:" << V2S(keys) << endl;
	string cipher_text = vernam(keys, plaintext);
	cout << "Cipher text :" << cipher_text << endl;

}
void decryption() {
	cout << "Please enter the Ciphertext:" << endl;
	string cipher_text;
	cin >> cipher_text;
	cout << "Please select a key(R is random / U is user input) :" << endl;
	
	vector<int> keys;
	char option;
	cin >> option;
	if (option == 'R')
		keys = Key(cipher_text);
	else {
		cout << "Please enter the Key:" << endl;
		string tmp;
		for (size_t i = 0; i < cipher_text.size(); i++)
		{
			cin >> tmp;
			keys.push_back(atoi(tmp.c_str()));
		}
	}
	cout << "Cipher text :" << cipher_text << endl;
	cout << "Key:" << V2S(keys) << endl;
	string plaintext = V_vernam(keys, cipher_text);
	cout << "Plaintext:" << plaintext << endl;
	

}
int main()
{
	cout << "written by REVO" << endl <<"Welcome to My Vernam Cipher!This program is case sensitive!!!" << endl;
	char input;
	int tmp = 1;
	while (tmp) {
		cout << "Please select the mode (E is encryption/D isdecryption/X is exit):" << endl;
		cin >> input;
		switch (input)
		{
		case('E'):
			encryption();
			break;
		case('D'):
			decryption();
			break;
		case('X'):
			tmp = 0;
			break;
		default:
			break;
		}
	}
	return 0;
}
