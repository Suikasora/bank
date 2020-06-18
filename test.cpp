#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

/*int main(void)*/
//{
	//int ID;
	//string name;
	//ifstream file;
	//file.open("test.txt");
	//file >> ID ;
	//file >> name;
	//cout << ID << name;
	//file.close();
	//return 0;
/*}*/
void Menu_User(){
	int choice;
	do{
		system("");
		cout << "============================================================"<<endl;
		cout << "1-存款 2-取款 \n3-账户明细查询 4-密码修改\n5-余额查询 6-销户\n7-冻结账户\n0-注销登录"<<endl;
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
							 return;
						 }
			case 6:{
							 LoadingAccount.Delete();
							 break;
						 }
			case 7:{
							 
						 }
			case 0:{
							 LoadingAccount.Save();
							 break;
						 }
		}
	}while(choice);
	return ;
}
int main(void)
{
	int ID;
	string name,temp;
	string tID = "ID:";
	string tname = "name:";
	ifstream file;
	file.open("test.txt");
	while( file >> temp ){
		if( temp == tID ){
			file >> ID;
		}
		if( temp == tname ){
			file >> name;
		}
		if( file.eof() ){
			break;
		}
	}
	cout << name << ID << endl;
		return 0;
}
