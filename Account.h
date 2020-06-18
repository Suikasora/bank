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
	int num;//�ʺ�
	char ID[24];//���֤��
	char name[20];//����
	int password;//����
	char phonenum[14];//�ֻ�����
	int freeze = 0;//�����ж�
public:
	double balance;//���
	inline void ReadUser(ifstream& readfile);//���ļ���ȡ�˺ż�����Ϣ
	inline void outUser(ofstream& outfile);//����ʺż���Ϣ���ļ�
	void welcome();
	void Register();//����
	void Login();//�ʺŵ�¼
	void deposit();//���
	void withdraw();//ȡ��
	void recording(int amount);//�����˻���ϸ
	void transfer_recording(int amount, int num);
	void Details();//��ӡ�˻���ϸ
	void ChangePassword();//��������
	void frozen();//�����˺�
	void Save();//������Ϣ���ļ�
	void Delete();//ɾ���ʺż�����Ϣ
	void transfer();//ת��
//����Ա���ܺ���
	void Administrator_PrintDetails();//�����ʺŲ�ѯ�˻���ϸ
	void Administrator_delete();//ɾ���ʺż�����Ϣ
	void Administrator_frozen();
	void Administrator_unfrozen();//�ⶳ�˺�
	void Administrator_ReadUser();//��ȡ�˻���Ϣ
	void Administrator_ReadDetails();//�����ǰ�˻�������Ϣ
	//int ReadUser(string num, account *tempaccount);
	//
};
extern account LoadingAccount;//��ǰ�ʺ�


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