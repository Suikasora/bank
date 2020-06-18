#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include "Account.h"
#include "Menu.h"

using namespace std;

void Menu_Administrator(void) {
	int choice;
	do {
		system("cls");
		cout << "============================================================" << endl;
		cout << "1-�鿴�˻���ˮ 2-ɾ���˻�\n3-�ⶳ�ʺ� 4-����ʺŸ�����Ϣ\n5- �����ʺ� 0-�˳�ϵͳ" << endl;
		cout << "============================================================" << endl;

		cin >> choice;
		switch (choice) {
		case 1: {
			LoadingAccount.Administrator_PrintDetails();
			break;
		}
		case 2: {
			LoadingAccount.Administrator_delete();
			break;
		}
		case 3: {
			LoadingAccount.Administrator_unfrozen();
			break;
		}
		case 4: {
			LoadingAccount.Administrator_ReadDetails();
			break;
		}
		case 5: {
			LoadingAccount.Administrator_frozen();
			break;
		}
		case 0:
			break;
		}
	} while (choice);
	return;
}
void Menu_User() {
	int choice;
	do {
		system("cls");
		cout << "============================================================" << endl;
		LoadingAccount.welcome();
		cout << "1-��� 2-ȡ�� \n3-�˻���ϸ��ѯ 4-�����޸�\n5-����ѯ 6-ת��\n7-�����˻� 8-����\n0-ע����¼" << endl;
		cout << "============================================================" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			LoadingAccount.deposit();
			break;
		}
		case 2: {
			LoadingAccount.withdraw();
			break;
		}
		case 3: {
			LoadingAccount.Details();
			break;
		}
		case 4: {
			LoadingAccount.ChangePassword();
			break;
		}
		case 5: {
			system("cls");
			cout << "�����˻����Ϊ" << LoadingAccount.balance << "Ԫ" << endl;
			getchar();
			break;
		}
		case 6: {
			LoadingAccount.transfer();
			break;
		}
		case 7: {
			LoadingAccount.frozen();
			return;//���س�ʼ����
		}
		case 8: {
			LoadingAccount.Delete();
			return;//���س�ʼ����
		}
		case 0: {
			//������µ��ʺ���Ϣ���ļ�
			LoadingAccount.Save();
			break;
		}
		}
	} while (choice);//choice==0����
	return;
}
void Menu_Choose(void) {
	int choice;
	do {
		system("cls");
		cout << "============================================================" << endl;
		cout << "=================��ӭ���������˻�����ϵͳ��=================" << endl;
		cout << "============================================================" << endl;
		cout << "1-����ͨ�û���ݵ���" << endl;
		cout << "2-�Թ���Ա��ݵ���" << endl;
		cout << "3-����" << endl;
		cout << "0-�˳�ϵͳ" << endl;
		cout << "============================================================" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			LoadingAccount.Login();
			break;
		}
		case 2: {
			if (Administrator_Check()) {
				Menu_Administrator();
			}
			break;
		}
		case 3: {
			LoadingAccount.Register();
			Menu_User();
			break;
		}
		case 0:
			break;
		}
	} while (choice);
}