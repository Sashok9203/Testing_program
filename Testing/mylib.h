#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "Exceptions.h"
#include <conio.h>
#include <windows.h>

struct LogPass
{
	std::string login;
	std::string password;
};

void saveStrToFile(const std::string title, const std::string str);
std::string idcrypt(const std::string& str);
bool isFileExist(const std::string& fileName);
bool goToLabel(std::ifstream& ifs,const std::string& lable);
bool goToNextLabel(std::ifstream& ifs, const std::string& lable);
int getValue(int min, int max);
std::string getText(const std::string& title,int blankCount = 0);
std::string getWord(const std::string& title);
bool getFWord(const std::string& fileName, const std::string& label, std::string& str);
bool getFSWord(std::ifstream& ifs,std::string& str);
bool getFSString(std::ifstream& ifs, std::string& str);
bool getFSText(std::ifstream& ifs, std::string& str);
std::string getPassword();
bool fileCopy(const std::string& from, const std::string& to);
LogPass getLogPas(bool hidePass = false);

std::string getString(const std::string& title);
bool isBlank(const std::string& str);
bool isAlNum(const std::string& str);
bool isDigit(const std::string& str);
void setCursor(short x, short y);
COORD getCursor();

template<typename T>
bool isVectorExist(const std::vector<T>& vec,const T& value)
{
	for (const T& val : vec)
		if (val == value) return true;
	return false;
}
