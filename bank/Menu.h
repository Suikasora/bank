#pragma once
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