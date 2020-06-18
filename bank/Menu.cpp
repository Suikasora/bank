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
		cout << "1-查看账户流水 2-删除账户\n3-解冻帐号 4-输出帐号个人信息\n5- 冻结帐号 0-退出系统" << endl;
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
		cout << "1-存款 2-取款 \n3-账户明细查询 4-密码修改\n5-余额查询 6-转账\n7-冻结账户 8-销户\n0-注销登录" << endl;
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
			cout << "您的账户余额为" << LoadingAccount.balance << "元" << endl;
			getchar();
			break;
		}
		case 6: {
			LoadingAccount.transfer();
			break;
		}
		case 7: {
			LoadingAccount.frozen();
			return;//返回初始界面
		}
		case 8: {
			LoadingAccount.Delete();
			return;//返回初始界面
		}
		case 0: {
			//保存更新的帐号信息到文件
			LoadingAccount.Save();
			break;
		}
		}
	} while (choice);//choice==0结束
	return;
}
void Menu_Choose(void) {
	int choice;
	do {
		system("cls");
		cout << "============================================================" << endl;
		cout << "=================欢迎来到银行账户管理系统！=================" << endl;
		cout << "============================================================" << endl;
		cout << "1-以普通用户身份登入" << endl;
		cout << "2-以管理员身份登入" << endl;
		cout << "3-开户" << endl;
		cout << "0-退出系统" << endl;
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