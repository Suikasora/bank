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
	//首先检测系统文件
	if( !CheckBanktxtSuccess() ){
		//创建系统文件
		CreatBanktxt();
	}
	Menu_Choose();
	return 0;
}
