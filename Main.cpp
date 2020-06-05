#include <iostream>
#include "C:\Users\user\Desktop\lab2\lab2\Algoritm.h"

using namespace std;

int main()
{
	system("color F0");
	string input = "string for test";
	Alg_Shanon_Fano encryptor;
	string code = encryptor.coding_Info(input);
	encryptor.Input_Code();
	encryptor.decoding_info(code);
}