#include <iostream>
#include "C:\Users\user\Desktop\lab2\lab2\Algoritm.h"

using namespace std;

int main()
{
	system("color F0");
	string input = "string for test";
	Algoritm encryptor;
	string code = encryptor.encodeReview(input);
	encryptor.printCodes();
	encryptor.decodeReview(code);
}