#include <string>
#include <bitset>
#include <iostream>
#include <vector>

#include <fstream>
#include <Windows.h>

#include "CImg.h"
using namespace cimg_library;
using namespace std;
string ExePath() {
	TCHAR NPath[MAX_PATH];
	GetModuleFileName(NULL, NPath, MAX_PATH);
	//string::size_type pos = string(buffer).find_last_of("\\/");
	//return string(buffer).substr(0, pos);
	wstring test(&NPath[0]); //convert to wstring
	string test2(test.begin(), test.end()); //and convert to string.
	return test2;
}
bitset<8> add(char a, bitset<8> tmp) {

	int S_tmp = a - '0';
	if (S_tmp == 1) {
		if (tmp[6] == 1)
			tmp[6] = 0;
		else
			tmp[6] = 1;
	}
	return tmp;
}

float cal_co(string a, string b) {
	float mean_A, mean_B;
	float tmp = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		tmp += (int)a[i];
	}
	mean_A = float(tmp / a.size());
	tmp = 0;
	for (size_t i = 0; i < b.size(); i++)
	{
		tmp += (int)b[i];
	}
	mean_B = float(tmp / b.size());
	float corr = 0.0;
	tmp = 0.0;
	float tmp_downer_L = 0.0, tmp_downer_R = 0.0;
	for (size_t i = 0; i < a.size(); i++)
	{
		tmp += ((float)a[i] - mean_A)*((float)b[i] - mean_B);
		tmp_downer_L += pow(((float)a[i] - mean_A), 2);
		tmp_downer_R += pow(((float)b[i] - mean_B), 2);
	}
	corr = tmp / (pow(tmp_downer_L, 0.5)*pow(tmp_downer_R, 0.5));
	return corr;
}

unsigned int substract(bitset<8> water, bitset<8> ori) {
	bitset<8> saver;
	//saver = ori & ~water;
	//unsigned int tmp = (int)saver[6];
	return water[6]-ori[6];
}

int main() {
	cout << "Please enter the name of image:" << endl;
	string f = "ABC";
	cin >> f;
	cout << "Please enter the plaintext:" << endl;
	string myString = "HELLOWORLD";
	cin >> myString;
	myString += '[';
	vector<bitset<6>> sequence;
	bitset<6> tmp_A;
	string s_sequence;
	for (size_t i = 0; i < myString.size(); ++i)
	{
		//cout << bitset<6>(myString.c_str()[i]) << endl;
		tmp_A = myString.c_str()[i];
		sequence.push_back(tmp_A);
		s_sequence += tmp_A.to_string();
	}
	//switch to string

	

	//got sequence
	string path = ExePath();
	cout << "Current PATH : " << path  << endl;

	
	//path+
	
	//baboon = ReadBMP("baboon.bmp");
	CImg<unsigned int> src(f.c_str());
	int width = src.width();
	int height = src.height();
	unsigned short int R, G, B;
	//for (int r = 0; r < height; r++)
	//	for (int c = 0; c < width; c++){
	//		R = (int)src(c, r, 0, 0);
	//		G = (int)src(c, r, 0, 1);
	//		B = (int)src(c, r, 0, 2);
	//	}

	//i will set it on 300,300 -> 400,400
	bitset<8> tmp,new_tmp;
	int runner = 0;
	int S_tmp;

	int TESTA, TESTB;
	for (size_t w = 300; w < 400; w++){
		for (size_t h = 200; h < 300; h++)
		{
			TESTA = src(w, h, 0, 0);
			//R
			tmp = (int)src(w, h, 0, 0);
			new_tmp = add(s_sequence[runner++], tmp);
			src(w, h, 0, 0) = (int)(new_tmp.to_ulong());
			if (runner >= s_sequence.size())
				break;
			TESTB = src(w, h, 0, 0);
			//G
			tmp = (int)src(w, h, 0, 1);
			new_tmp = add(s_sequence[runner++], tmp);
			src(w, h, 0, 1) = (int)(new_tmp.to_ulong());
			if (runner >= s_sequence.size())
				break;
			//B
			tmp = (int)src(w, h, 0, 2);
			new_tmp = add(s_sequence[runner++], tmp);
			src(w, h, 0, 2) = (int)(new_tmp.to_ulong());
			if (runner >= s_sequence.size())
				break;
			
			
		}
		if (runner >= s_sequence.size())
			break;
	}

	//cout << src(300, 202, 0, 0);

	src.save("tmp.bmp");

	//decoding
	CImg<unsigned int> ori(f.c_str());
	CImg<unsigned int> encoded("tmp.bmp");
	width = encoded.width();
	height = encoded.height();
	int ori_width = ori.width();
	int ori_height = ori.height();
	bitset<8> ori_bit, encode_bit;
	bitset<6> char_bit;
	int mod = 0,mod2=0,mod3=0;
	runner = 5;
	char CHAR;
	string result;
	//Correlation
	string ori_se, water_se;
	for (size_t w = 300; w < 400; w++) {
		for (size_t h = 200; h < 300; h++)
		{
			//R
			encode_bit = (int)encoded(w, h, 0, 0);
			ori_bit = (int)ori(w, h, 0, 0);
			mod = substract(encode_bit, ori_bit);
			char_bit.set(runner--, mod);
			//
			ori_se += (char)ori_bit[6];
			water_se += (char)encode_bit[6];
			//G
			encode_bit = (int)encoded(w, h, 0, 1);
			ori_bit = (int)ori(w, h, 0, 1);
			mod = substract(encode_bit, ori_bit);
			char_bit.set(runner--, mod);
			//
			ori_se += (char)ori_bit[6];
			water_se += (char)encode_bit[6];
			//B
			encode_bit = (int)encoded(w, h, 0, 2);
			ori_bit = (int)ori(w, h, 0, 2);
			mod = substract(encode_bit, ori_bit);
			char_bit.set(runner--, mod);
			//
			ori_se += (char)ori_bit[6];
			water_se += (char)encode_bit[6];
			///
			if (runner == -1) {
				runner = 5;
				int abc = (int)(char_bit.to_ulong());
				CHAR = (int)char_bit.to_ulong() + '@';
				char_bit.reset();
				if (CHAR == '[')
					break;
				result += CHAR;
			}
		}
		if (CHAR == '[')
			break;
	}
	//water_se
	cout << "The coefficient of Between watered Image and original Image : " << cal_co(ori_se, water_se) << endl;
	cout << "Recovered PlainText : " << result << endl;
	cout << "Done" << endl;
	cout << "THIS PROGRAM IS WRITTEN By REVO(DB325554)" << endl;
	return 0;
}