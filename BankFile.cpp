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
	//���ļ���ʧ�ܣ����ļ�������
	if (Bank.fail()) {
		return 0;//��
	}
	else {
		return 1;//��
	}
}
void CreatBanktxt() {
	system("cls");
	int password;
	ofstream BankFile;
	BankFile.open("Bank.txt");
	cout << "���ڱ�ϵͳ��һ��ʹ�ã�����������Ա�ʺ�" << endl;
	cout << "���������Ա����(6λ����):";
	cin >> password;
	BankFile << password << endl;
	BankFile << "2020000001";//��ʼ�ʺ�
	BankFile.close();
	cout << "�ɹ�!" << endl;
	getchar();
	getchar();
}
