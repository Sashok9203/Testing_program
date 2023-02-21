#pragma once
#include <exception>
#include <stdexcept>
#include <string>



// Question class exceptions

class question_invalid_argument:public std::invalid_argument
{
private:
	std::string message;
public:
	question_invalid_argument():invalid_argument("������� ��������  ... "),message(invalid_argument::what()) {}
	question_invalid_argument(const std::string& message):invalid_argument("������� ��������  ... "),message(invalid_argument::what() +  message) {}
	const char* what() const { return message.c_str(); };
};


class question_invalid_file_format:public std::exception
{
private:
	std::string message;
public:
	question_invalid_file_format():exception("������� � ���� ������� ...") {}
	question_invalid_file_format(const std::string& message):message("������� � ���� ������� ...\n" + message) {}
	const char* what() const { return message.c_str(); };
};
