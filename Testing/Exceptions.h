#pragma once
#pragma once
#include <exception>
#include <stdexcept>
#include <string>
class invalid_file_format :public std::exception
{
private:
	std::string message;
public:
	invalid_file_format() :exception("�������  �����  ") {}
	invalid_file_format(const std::string& message) :message("�������  ����� \n" + message) {}
	const char* what() const { return message.c_str(); };
};