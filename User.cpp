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
	cout << ">>�ʺ�Ϊ[" << num << "]���û�[" << name << "],��ӭ����" << endl;
}
void account::Register() {
	system("cls");
	//�������������
	int password1;
	int password2;
	//������Ϣ��LoadingAccount
	cout << "����������:";
	cin >> LoadingAccount.name;
	cout << "���������֤��:";
	cin >> LoadingAccount.ID;
	cout << "���������ĵ绰����:";
	cin >> LoadingAccount.phonenum;
Regi_begin:
	system("cls");
	cout << "������6λ��������:";
	cin >> password1;
	//�����ж������Ƿ�Ϸ�
	if (cin.fail()) {//�Ƿ������������
		cin.clear();
		cout << "��������ϸ�ʽ������!" << endl;
		getchar();
		getchar();
		getchar();
		goto Regi_begin;
	}
	if (password1 < 100000 || password1 > 999999) {//�Ƿ�����6λ����
		cout << "��������ϸ�ʽ������!" << endl;
		goto Regi_begin;
	}
	cout << "���ٴ�����6λ��������:";
	cin >> password2;

	//�ж������Ƿ�Ϸ�
	for (int i = 1; i <= 3; i++) {
		if (password1 != password2) {
			system("cls");
			cout << "�����������벻ͬ����������������!(������"<<3-i<<"�λ���)" << endl;
			cout << "������6λ��������:";
			cin >> password1;
			cout << "���ٴ�����6λ��������:";
			cin >> password2;
		}
		else {
			LoadingAccount.password = password1;
		}
		if (i == 3 && password1 != password2) {
			system("cls");
			cout << "���Ѿ�ʧ�������Σ�ϵͳ�Զ��˳�!";
			getchar();
			return;
		}
	}
	//ȷ���ʺŲ����浽�ļ�
	string TempPassword;
	int TempAccountnum;//���������˻����˺�
	//������ϵͳ�ļ�
	fstream Bank;
	Bank.open("Bank.txt", ios::in | ios::out);
	Bank >> TempPassword >> TempAccountnum;//��ȡϵͳ�ļ�
	//�����˻��ļ�
	string filename = to_string(TempAccountnum) + ".txt";
	ofstream outfile;
	outfile.open(filename);
	outfile << LoadingAccount.ID << endl;
	outfile << LoadingAccount.name << endl;
	outfile << LoadingAccount.password << endl;
	outfile << LoadingAccount.phonenum << endl;
	outfile << "0" << endl;//�Ƿ񶳽�
	outfile << "0" << endl;//�˻����
	outfile.close();
	//������������ɺ�ȷ���˻��ʺ�
	LoadingAccount.num = TempAccountnum;
	//����ϵͳ�ļ�
	Bank.seekp(ios::beg);//ת���ļ���ͷ
	TempAccountnum++;//��ǵ��ʺ�����
	Bank << TempPassword << endl << TempAccountnum;
	Bank.close();

	return;
}
void account::Login() {
	int num;//�ʺ�
	int password;//����
	int flag = 0;
	while (1) {
		system("cls");
		cout << "�������ʺţ�";
		cin >> num;
		cout << "���������룺";
		cin >> password;

		string filename = to_string(num) + ".txt";//�����ʺ���Ϣ���ļ���
		ifstream readfile;
		readfile.open(filename);
		if (readfile.fail()) {
			cout << "�û�������!" << endl;
			getchar();
			continue;//���������ʺ�����
		}
		//�����û���Ϣ
		ReadUser(readfile);
		readfile.close();

		//�ж��ʺ��Ƿ񶳽�
		if (LoadingAccount.freeze) {
			cout << "�˺��ѱ����ᣬ����ʧ�ܣ�" << endl;
			return;
		}
		//�û���Ϣ�Ѿ����룬ȷ�������Ƿ���ȷ
		if (LoadingAccount.password == password) {
			LoadingAccount.num = num;
			cout << "�û�����ɹ�!" << endl;
			getchar();
			Menu_User();
			return;
		}
		else {
			cout << "�����������!����ʧ��!" << endl;
			flag++;
			if (flag >= 3) {
				cout << "ʧ�ܴ������࣬������ʱ��ֹ����!" << endl;
				break;
			}
			getchar();
			continue;
		}
	}
}

