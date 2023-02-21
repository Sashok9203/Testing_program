#pragma once
#include <exception>
#include <stdexcept>
#include <string>

class test_invalid_argument:public std::invalid_argument
{
private:
	std::string message;
public:
	test_invalid_argument():invalid_argument("Невірний аргумент  ... "), message(invalid_argument::what()) {}
	test_invalid_argument(const std::string& message):invalid_argument("Невірний аргумент  ... "), message(invalid_argument::what() + message) {}
	const char* what() const { return message.c_str(); };
};
class test_invalid_file_format:public std::exception
{
private:
	std::string message;
public:
	test_invalid_file_format():exception("Помилка в файлі тесту ...") {}
	test_invalid_file_format(const std::string& message):message("Помилка в файлі тесту ...\n" + message) {}
	const char* what() const { return message.c_str(); };
};