#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>


using namespace std;

void Menu_Choose();//系统的初始选择界面
void Menu_User();//普通用户菜单
void Menu_Administrator();//管理员用户菜单

int CheckBanktxtSuccess();//检查银行系统文件
void CreatBanktxt();//创建银行的系统文件

int Administrator_Check();//检查管理员密码

class account{
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
		void transfer_recording(int amount,int num);
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
}LoadingAccount;//当前帐号



//============================================================================cpp_BankFile
int CheckBanktxtSuccess(){
	fstream Bank;
	Bank.open("Bank.txt");
	//若文件打开失败，即文件不存在
	if( Bank.fail() ){
		return 0;//假
	}
	else{
		return 1;//真
	}
}
void CreatBanktxt(){
	system("");
	int password;
	ofstream BankFile;
	BankFile.open("Bank.txt");
	cout << "由于本系统第一次使用，将创建管理员帐号"<<endl;
	cout << "请输入管理员密码(6位数字):" ;
	cin >> password;
	BankFile << password << endl;
	BankFile << "2020000001";//初始帐号
	BankFile.close();
	cout << "成功!" << endl;
	getchar();
	getchar();
}

//============================================================================cpp_Class
void account::ReadUser( ifstream& readfile){
	readfile >> num;
	readfile >> ID;
	readfile >> name;
	readfile >> password;
	readfile >> phonenum;
	readfile >> freeze;
	readfile >> balance;
}
void account::outUser(ofstream& outfile){
	outfile << num << endl;
	outfile << ID << endl;
	outfile << name << endl;
	outfile << password <<endl;
	outfile << phonenum << endl;
	outfile << freeze << endl;
	outfile << balance <<endl;
}
void account::welcome(){
	cout << ">>帐号为[" << num << "]的用户" << name << ",欢迎您！" <<endl;
}
void account::Register(){
Regi_begin:
	system("");
	//两次输入的密码
	int password1;
	int password2;
	//保存信息到LoadingAccount
	cout<<"请输入名字:";
	cin>>LoadingAccount.name;
	cout<<"请输入身份证号:";
	cin>>LoadingAccount.ID;
	cout << "请输入您的电话号码:";
	cin >> LoadingAccount.phonenum;
	cout<<"请输入6位数字密码:";
	cin >> password1;
	//初次判断密码是否合法
	if( cin.fail() ){//是否输入的是数字
		cin.clear();
		cout << "请输入符合格式的密码!" << endl;
		getchar();
		getchar();
		getchar();
		goto Regi_begin;
	}
	if( password1 < 100000 || password1 > 999999 ){//是否输入6位数字
		cout << "请输入符合格式的密码!" << endl;
		goto Regi_begin;
	}
	cout<<"请再次输入6位数字密码:";
	cin >> password2;

	//判断密码是否合法
	for(int i = 1;i <= 3;i++){
		if( password1 != password2 ){
			system("");
			cout << "两次输入密码不同，请重新输入密码"<<endl;	
			cout<<"请输入6位数字密码:";
			cin >> password1;
			cout<<"请再次输入6位数字密码:";
			cin >> password2;
		}
		else{
			LoadingAccount.password = password1;
		}
		if( i==3 && password1 != password2 ){
			system("");
			cout << "你已经失败了三次，系统自动退出!";
			getchar();
			return ;
		}
	}
	//确定帐号并保存到文件
	string TempPassword;
	int TempAccountnum;//创建的新账户的账号
	//打开银行系统文件
	fstream Bank;
	Bank.open("Bank.txt",ios::in|ios::out);
	Bank >> TempPassword >> TempAccountnum;//读取系统文件
	//创建账户文件
	string filename = to_string(TempAccountnum)+ ".txt";
	ofstream outfile;
	outfile.open(filename);
	outfile << LoadingAccount.ID << endl;
	outfile << LoadingAccount.name << endl;
	outfile << LoadingAccount.password <<endl;
	outfile << LoadingAccount.phonenum << endl;
	outfile << "0" <<endl;//是否冻结
	outfile << "0" <<endl;//账户余额
	outfile.close();
	//在上述步骤完成后，确定账户帐号
	LoadingAccount.num = TempAccountnum;
	//更新系统文件
	Bank.seekp(ios::beg);//转到文件开头
	TempAccountnum++;//标记的帐号增加
	Bank << TempPassword << endl << TempAccountnum;
	Bank.close();

	return ;
}
void account::Login(){
	int num;//帐号
	int password;//密码
	int flag = 0;
	while( 1 ){
		system("");
		cout << "请输入帐号：";
		cin >> num;
		cout << "请输入密码：";
		cin >> password;

		string filename = to_string(num) + ".txt";//保存帐号信息的文件名
		ifstream readfile;
		readfile.open(filename);
		if( readfile.fail() ){
			cout << "用户不存在!" << endl;
			getchar();
			continue;//重新输入帐号密码
		}
		//读入用户信息
		ReadUser(readfile);
		readfile.close();

		//判断帐号是否冻结
		if( LoadingAccount.freeze ){
			cout << "账号已被冻结，登入失败！" << endl;
			return ;
		}
		//用户信息已经读入，确认密码是否正确
		if( LoadingAccount.password == password ){
			LoadingAccount.num = num;
			cout << "用户登入成功!" << endl;
			getchar();
			Menu_User();
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
			continue;
		}
	}
}
void account::recording(int amount){
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//保存帐号信息的文件名
	ofstream outfile;
	outfile.open(filename,ios::app);
	//将时间转化为文本写入文件
	time_t now = time(0);
	char* dt = ctime(&now);
	outfile << endl << dt ;
	//判断存取款，写入文件
	if( amount >0 ){
		outfile << "存款" << amount << "元" << "\t";
	}
	else{
		amount = -amount;
		outfile << "取款" << amount << "元" << "\t";
	}
	outfile << "余额" << LoadingAccount.balance << "元" << endl;
	outfile.close();
}
void account::transfer_recording(int amount,int num){
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//保存帐号信息的文件名
	ofstream outfile;
	outfile.open(filename,ios::app);
	//将时间转化为文本写入文件
	time_t now = time(0);
	char* dt = ctime(&now);
	outfile << endl << dt ;
	//写入存取款信息
	outfile << "汇款到账户"<< num << "合计" << amount << "元" << "\t";
	outfile << "余额" << LoadingAccount.balance << "元" << endl;
	outfile.close();
}
void account::deposit(){
	int flag = 1;//是否继续存款循环的标志
	int confirm ;//确认存款
	while( flag ){
		confirm = 0;//初始化
		int amount = 0;//存款额
		system("");
		cout << "请输入存款额："<<endl;
		cin >> amount;
		getchar();

		system("");
		cout << "您将要存款" << amount << "元" << endl;
		cout << "请再次确认存款（1-确认，0-取消）"<<endl;
		cin >> confirm;
		getchar();
		if( confirm ){
			system("");
			LoadingAccount.balance += amount;
			cout << "存款成功！" << endl;
			cout << "您的账户余额为" << LoadingAccount.balance << "元" << endl;
			recording(amount);
		}
		cout << "是否继续存款？（1-是，0-否）"<<endl;
		cin >> flag;
		getchar();
	}
	}
