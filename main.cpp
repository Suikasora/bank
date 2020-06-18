#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>


using namespace std;

void Menu_User();
void Menu_Choose();
void Menu_Administrator();
class account{
	private:
		int num;
		char ID[24];
		char name[20];
		int password;
		char phonenum[14];
		int freeze = 0;
	public:
		double balance;
		void CreatAccount();
		void ReadUser();
		void recording(int amount);
		void deposit();
		void withdraw();
		void Details();
		void ChangePassword();
		void frozen();
		void Save();
		void Delete();
}person;


void account::CreatAccount(){
	int password1;
	int password2;
	cout<<"请输入名字:";
	cin>>person.name;
	cout<<"请输入身份证号:";
	cin>>person.ID;
	cout<<"请输入6位数字密码:";
	cin >> password1;
	cout<<"请再次输入6位数字密码:";
	cin >> password2;

	for(int i = 1;i <= 3;i++){
		if( password1 != password2 ){
			system("clear");
			cout << "两次输入密码不同，请重新输入密码"<<endl;	
			cout<<"请输入6位数字密码:";
			cin >> password1;
			cout<<"请再次输入6位数字密码:";
			cin >> password2;
		}
		else{
			person.password = password1;
		}
		if( i==3 && password1 != password2 ){
			system("clear");
			cout << "你已经失败了三次，系统自动退出!";
			getchar();
			return ;
		}
	}
	cout << "请输入您的电话号码:";
	cin >> person.phonenum;
	//confirm account and save
		string TempPassword;
	int TempAccountnum;
	//open bank.txt
	fstream Bank;
	Bank.open("Bank.txt",ios::in|ios::out);
	Bank >> TempPassword >> TempAccountnum;

	string filename = to_string(TempAccountnum)+ ".txt";
	ofstream outfile;
	outfile.open(filename);
	if( outfile.fail() ){
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}
	outfile << person.ID << endl;
	outfile << person.name << endl;
	outfile << person.password <<endl;
	outfile << person.phonenum << endl;
	outfile << "0" <<endl;
	outfile << "0" <<endl;
	outfile.close();

	Bank.seekp(ios::beg);
	TempAccountnum++;//The num of account ++
	Bank << TempPassword << endl << TempAccountnum;
	Bank.close();

	person.num = TempAccountnum;

	return ;
}
void account::ReadUser(){
	int num;
	int password;
	int flag = 0;
	while( 1 ){
		system("clear");
		cout << "请输入卡号：";
		cin >> num;
		cout << "请输入密码：";
		cin >> password;

		string filename = to_string(num) + ".txt";
		ifstream readfile;
		readfile.open(filename);
		if( readfile.fail() ){
			cout << "用户不存在!" << endl;
			getchar();
			getchar();
			continue;
		}
		else{
			//读入用户信息
			readfile >> person.ID >> person.name >> person.password >> person.phonenum;
			readfile >> person.freeze;
			readfile >> person.balance;
			readfile.close();
			//判断帐号是否冻结
			if( person.freeze ){
				cout << "账号已被冻结，登入失败！" << endl;
				return ;
			}
			//用户信息已经读入，确认密码是否正确
			if( person.password == password ){
				person.num = num;
				cout << "用户登入成功!" << endl;
				getchar();
				getchar();
				return ;
			}
			else{
				cout << "密码输入错误!登入失败!" << endl;
				flag++;
				if( flag >=3 ){
					cout << "失败次数过多，将被暂时禁止登入!"<<endl;
					break;
				}
				getchar();
				getchar();
				continue;
			}
					}
	}
}
void account::recording(int amount){
	string filename = to_string(person.num) + "-recording.txt";
	ofstream outfile;
	outfile.open(filename,ios::app);
	//time
	time_t now = time(0);
	char* dt = ctime(&now);
	outfile << endl << dt ;
	if( amount >0 ){
		outfile << "存款" << amount << "元" << "\t";
	}
	else{
		amount = -amount;
		outfile << "取款" << amount << "元" << "\t";
	}
	outfile << "余额" << person.balance << "元" << endl;
	outfile.close();
	return ;
}
void account::deposit(){
	int flag = 1;
	int confirm ;
	while( flag ){
		confirm = 0;
		int amount = 0;
		system("clear");
		cout << "请输入存款额："<<endl;
		cin >> amount;
		getchar();
		system("clear");
		cout << "您将要存款" << amount << "元" << endl;
		cout << "请再次确认存款（1-确认，0-取消）"<<endl;
		cin >> confirm;
		getchar();
		if( confirm ){
			system("clear");
			person.balance += amount;
			cout << "存款成功！" << endl;
			cout << "您的账户余额为" << person.balance << "元" << endl;
			recording(amount);
		}
		cout << "是否继续存款？（1-是，0-否）"<<endl;
		cin >> flag;
		getchar();
	}
	}
