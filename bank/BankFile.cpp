#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include "Account.h"
#include "Menu.h"

using namespace std;

int CheckBanktxtSuccess() {
	fstream Bank;
	Bank.open("Bank.txt");
	//若文件打开失败，即文件不存在
	if (Bank.fail()) {
		return 0;//假
	}
	else {
		return 1;//真
	}
}
void CreatBanktxt() {
	system("cls");
	int password;
	ofstream BankFile;
	BankFile.open("Bank.txt");
	cout << "由于本系统第一次使用，将创建管理员帐号" << endl;
	cout << "请输入管理员密码(6位数字):";
	cin >> password;
	BankFile << password << endl;
	BankFile << "2020000001";//初始帐号
	BankFile.close();
	cout << "成功!" << endl;
	getchar();
	getchar();
}
