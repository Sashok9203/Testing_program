#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include "Exceptions.h"

class testing_invalid_file_format :public invalid_file_format
{
private:
	std::string message;
public:
	testing_invalid_file_format() :invalid_file_format("Testing  ...") {}
	testing_invalid_file_format(const std::string& message) :message("Testing ...\n" + message) {}
	const char* what() const { return message.c_str(); };
};

