#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include "Account.h"
#include "Menu.h"

using namespace std;

account LoadingAccount;

int main(void){
	//���ȼ��ϵͳ�ļ�
	if( !CheckBanktxtSuccess() ){
		//����ϵͳ�ļ�
		CreatBanktxt();
	}
	Menu_Choose();
	return 0;
}
