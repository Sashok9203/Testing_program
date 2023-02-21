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
	invalid_file_format() :exception("Помилка  файлу  ") {}
	invalid_file_format(const std::string& message) :message("Помилка  файлу \n" + message) {}
	const char* what() const { return message.c_str(); };
};