#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>

using namespace std;
void Menu_Choose();//ϵͳ�ĳ�ʼѡ�����
void Menu_User();//��ͨ�û��˵�
void Menu_Administrator();//����Ա�û��˵�

int CheckBanktxtSuccess();//�������ϵͳ�ļ�
void CreatBanktxt();//�������е�ϵͳ�ļ�

int Administrator_Check();//������Ա����