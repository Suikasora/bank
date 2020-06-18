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
		cout << "�����뿨�ţ�";
		cin >> num;

		string filename = to_string(num) + ".txt";
		ifstream readfile;
		readfile.open(filename);
		//�˻��ļ�������
		if (readfile.fail()) {
			cout << "�û�������!" << endl;
			getchar();
		}
		else {
			//�����û���Ϣ
			ReadUser(readfile);
			readfile.close();
			cout << "�˻���Ϣ����ɹ���" << endl;
			getchar();
			return;
		}
	}
}
void account::Administrator_PrintDetails(void) {
	system("cls");
	int tempnum = 0;
	cout << "��������Ҫ��ѯ���ʺţ�";
	cin >> tempnum;

	system("cls");
	string filename = to_string(tempnum) + "-recording.txt";
	ifstream infile;
	infile.open(filename);
	string tempstr;
	while (!infile.eof()) {//����ļ�����ֱ�����������ļ�
		getline(infile, tempstr);//���ļ��������뵽tempstr��
		cout << tempstr << endl;
	}
	infile.close();
	getchar();
	getchar();
}
void account::Administrator_delete(void) {
	system("cls");
	cout << "��������Ҫ�������ʺţ�";
	int tempnum = 0;
	int flag = 0;
	cin >> tempnum;

	string filename1 = to_string(tempnum) + "-recording.txt";//�˻���ϸ�ļ�
	string filename2 = to_string(tempnum) + ".txt";//�˻���Ϣ�ļ�
	const char* cf1 = filename1.c_str();
	const char* cf2 = filename2.c_str();
	//�����ļ�����
	if (!remove(cf1)) {
		flag++;
	}
	if (!remove(cf2)) {
		flag++;
	}
	//�������ļ�����Ϊ0,���ʺ���Ϣ���ٳɹ�
	if (flag > 0) {
		cout << "�����ɹ���" << endl;
	}
	else {
		cout << "�˻������ڣ�����ʧ�ܣ�" << endl;
	}
	getchar();
}
void account::Administrator_frozen() {
	Administrator_ReadUser();
	system("cls");
	int flag = 0;//����ȷ��
	cout << "�Ƿ�ȷ�϶����ʺţ� 1-ȷ�ϣ�0-ȡ��" << endl;
	cin >> flag;
	if (flag) {
		LoadingAccount.freeze = 1;
		cout << "����ɹ���" << endl;
		LoadingAccount.Save();//�����ʺŶ�����Ϣ���ļ�
		getchar();
	}
}
void account::Administrator_unfrozen(void) {
	system("cls");
	cout << "��������Ҫ�ⶳ���ʺţ�";
	int tempnum = 0;
	cin >> tempnum;
	string filename = to_string(tempnum) + ".txt";//�ļ���

	//���ļ������û���Ϣ
	ifstream readfile;
	readfile.open(filename);
	if (readfile.fail()) {
		cout << "\t ���ʺ������˻������ڣ� \"" << filename << "\"" << endl;
		getchar();
		return;
	}
	ReadUser(readfile);
	readfile.close();

	//����û���Ϣ���ļ�
	ofstream outfile;
	outfile.open(filename);
	if (outfile.fail()) {
		cout << "\t Fail to open file \"" << filename << "\"" << endl;
	}

	outUser(outfile);
	outfile.close();

	cout << "�ʺ�" << tempnum << "�ⶳ�ɹ�!" << endl;
}
int Administrator_Check(void) {
	string CorrectPassword, EnteredPassword;//������ȷ����������������
	cout << "Please input Administrator password:" << endl;
	cin >> EnteredPassword;

	//���ļ��ж�ȡ��ȷ�Ĺ���Ա����
	ifstream in;
	in.open("Bank.txt");
	in >> CorrectPassword;
	in.close();

	if (CorrectPassword == EnteredPassword) {//������������ȷ
		cout << "����Ա���ˣ���ӭ����" << endl;
		return 1;
	}
	else {//�������������
		cout << "�������!����ѡ�����" << endl;
		return 0;
	}
}
void account::Administrator_ReadDetails() {
	LoadingAccount.Administrator_ReadUser();
	system("cls");
	cout << "�˺�\t" << LoadingAccount.num << endl;
	cout << "����\t" << LoadingAccount.name << endl;
	cout << "����\t" << LoadingAccount.password << endl;
	cout << "�ֻ���\t" << LoadingAccount.phonenum << endl;
	if (LoadingAccount.freeze) {
		cout << "�ʺ�״̬\t����" << endl;
	}
	else {
		cout << "�ʺ�״̬\tδ����" << endl;
	}
	cout << "���\t" << LoadingAccount.balance << endl;
	getchar();
}