void account::withdraw(){
	int flag = 1;
	int confirm ;
	while( flag ){
		confirm = 0;
		int amount = 0;
		system("clear");
		cout << "请输入取款额："<<endl;
		cin >> amount;
		getchar();
		system("clear");
		cout << "您将要取款" << amount << "元" << endl;
		cout << "请再次确认取款（1-确认，0-取消）"<<endl;
		cin >> confirm;
		getchar();
		if( confirm ){
			system("clear");
			if( person.balance >= amount ){
				person.balance -= amount;
				cout << "取款成功！" << endl;
				cout << "您的账户余额为" << person.balance << "元" << endl;
				recording(-amount);
			}
			else{
				cout << "余额不足，取款失败！"<<endl;
			}
		}
		cout << "是否继续取款？（1-是，0-否）"<<endl;
		cin >> flag;
		getchar();
	}
}
void account::Save(){
	string filename = to_string(person.num) + ".txt";
	ofstream outfile;
	outfile.open(filename);
	if( outfile.fail() ){
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}
	outfile << person.ID << endl;
	outfile << person.name << endl;
	outfile << person.password <<endl;
	outfile << person.phonenum << endl;
	outfile << person.freeze << endl;
	outfile << person.balance <<endl;
	outfile.close();
}
void account::Details(){
	system("clear");
	string filename = to_string(person.num) + "-recording.txt";
	ifstream infile;
	infile.open(filename);
	string tempstr;
	while( !infile.eof() ){
		getline(infile,tempstr);//将文件内容输入到tempstr中
		cout << tempstr << endl;
	}
	infile.close();
	getchar();
	getchar();
}
void account::ChangePassword(){
	system("clear");
	int password,password1,password2;
	cout << "请输入原密码：";
	cin >> password;
	if( password == person.password ){
		system("clear");
		cout<<"请输入新6位数字密码:";
		cin >> password1;
		cout<<"请再次输入新6位数字密码:";
		cin >> password2;

		for(int i = 1;i <= 3;i++){
			if( password1 != password2 ){
				system("clear");
				cout << "两次输入密码不同，请重新输入密码"<<endl;
				cout<<"请输入新6位数字密码:";
				cin >> password1;
				cout<<"请再次输入新6位数字密码:";
				cin >> password2;
			}
			else{
				person.password = password1;
				cout << "密码修改成功！\n新密码为:" << password << endl;
			}
			if( i==3 && password1 != password2 ){
				system("clear");
				cout << "你已经失败了三次，系统自动退出!";
				getchar();
				return ;
			}
		}
	}
	else{
		system("clear");
		cout << "密码输入错误，修改密码失败！"<<endl;
	}
	getchar();
	getchar();
}
void account::Delete(){
	system("clear");
	int password;
	char ID[24];
	cout << "请输入密码:";
	cin >> password;
	cout << "请输入身份证号:";
	cin >> ID;
	int tempnum = person.num;
	
	system("clear");
	if( password == person.password && ID == person.ID ){
		string filename1 = to_string(tempnum) + "-recording.txt";
		string filename2 = to_string(tempnum) + ".txt";
		const char * cf1 = filename1.c_str();
		const char * cf2 = filename2.c_str();
		remove(cf1);
		remove(cf2);
		cout << "销户成功！" << endl;
	}
	else{
		cout << "输入有误，销户失败！"<<endl;
	}
	getchar();
	getchar();
}
void account::frozen(){
	system("clear");
	int flag = 0;
	cout << "是否确认冻结帐号？ 1-确认，2-取消" << endl;
	cin >> flag;
	if( flag ){
		person.freeze = 1;
		cout << 	"冻结成功！"<<endl;
		person.Save();
		Menu_Choose();
	}
}
//============================================================================
void Administrator_details(void){
	system("clear");
	cout << "请输入需要查询的帐号：";
	int tempnum = 0;
	cin >> tempnum;
	
	system("clear");
	string filename = to_string(tempnum) + "-recording.txt";
	ifstream infile;
	infile.open(filename);
	string tempstr;
	while( !infile.eof() ){
		getline(infile,tempstr);//将文件内容输入到tempstr中
		cout << tempstr << endl;
	}
	infile.close();
	getchar();
	getchar();
}
void Administrator_delete(void){
	system("clear");
	cout << "请输入需要销户的帐号：";
	int tempnum = 0;
	int flag = 0;
	cin >> tempnum;
	
	string filename1 = to_string(tempnum) + "-recording.txt";
	string filename2 = to_string(tempnum) + ".txt";
	const char * cf1 = filename1.c_str();
	const char * cf2 = filename2.c_str();
	if( !remove(cf1) ){
		flag ++;
	}
	if( !remove(cf2) ){
		flag ++;
	}	
	if( flag >0 ){
		cout << "销户成功！" << endl;
	}
	else{
		cout << "账户不存在，销户失败！" << endl;
	}
	getchar();
}
void Administrator_unfrozen(void){
	system("clear");
	cout << "请输入需要解冻的帐号：";
	int tempnum = 0;
	cin >> tempnum;

		char ID[24];
		char name[20];
		int password;
		char phonenum[14];
		int freeze = 0;
		double balance;

	//读入用户信息
	string filename = to_string(tempnum) + ".txt";	
	ifstream readfile;
	readfile.open(filename);
	if( readfile.fail() ){
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
		getchar();
		return;
	}
	readfile >> ID >> name >> password >> phonenum;
	readfile >> freeze;
	readfile >> balance;
	readfile.close();

	ofstream outfile;
	outfile.open(filename);
	if( outfile.fail() ){
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}
	outfile << ID << endl;
	outfile << password <<endl;
	outfile << phonenum << endl;
	outfile << freeze << endl;
	outfile << balance <<endl;
	outfile.close();

	cout << "帐号" << tempnum << "解冻成功!" << endl;

}
int AdministratorCheck(void){
	string CorrectPassword,EnteredPassword;
	cout << "Please input Administrator password:" <<endl;
	cin >> EnteredPassword;

	ifstream in;
	in.open("Bank.txt");
	in >> CorrectPassword;
	in.close();

	if( CorrectPassword == EnteredPassword ){
		cout << "管理员大人，欢迎回来" << endl;
		return 1;
	}
	else{
		cout << "密码错误!返回选择界面" << endl;
		return 0;
	}

}

