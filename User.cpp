#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include "Account.h"
#include "Menu.h"

using namespace std;

#pragma warning(disable : 4996)

void account::welcome() {
	cout << ">>帐号为[" << num << "]的用户[" << name << "],欢迎您！" << endl;
}
void account::Register() {
	system("cls");
	//两次输入的密码
	int password1;
	int password2;
	//保存信息到LoadingAccount
	cout << "请输入名字:";
	cin >> LoadingAccount.name;
	cout << "请输入身份证号:";
	cin >> LoadingAccount.ID;
	cout << "请输入您的电话号码:";
	cin >> LoadingAccount.phonenum;
Regi_begin:
	system("cls");
	cout << "请输入6位数字密码:";
	cin >> password1;
	//初次判断密码是否合法
	if (cin.fail()) {//是否输入的是数字
		cin.clear();
		cout << "请输入符合格式的密码!" << endl;
		getchar();
		getchar();
		getchar();
		goto Regi_begin;
	}
	if (password1 < 100000 || password1 > 999999) {//是否输入6位数字
		cout << "请输入符合格式的密码!" << endl;
		goto Regi_begin;
	}
	cout << "请再次输入6位数字密码:";
	cin >> password2;

	//判断密码是否合法
	for (int i = 1; i <= 3; i++) {
		if (password1 != password2) {
			system("cls");
			cout << "两次输入密码不同，请重新输入密码!(您还有"<<3-i<<"次机会)" << endl;
			cout << "请输入6位数字密码:";
			cin >> password1;
			cout << "请再次输入6位数字密码:";
			cin >> password2;
		}
		else {
			LoadingAccount.password = password1;
		}
		if (i == 3 && password1 != password2) {
			system("cls");
			cout << "你已经失败了三次，系统自动退出!";
			getchar();
			return;
		}
	}
	//确定帐号并保存到文件
	string TempPassword;
	int TempAccountnum;//创建的新账户的账号
	//打开银行系统文件
	fstream Bank;
	Bank.open("Bank.txt", ios::in | ios::out);
	Bank >> TempPassword >> TempAccountnum;//读取系统文件
	//创建账户文件
	string filename = to_string(TempAccountnum) + ".txt";
	ofstream outfile;
	outfile.open(filename);
	outfile << LoadingAccount.ID << endl;
	outfile << LoadingAccount.name << endl;
	outfile << LoadingAccount.password << endl;
	outfile << LoadingAccount.phonenum << endl;
	outfile << "0" << endl;//是否冻结
	outfile << "0" << endl;//账户余额
	outfile.close();
	//在上述步骤完成后，确定账户帐号
	LoadingAccount.num = TempAccountnum;
	//更新系统文件
	Bank.seekp(ios::beg);//转到文件开头
	TempAccountnum++;//标记的帐号增加
	Bank << TempPassword << endl << TempAccountnum;
	Bank.close();

	return;
}
void account::Login() {
	int num;//帐号
	int password;//密码
	int flag = 0;
	while (1) {
		system("cls");
		cout << "请输入帐号：";
		cin >> num;
		cout << "请输入密码：";
		cin >> password;

		string filename = to_string(num) + ".txt";//保存帐号信息的文件名
		ifstream readfile;
		readfile.open(filename);
		if (readfile.fail()) {
			cout << "用户不存在!" << endl;
			getchar();
			continue;//重新输入帐号密码
		}
		//读入用户信息
		ReadUser(readfile);
		readfile.close();

		//判断帐号是否冻结
		if (LoadingAccount.freeze) {
			cout << "账号已被冻结，登入失败！" << endl;
			return;
		}
		//用户信息已经读入，确认密码是否正确
		if (LoadingAccount.password == password) {
			LoadingAccount.num = num;
			cout << "用户登入成功!" << endl;
			getchar();
			Menu_User();
			return;
		}
		else {
			cout << "密码输入错误!登入失败!" << endl;
			flag++;
			if (flag >= 3) {
				cout << "失败次数过多，将被暂时禁止登入!" << endl;
				break;
			}
			getchar();
			continue;
		}
	}
}

