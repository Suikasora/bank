#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include "Account.h"
#include "Menu.h"
using namespace std;

void account::Administrator_ReadUser() {
	int num;
	while (1) {
		system("cls");
		cout << "请输入卡号：";
		cin >> num;

		string filename = to_string(num) + ".txt";
		ifstream readfile;
		readfile.open(filename);
		//账户文件不存在
		if (readfile.fail()) {
			cout << "用户不存在!" << endl;
			getchar();
		}
		else {
			//读入用户信息
			ReadUser(readfile);
			readfile.close();
			cout << "账户信息读入成功！" << endl;
			getchar();
			return;
		}
	}
}
void account::Administrator_PrintDetails(void) {
	system("cls");
	int tempnum = 0;
	cout << "请输入需要查询的帐号：";
	cin >> tempnum;

	system("cls");
	string filename = to_string(tempnum) + "-recording.txt";
	ifstream infile;
	infile.open(filename);
	string tempstr;
	while (!infile.eof()) {//输出文件内容直到读完整个文件
		getline(infile, tempstr);//将文件内容输入到tempstr中
		cout << tempstr << endl;
	}
	infile.close();
	getchar();
	getchar();
}
void account::Administrator_delete(void) {
	system("cls");
	cout << "请输入需要销户的帐号：";
	int tempnum = 0;
	int flag = 0;
	cin >> tempnum;

	string filename1 = to_string(tempnum) + "-recording.txt";//账户明细文件
	string filename2 = to_string(tempnum) + ".txt";//账户信息文件
	const char* cf1 = filename1.c_str();
	const char* cf2 = filename2.c_str();
	//销毁文件计数
	if (!remove(cf1)) {
		flag++;
	}
	if (!remove(cf2)) {
		flag++;
	}
	//当销户文件数不为0,则帐号信息销毁成功
	if (flag > 0) {
		cout << "销户成功！" << endl;
	}
	else {
		cout << "账户不存在，销户失败！" << endl;
	}
	getchar();
}
void account::Administrator_frozen() {
	Administrator_ReadUser();
	system("cls");
	int flag = 0;//二次确认
	cout << "是否确认冻结帐号？ 1-确认，0-取消" << endl;
	cin >> flag;
	if (flag) {
		LoadingAccount.freeze = 1;
		cout << "冻结成功！" << endl;
		LoadingAccount.Save();//保存帐号冻结信息到文件
		getchar();
	}
}
void account::Administrator_unfrozen(void) {
	system("cls");
	cout << "请输入需要解冻的帐号：";
	int tempnum = 0;
	cin >> tempnum;
	string filename = to_string(tempnum) + ".txt";//文件名

	//从文件读入用户信息
	ifstream readfile;
	readfile.open(filename);
	if (readfile.fail()) {
		cout << "\t 该帐号所有账户不存在！ \"" << filename << "\"" << endl;
		getchar();
		return;
	}
	ReadUser(readfile);
	readfile.close();

	//输出用户信息到文件
	ofstream outfile;
	outfile.open(filename);
	if (outfile.fail()) {
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}

	outUser(outfile);
	outfile.close();

	cout << "帐号" << tempnum << "解冻成功!" << endl;
}
int Administrator_Check(void) {
	string CorrectPassword, EnteredPassword;//保存正确的密码和输入的密码
	cout << "Please input Administrator password:" << endl;
	cin >> EnteredPassword;

	//从文件中读取正确的管理员密码
	ifstream in;
	in.open("Bank.txt");
	in >> CorrectPassword;
	in.close();

	if (CorrectPassword == EnteredPassword) {//若密码输入正确
		cout << "管理员大人，欢迎回来" << endl;
		return 1;
	}
	else {//若密码输入错误
		cout << "密码错误!返回选择界面" << endl;
		return 0;
	}
}
void account::Administrator_ReadDetails() {
	LoadingAccount.Administrator_ReadUser();
	system("cls");
	cout << "账号\t" << LoadingAccount.num << endl;
	cout << "姓名\t" << LoadingAccount.name << endl;
	cout << "密码\t" << LoadingAccount.password << endl;
	cout << "手机号\t" << LoadingAccount.phonenum << endl;
	if (LoadingAccount.freeze) {
		cout << "帐号状态\t冻结" << endl;
	}
	else {
		cout << "帐号状态\t未冻结" << endl;
	}
	cout << "余额\t" << LoadingAccount.balance << endl;
	getchar();
}