void Menu_Administrator(void)
{
	int choice;
	do{
		system("clear");
		cout << "============================================================"<<endl;
		cout << "1-查看账户流水 2-销户\n3-解冻帐号\n0-退出系统"<<endl;
		cout << "============================================================"<<endl;

		cin >> choice;
		switch(choice){
			case 1:{
							 Administrator_details();
							 break;
						 }
			case 2:{
							Administrator_delete();
							break;
						 }
			case 3:{
							 Administrator_unfrozen();
							 break;
						 }
			case 0:
				break;
		}
	}while(choice);
	return ;
}
void Menu_User(void){
	int choice;

	do{
		system("clear");
		cout << "============================================================"<<endl;
		cout << "1-存款 2-取款 \n3-账户明细查询 4-密码修改\n5-余额查询 6-销户\n7-冻结账户\n0-注销登录"<<endl;
		cout << "============================================================"<<endl;
		cin >> choice;
		switch(choice){
			case 1:{
							 person.deposit();
							 break;
						 }
			case 2:{
							 person.withdraw();
							 break;
						 }
			case 3:{
							 person.Details();
							 break;
						 }
			case 4:{
							 person.ChangePassword();
							 break;
						 }
			case 5:{
							 system("clear");
							 cout << "您的账户余额为" << person.balance << "元" << endl;
							 getchar();
							 return;
						 }
			case 6:{
							 person.Delete();
							 break;
						 }
			case 7:{
							 
						 }
			case 0:{
							 person.Save();
							 break;
						 }
		}
	}while(choice);
	return ;
}
void Menu_Choose(void){
		int choice;
	do{
		system("clear");
		cout << "============================================================"<<endl;
		cout << "=================欢迎来到银行账户管理系统！=================";
		cout << "============================================================"<<endl;
		cout << "1-以普通用户身份登入"<<endl;
		cout << "2-以管理员身份登入"<<endl;
		cout << "3-开户" <<endl;
		cout << "0-退出系统"<<endl;
		cout << "============================================================"<<endl;
		cin >> choice;
		switch(choice){
			case 1:{
				person.ReadUser();
				Menu_User();
				break;
						 }
			case 2:{
				if( AdministratorCheck() ){
					Menu_Administrator();
				}
				break;
						 }
			case 3:{
				person.CreatAccount();
				Menu_User();
				break;
						 }
			case 0:
				break;
		}
	}while(choice);
}

int main(void)
{
	Menu_Choose();
	return 0;
}
