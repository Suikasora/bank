#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
using namespace std;

class account {
private:
	int num;//帐号
	char ID[24];//身份证号
	char name[20];//名字
	int password;//密码
	char phonenum[14];//手机号码
	int freeze = 0;//冻结判定
public:
	double balance;//余额
	inline void ReadUser(ifstream& readfile);//从文件读取账号及其信息
	inline void outUser(ofstream& outfile);//输出帐号及信息到文件
	void welcome();
	void Register();//开户
	void Login();//帐号登录
	void deposit();//存款
	void withdraw();//取款
	void recording(int amount);//保存账户明细
	void transfer_recording(int amount, int num);
	void Details();//打印账户明细
	void ChangePassword();//更改密码
	void frozen();//冻结账号
	void Save();//保存信息到文件
	void Delete();//删除帐号及其信息
	void transfer();//转账
//管理员功能函数
	void Administrator_PrintDetails();//根据帐号查询账户明细
	void Administrator_delete();//删除帐号及其信息
	void Administrator_frozen();
	void Administrator_unfrozen();//解冻账号
	void Administrator_ReadUser();//读取账户信息
	void Administrator_ReadDetails();//输出当前账户个人信息
	//int ReadUser(string num, account *tempaccount);
	//
};
extern account LoadingAccount;//当前帐号


void account::ReadUser(ifstream& readfile) {
	int encrypt = (num * 6) - 5;
	readfile >> encrypt;
	readfile >> ID;
	readfile >> name;
	readfile >> password;
	readfile >> phonenum;
	readfile >> freeze;
	readfile >> balance;
}
void account::outUser(ofstream& outfile) {
	outfile << num << endl;
	num = (num + 5) / 6;
	outfile << ID << endl;
	outfile << name << endl;
	outfile << password << endl;
	outfile << phonenum << endl;
	outfile << freeze << endl;
	outfile << balance << endl;
}