void account::recording(int amount) {
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//保存帐号信息的文件名
	ofstream outfile;
	outfile.open(filename, ios::app);
	//将时间转化为文本写入文件
	time_t now = time(0);
	char* dt = ctime(&now);
	outfile << endl << dt;
	//判断存取款，写入文件
	if (amount > 0) {
		outfile << "存款" << amount << "元" << "\t";
	}
	else {
		amount = -amount;
		outfile << "取款" << amount << "元" << "\t";
	}
	outfile << "余额" << LoadingAccount.balance << "元" << endl;
	outfile.close();
}
void account::transfer_recording(int amount, int num) {
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//保存帐号信息的文件名
	ofstream outfile;
	outfile.open(filename, ios::app);
	//将时间转化为文本写入文件
	time_t now = time(0);
	char* dt = ctime(&now);
	outfile << endl << dt;
	//写入存取款信息
	outfile << "汇款到账户" << num << "合计" << amount << "元" << "\t";
	outfile << "余额" << LoadingAccount.balance << "元" << endl;
	outfile.close();
}
void account::deposit() {
	int flag = 1;//是否继续存款循环的标志
	int confirm;//确认存款
	while (flag) {
		confirm = 0;//初始化
		int amount = 0;//存款额
		system("cls");
		cout << "请输入存款额：" << endl;
		cin >> amount;
		getchar();

		system("cls");
		cout << "您将要存款" << amount << "元" << endl;
		cout << "请再次确认存款（1-确认，0-取消）" << endl;
		cin >> confirm;
		getchar();
		if (confirm) {
			system("cls");
			LoadingAccount.balance += amount;
			cout << "存款成功！" << endl;
			cout << "您的账户余额为" << LoadingAccount.balance << "元" << endl;
			recording(amount);
		}
		cout << "是否继续存款？（1-是，0-否）" << endl;
		cin >> flag;
		getchar();
	}
}
void account::withdraw() {
	int flag = 1;//是否继续取款循环的标志
	int confirm;//确认取款
	while (flag) {
		confirm = 0;
		int amount = 0;
		system("cls");
		cout << "请输入取款额：" << endl;
		cin >> amount;
		getchar();
		system("cls");
		cout << "您将要取款" << amount << "元" << endl;
		cout << "请再次确认取款（1-确认，0-取消）" << endl;
		cin >> confirm;
		getchar();
		if (confirm) {
			system("cls");
			if (LoadingAccount.balance >= amount) {
				LoadingAccount.balance -= amount;
				cout << "取款成功！" << endl;
				cout << "您的账户余额为" << LoadingAccount.balance << "元" << endl;
				recording(-amount);
			}
			else {
				cout << "余额不足，取款失败！" << endl;
			}
		}
		cout << "是否继续取款？（1-是，0-否）" << endl;
		cin >> flag;
		getchar();
	}
}
void account::Save() {
	string filename = to_string(num) + ".txt";//文件名称
	ofstream outfile;
	outfile.open(filename);
	//若文件打开失败
	if (outfile.fail()) {
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}
	//保存信息到文件
	outUser(outfile);
	outfile.close();
}
void account::Details() {
	system("cls");
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//文件名称
	ifstream infile;
	infile.open(filename);
	string tempstr;//在循环中承载文件内容
	while (!infile.eof()) {
		getline(infile, tempstr);//将文件内容输入到tempstr中
		cout << tempstr << endl;
	}
	infile.close();
	getchar();
}
void account::ChangePassword() {
	while (1) {
	Change_begin:
		system("cls");
		int password, password1, password2;
		cout << "请输入原密码(输入0退出)：";
		cin >> password;
		//输入0退出
		if (password == 0) {
			return;
		}
		//检测密码是否正确
		if (password == LoadingAccount.password) {
			//新密码输入
			system("cls");
			cout << "请输入新6位数字密码:";
			cin >> password1;
			//密码格式检测
			if (cin.fail()) {//是否输入的是数字
				cin.clear();
				cout << "请输入符合格式的密码!" << endl;
				getchar();
				getchar();
				getchar();
				goto Change_begin;
			}
			if (password1 < 100000 || password1 > 999999) {//是否输入6位数字
				cout << "请输入符合格式的密码!" << endl;
				goto Change_begin;
			}
			cout << "请再次输入新6位数字密码:";
			cin >> password2;
			//检验密码
			for (int i = 1; i <= 3; i++) {
				if (password1 != password2) {
					system("cls");
					cout << "两次输入密码不同，请重新输入密码" << endl;
					cout << "请输入新6位数字密码:";
					cin >> password1;
					cout << "请再次输入新6位数字密码:";
					cin >> password2;
				}
				else {
					LoadingAccount.password = password1;
					cout << "密码修改成功！\n新密码为:" << password << endl;
					getchar();
					getchar();
					break;
				}
				if (i == 3 && password1 != password2) {
					system("cls");
					cout << "你已经失败了三次，系统自动退出!";
					getchar();
					return;
				}
			}
		}
		else {
			system("cls");
			cout << "密码输入错误，修改密码失败！" << endl;
		}
	}
}
void account::Delete() {
	system("cls");
	int password;//密码
	char ID[24];//身份证号
	//身份验证
	cout << "请输入密码:";
	cin >> password;
	cout << "请输入身份证号:";
	cin >> ID;
	int tempnum = LoadingAccount.num;//保存帐号

	system("cls");
	if (password == LoadingAccount.password && ID == LoadingAccount.ID) {
		string filename1 = to_string(tempnum) + "-recording.txt";
		string filename2 = to_string(tempnum) + ".txt";
		const char* cf1 = filename1.c_str();
		const char* cf2 = filename2.c_str();
		remove(cf1);
		remove(cf2);
		cout << "销户成功！" << endl;
	}
	else {
		cout << "输入有误，销户失败！" << endl;
	}
	getchar();
}
void account::frozen() {
	system("cls");
	int flag = 0;//二次确认
	cout << "是否确认冻结帐号？ 1-确认，2-取消" << endl;
	cin >> flag;
	if (flag) {
		LoadingAccount.freeze = 1;
		cout << "冻结成功！" << endl;
		LoadingAccount.Save();//保存帐号冻结信息到文件
		getchar();
	}
}
void account::transfer() {
	int amount;//转账的数额
	int num;//转账的帐号
	int flag;//继续转账标志
	int flag2;//二次确认标志
	account transfer_account;
	do {
		system("cls");
		cout << "请输入要转账的帐号:";
		cin >> num;
		cout << "请输入要转账的金额:";
		cin >> amount;
		//检测余额
		if (amount >= LoadingAccount.balance) {
			system("cls");
			cout << "账户余额不足，转账失败!" << endl;
			getchar();
			continue;
		}
		ifstream readfile;
		string transfer_account_name = to_string(num) + ".txt";//对方账户文件名
		readfile.open(transfer_account_name);
		//检测对方账户是否存在
		if (readfile.fail()) {
			system("cls");
			cout << "对方账户不存在，转账失败!" << endl;
			getchar();
			continue;
		}
		//对方账户信息读取
		transfer_account.ReadUser(readfile);
		//检测对方账户情况
		if (transfer_account.freeze) {
			system("cls");
			cout << "对方账户已被冻结，转账失败!" << endl;
			getchar();
			continue;
		}
		//二次确认
		cout << "是否确认转账" << amount << "元？ 1-确认 2-取消" << endl;
		cin >> flag2;
		if (!flag2) {
			continue;
		}
		transfer_account.balance += amount;//对方账户余额增加
		LoadingAccount.balance -= amount;//己方账户余额减少
		transfer_account.Save();//对方账户信息保存
		readfile.close();
		system("cls");
		//将汇款记录保存到账户明细中
		transfer_recording(amount, num);
		cout << "转账成功！" << endl;
		cout << "是否继续转账? 1-是 0-否" << endl;
		cin >> flag;
	} while (flag);
}