void account::recording(int amount) {
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//�����ʺ���Ϣ���ļ���
	ofstream outfile;
	outfile.open(filename, ios::app);
	//��ʱ��ת��Ϊ�ı�д���ļ�
	time_t now = time(0);
	char* dt = ctime(&now);
	outfile << endl << dt;
	//�жϴ�ȡ�д���ļ�
	if (amount > 0) {
		outfile << "���" << amount << "Ԫ" << "\t";
	}
	else {
		amount = -amount;
		outfile << "ȡ��" << amount << "Ԫ" << "\t";
	}
	outfile << "���" << LoadingAccount.balance << "Ԫ" << endl;
	outfile.close();
}
void account::transfer_recording(int amount, int num) {
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//�����ʺ���Ϣ���ļ���
	ofstream outfile;
	outfile.open(filename, ios::app);
	//��ʱ��ת��Ϊ�ı�д���ļ�
	time_t now = time(0);
	char* dt = ctime(&now);
	outfile << endl << dt;
	//д���ȡ����Ϣ
	outfile << "���˻�" << num << "�ϼ�" << amount << "Ԫ" << "\t";
	outfile << "���" << LoadingAccount.balance << "Ԫ" << endl;
	outfile.close();
}
void account::deposit() {
	int flag = 1;//�Ƿ�������ѭ���ı�־
	int confirm;//ȷ�ϴ��
	while (flag) {
		confirm = 0;//��ʼ��
		int amount = 0;//����
		system("cls");
		cout << "��������" << endl;
		cin >> amount;
		getchar();

		system("cls");
		cout << "����Ҫ���" << amount << "Ԫ" << endl;
		cout << "���ٴ�ȷ�ϴ�1-ȷ�ϣ�0-ȡ����" << endl;
		cin >> confirm;
		getchar();
		if (confirm) {
			system("cls");
			LoadingAccount.balance += amount;
			cout << "���ɹ���" << endl;
			cout << "�����˻����Ϊ" << LoadingAccount.balance << "Ԫ" << endl;
			recording(amount);
		}
		cout << "�Ƿ��������1-�ǣ�0-��" << endl;
		cin >> flag;
		getchar();
	}
}
void account::withdraw() {
	int flag = 1;//�Ƿ����ȡ��ѭ���ı�־
	int confirm;//ȷ��ȡ��
	while (flag) {
		confirm = 0;
		int amount = 0;
		system("cls");
		cout << "������ȡ��" << endl;
		cin >> amount;
		getchar();
		system("cls");
		cout << "����Ҫȡ��" << amount << "Ԫ" << endl;
		cout << "���ٴ�ȷ��ȡ�1-ȷ�ϣ�0-ȡ����" << endl;
		cin >> confirm;
		getchar();
		if (confirm) {
			system("cls");
			if (LoadingAccount.balance >= amount) {
				LoadingAccount.balance -= amount;
				cout << "ȡ��ɹ���" << endl;
				cout << "�����˻����Ϊ" << LoadingAccount.balance << "Ԫ" << endl;
				recording(-amount);
			}
			else {
				cout << "���㣬ȡ��ʧ�ܣ�" << endl;
			}
		}
		cout << "�Ƿ����ȡ���1-�ǣ�0-��" << endl;
		cin >> flag;
		getchar();
	}
}
void account::Save() {
	string filename = to_string(num) + ".txt";//�ļ�����
	ofstream outfile;
	outfile.open(filename);
	//���ļ���ʧ��
	if (outfile.fail()) {
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}
	//������Ϣ���ļ�
	outUser(outfile);
	outfile.close();
}
void account::Details() {
	system("cls");
	string filename = to_string(LoadingAccount.num) + "-recording.txt";//�ļ�����
	ifstream infile;
	infile.open(filename);
	string tempstr;//��ѭ���г����ļ�����
	while (!infile.eof()) {
		getline(infile, tempstr);//���ļ��������뵽tempstr��
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
		cout << "������ԭ����(����0�˳�)��";
		cin >> password;
		//����0�˳�
		if (password == 0) {
			return;
		}
		//��������Ƿ���ȷ
		if (password == LoadingAccount.password) {
			//����������
			system("cls");
			cout << "��������6λ��������:";
			cin >> password1;
			//�����ʽ���
			if (cin.fail()) {//�Ƿ������������
				cin.clear();
				cout << "��������ϸ�ʽ������!" << endl;
				getchar();
				getchar();
				getchar();
				goto Change_begin;
			}
			if (password1 < 100000 || password1 > 999999) {//�Ƿ�����6λ����
				cout << "��������ϸ�ʽ������!" << endl;
				goto Change_begin;
			}
			cout << "���ٴ�������6λ��������:";
			cin >> password2;
			//��������
			for (int i = 1; i <= 3; i++) {
				if (password1 != password2) {
					system("cls");
					cout << "�����������벻ͬ����������������" << endl;
					cout << "��������6λ��������:";
					cin >> password1;
					cout << "���ٴ�������6λ��������:";
					cin >> password2;
				}
				else {
					LoadingAccount.password = password1;
					cout << "�����޸ĳɹ���\n������Ϊ:" << password << endl;
					getchar();
					getchar();
					break;
				}
				if (i == 3 && password1 != password2) {
					system("cls");
					cout << "���Ѿ�ʧ�������Σ�ϵͳ�Զ��˳�!";
					getchar();
					return;
				}
			}
		}
		else {
			system("cls");
			cout << "������������޸�����ʧ�ܣ�" << endl;
		}
	}
}
void account::Delete() {
	system("cls");
	int password;//����
	char ID[24];//���֤��
	//�����֤
	cout << "����������:";
	cin >> password;
	cout << "���������֤��:";
	cin >> ID;
	int tempnum = LoadingAccount.num;//�����ʺ�

	system("cls");
	if (password == LoadingAccount.password && ID == LoadingAccount.ID) {
		string filename1 = to_string(tempnum) + "-recording.txt";
		string filename2 = to_string(tempnum) + ".txt";
		const char* cf1 = filename1.c_str();
		const char* cf2 = filename2.c_str();
		remove(cf1);
		remove(cf2);
		cout << "�����ɹ���" << endl;
	}
	else {
		cout << "������������ʧ�ܣ�" << endl;
	}
	getchar();
}
void account::frozen() {
	system("cls");
	int flag = 0;//����ȷ��
	cout << "�Ƿ�ȷ�϶����ʺţ� 1-ȷ�ϣ�2-ȡ��" << endl;
	cin >> flag;
	if (flag) {
		LoadingAccount.freeze = 1;
		cout << "����ɹ���" << endl;
		LoadingAccount.Save();//�����ʺŶ�����Ϣ���ļ�
		getchar();
	}
}
void account::transfer() {
	int amount;//ת�˵�����
	int num;//ת�˵��ʺ�
	int flag;//����ת�˱�־
	int flag2;//����ȷ�ϱ�־
	account transfer_account;
	do {
		system("cls");
		cout << "������Ҫת�˵��ʺ�:";
		cin >> num;
		cout << "������Ҫת�˵Ľ��:";
		cin >> amount;
		//������
		if (amount >= LoadingAccount.balance) {
			system("cls");
			cout << "�˻����㣬ת��ʧ��!" << endl;
			getchar();
			continue;
		}
		ifstream readfile;
		string transfer_account_name = to_string(num) + ".txt";//�Է��˻��ļ���
		readfile.open(transfer_account_name);
		//���Է��˻��Ƿ����
		if (readfile.fail()) {
			system("cls");
			cout << "�Է��˻������ڣ�ת��ʧ��!" << endl;
			getchar();
			continue;
		}
		//�Է��˻���Ϣ��ȡ
		transfer_account.ReadUser(readfile);
		//���Է��˻����
		if (transfer_account.freeze) {
			system("cls");
			cout << "�Է��˻��ѱ����ᣬת��ʧ��!" << endl;
			getchar();
			continue;
		}
		//����ȷ��
		cout << "�Ƿ�ȷ��ת��" << amount << "Ԫ�� 1-ȷ�� 2-ȡ��" << endl;
		cin >> flag2;
		if (!flag2) {
			continue;
		}
		transfer_account.balance += amount;//�Է��˻��������
		LoadingAccount.balance -= amount;//�����˻�������
		transfer_account.Save();//�Է��˻���Ϣ����
		readfile.close();
		system("cls");
		//������¼���浽�˻���ϸ��
		transfer_recording(amount, num);
		cout << "ת�˳ɹ���" << endl;
		cout << "�Ƿ����ת��? 1-�� 0-��" << endl;
		cin >> flag;
	} while (flag);
}