void account::withdraw(){
	int flag = 1;//是否继续取款循环的标志
	int confirm ;//确认取款
	while( flag ){
		confirm = 0;
		int amount = 0;
		system("");
		cout << "请输入取款额："<<endl;
		cin >> amount;
		getchar();
		system("");
		cout << "您将要取款" << amount << "元" << endl;
		cout << "请再次确认取款（1-确认，0-取消）"<<endl;
		cin >> confirm;
		getchar();
		if( confirm ){
			system("");
			if( LoadingAccount.balance >= amount ){
				LoadingAccount.balance -= amount;
				cout << "取款成功！" << endl;
				cout << "您的账户余额为" << LoadingAccount.balance << "元" << endl;
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
	string filename = to_string(num) + ".txt";//文件名称
	ofstream outfile;
	outfile.open(filename);
	//若文件打开失败
	if( outfile.fail() ){
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}
	//保存信息到文件
	outUser(outfile);
	outfile.close();
}
void account::Details(){
	system("");
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//文件名称
	ifstream infile;
	infile.open(filename);
	string tempstr;//在循环中承载文件内容
	while( !infile.eof() ){
		getline(infile,tempstr);//将文件内容输入到tempstr中
		cout << tempstr << endl;
	}
	infile.close();
	getchar();
}
void account::ChangePassword(){
	while( 1 ){
Change_begin:
		system("");
		int password,password1,password2;
		cout << "请输入原密码(输入0退出)：";
		cin >> password;
		//输入0退出
		if( password == 0 ){
			return;
		}
		//检测密码是否正确
		if( password == LoadingAccount.password ){
			//新密码输入
			system("");
			cout<<"请输入新6位数字密码:";
			cin >> password1;
			//密码格式检测
			if( cin.fail() ){//是否输入的是数字
				cin.clear();
				cout << "请输入符合格式的密码!" << endl;
				getchar();
				getchar();
				getchar();
				goto Change_begin;
			}
			if( password1 < 100000 || password1 > 999999 ){//是否输入6位数字
				cout << "请输入符合格式的密码!" << endl;
				goto Change_begin;
			}
			cout<<"请再次输入新6位数字密码:";
			cin >> password2;
			//检验密码
			for(int i = 1;i <= 3;i++){
				if( password1 != password2 ){
					system("");
					cout << "两次输入密码不同，请重新输入密码"<<endl;
					cout<<"请输入新6位数字密码:";
					cin >> password1;
					cout<<"请再次输入新6位数字密码:";
					cin >> password2;
				}
				else{
					LoadingAccount.password = password1;
					cout << "密码修改成功！\n新密码为:" << password << endl;
					getchar();
					getchar();
					break;
				}
				if( i==3 && password1 != password2 ){
					system("");
					cout << "你已经失败了三次，系统自动退出!";
					getchar();
					return ;
				}
			}
		}
		else{
			system("");
			cout << "密码输入错误，修改密码失败！"<<endl;
		}
	}
}
void account::Delete(){
	system("");
	int password;//密码
	char ID[24];//身份证号
	//身份验证
	cout << "请输入密码:";
	cin >> password;
	cout << "请输入身份证号:";
	cin >> ID;
	int tempnum = LoadingAccount.num;//保存帐号
	
	system("");
	if( password == LoadingAccount.password && ID == LoadingAccount.ID ){
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
}
void account::frozen(){
	system("");
	int flag = 0;//二次确认
	cout << "是否确认冻结帐号？ 1-确认，2-取消" << endl;
	cin >> flag;
	if( flag ){
		LoadingAccount.freeze = 1;
		cout << 	"冻结成功！"<<endl;
		LoadingAccount.Save();//保存帐号冻结信息到文件
		getchar();
	}
}
void account::transfer(){
	int amount;//转账的数额
	int num;//转账的帐号
	int flag;//继续转账标志
	int flag2;//二次确认标志
	account transfer_account;
	do{
		system("");
		cout << "请输入要转账的帐号:";
		cin >> num;
		cout << "请输入要转账的金额:";
		cin >> amount;
		//检测余额
		if( amount >= LoadingAccount.balance ){
			system("");
			cout << "账户余额不足，转账失败!" << endl;
			getchar();
			continue;
		}
		ifstream readfile;
		string transfer_account_name = to_string(num) + ".txt";//对方账户文件名
		readfile.open(transfer_account_name);
		//检测对方账户是否存在
		if( readfile.fail() ){
			system("");
			cout << "对方账户不存在，转账失败!" << endl;
			getchar();
			continue;
		}
		//对方账户信息读取
		transfer_account.ReadUser(readfile);
		//检测对方账户情况
		if( transfer_account.freeze ){
			system("");
			cout << "对方账户已被冻结，转账失败!" << endl;
			getchar();
			continue;
		}
		//二次确认
		cout << "是否确认转账"<< amount << "元？ 1-确认 2-取消" << endl;
		cin >> flag2;
		if( !flag2 ){
			continue;
		}
		transfer_account.balance += amount;//对方账户余额增加
		LoadingAccount.balance -= amount;//己方账户余额减少
		transfer_account.Save();//对方账户信息保存
		readfile.close();
		system("");
		//将汇款记录保存到账户明细中
		transfer_recording(amount,num);
		cout << "转账成功！" << endl;
		cout << "是否继续转账? 1-是 0-否" << endl;
		cin >> flag;
	}while(flag);
}
//============================================================================cpp_Admin
void account::Administrator_ReadUser(){
	int num;
	while( 1 ){
		system("");
		cout << "请输入卡号：";
		cin >> num;

		string filename = to_string(num) + ".txt";
		ifstream readfile;
		readfile.open(filename);
		//账户文件不存在
		if( readfile.fail() ){
			cout << "用户不存在!" << endl;
			getchar();
		}
		else{
			//读入用户信息
			ReadUser(readfile);
			readfile.close();
			cout << "账户信息读入成功！" << endl;
			getchar();
			return;
		}
	}
}
void account::Administrator_PrintDetails(void){
	system("");
	int tempnum = 0;
	cout << "请输入需要查询的帐号：";
	cin >> tempnum;

	system("");
	string filename = to_string(tempnum) + "-recording.txt";
	ifstream infile;
	infile.open(filename);
	string tempstr;
	while( !infile.eof() ){//输出文件内容直到读完整个文件
		getline(infile,tempstr);//将文件内容输入到tempstr中
		cout << tempstr << endl;
	}
	infile.close();
	getchar();
	getchar();
}
void account::Administrator_delete(void){
	system("");
	cout << "请输入需要销户的帐号：";
	int tempnum = 0;
	int flag = 0;
	cin >> tempnum;
	
	string filename1 = to_string(tempnum) + "-recording.txt";//账户明细文件
	string filename2 = to_string(tempnum) + ".txt";//账户信息文件
	const char * cf1 = filename1.c_str();
	const char * cf2 = filename2.c_str();
	//销毁文件计数
	if( !remove(cf1) ){
		flag ++;
	}
	if( !remove(cf2) ){
		flag ++;
	}	
	//当销户文件数不为0,则帐号信息销毁成功
	if( flag >0 ){
		cout << "销户成功！" << endl;
	}
	else{
		cout << "账户不存在，销户失败！" << endl;
	}
	getchar();
}
void account::Administrator_frozen(){
	Administrator_ReadUser();
	system("");
	int flag = 0;//二次确认
	cout << "是否确认冻结帐号？ 1-确认，0-取消" << endl;
	cin >> flag;
	if( flag ){
		LoadingAccount.freeze = 1;
		cout << 	"冻结成功！"<<endl;
		LoadingAccount.Save();//保存帐号冻结信息到文件
		getchar();
	}
}
void account::Administrator_unfrozen(void){
	system("");
	cout << "请输入需要解冻的帐号：";
	int tempnum = 0;
	cin >> tempnum;
	string filename = to_string(tempnum) + ".txt";//文件名

	//从文件读入用户信息
	ifstream readfile;
	readfile.open(filename);
	if( readfile.fail() ){
		cout << "\t 该帐号所有账户不存在！ \"" << filename << "\"" << endl;
		getchar();
		return;
	}
	ReadUser(readfile);
	readfile.close();

	//输出用户信息到文件
	ofstream outfile;
	outfile.open(filename);
	if( outfile.fail() ){
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}
	//输出帐号及信息到文件
	outUser(outfile);
	outfile.close();

	cout << "帐号" << tempnum << "解冻成功!" << endl;
}
int Administrator_Check(void){
	string CorrectPassword,EnteredPassword;//保存正确的密码和输入的密码
	cout << "Please input Administrator password:" <<endl;
	cin >> EnteredPassword;

	//从文件中读取正确的管理员密码
	ifstream in;
	in.open("Bank.txt");
	in >> CorrectPassword;
	in.close();

	if( CorrectPassword == EnteredPassword ){//若密码输入正确
		cout << "管理员大人，欢迎回来" << endl;
		return 1;
	}
	else{//若密码输入错误
		cout << "密码错误!返回选择界面" << endl;
		return 0;
	}
}
void account::Administrator_ReadDetails(){
	LoadingAccount.Administrator_ReadUser();
	system("");
	cout << "账号\t" << LoadingAccount.num << endl;
	cout << "姓名\t" << LoadingAccount.name << endl;
	cout << "密码\t" << LoadingAccount.password << endl;
	cout << "手机号\t" << LoadingAccount.phonenum << endl;
	if( LoadingAccount.freeze ){
		cout << "帐号状态\t冻结" << endl;
	}
	else{
		cout << "帐号状态\t未冻结" << endl;
	}
	cout << "余额\t" << LoadingAccount.balance << endl;
	getchar();
}
//============================================================================cpp_Menu
void Menu_Administrator(void){
	int choice;
	do{
		system("");
		cout << "============================================================"<<endl;
		cout << "1-查看账户流水 2-删除账户\n3-解冻帐号 4-输出帐号个人信息\n5- 冻结帐号 0-退出系统"<<endl;
		cout << "============================================================"<<endl;

		cin >> choice;
		switch(choice){
			case 1:{
							 LoadingAccount.Administrator_PrintDetails();
							 break;
						 }
			case 2:{
							LoadingAccount.Administrator_delete();
							break;
						 }
			case 3:{
							 LoadingAccount.Administrator_unfrozen();
							 break;
						 }
			case 4:{
							 LoadingAccount.Administrator_ReadDetails();
							 break;
						 }
			case 5:{
							 LoadingAccount.Administrator_frozen();
							 break;
						 }
			case 0:
				break;
		}
	}while(choice);
	return ;
}
void Menu_User(){
	int choice;
	do{
		system("");
		cout << "============================================================"<<endl;
		LoadingAccount.welcome();
		cout << "1-存款 2-取款 \n3-账户明细查询 4-密码修改\n5-余额查询 6-转账\n7-冻结账户 8-销户\n0-注销登录"<<endl;
		cout << "============================================================"<<endl;
		cin >> choice;
		switch(choice){
			case 1:{
							 LoadingAccount.deposit();
							 break;
						 }
			case 2:{
							 LoadingAccount.withdraw();
							 break;
						 }
			case 3:{
							 LoadingAccount.Details();
							 break;
						 }
			case 4:{
							 LoadingAccount.ChangePassword();
							 break;
						 }
			case 5:{
							 system("");
							 cout << "您的账户余额为" << LoadingAccount.balance << "元" << endl;
							 getchar();
							 break;
						 }
			case 6:{
							 LoadingAccount.transfer();
							 break;
						 }
			case 7:{
							 LoadingAccount.frozen();
							 return;//返回初始界面
						 }
			case 8:{
							 LoadingAccount.Delete();
							 return;//返回初始界面
						 }
			case 0:{
							 //保存更新的帐号信息到文件
							 LoadingAccount.Save();
							 break;
						 }
		}
	}while(choice);//choice==0结束
	return ;
}
void Menu_Choose(void){
		int choice;
	do{
		system("");
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
				LoadingAccount.Login();
				break;
						 }
			case 2:{
				if( Administrator_Check() ){
					Menu_Administrator();
				}
				break;
						 }
			case 3:{
				LoadingAccount.Register();
				Menu_User();
				break;
						 }
			case 0:
				break;
		}
	}while(choice);
}

int main(void){
	//首先检测系统文件
	if( !CheckBanktxtSuccess() ){
		//创建系统文件
		CreatBanktxt();
	}
	Menu_Choose();
	return 0;
}
