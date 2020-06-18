#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(void)
{
		//confirm account and save
		string TempPassword;
	int TempAccountnum;
	//open bank.txt
	fstream Bank;
	Bank.open("Bank.txt",ios::in|ios::out);
	Bank >> TempPassword >> TempAccountnum;

	Bank.seekp(ios::beg);
	//close bank.txt
	TempAccountnum++;//The num of account ++
	Bank << TempPassword << endl << TempAccountnum;
	Bank.close();
	return 0;
}
