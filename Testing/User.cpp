#include "User.h"

void User::delResult(int ind)
{
	if (ind < 0 || ind >= tResults.size()) throw std::exception(" ������� ������ ������ ����������");
	tResults.erase(tResults.begin() + ind);
}

 TestResult& User::getTestResult(int index)
{
	if (index < 0 || index >= tResults.size()) throw std::exception(" ������� ������ ������ ����������");
	return tResults[index];
}

void User::toFStream(std::ofstream& ofs) const
{
	ofs << fi.name << std::endl;
	ofs << fi.surname << std::endl;
	ofs << addres.city << std::endl;
	ofs << addres.country << std::endl;
	ofs << addres.street << std::endl;
	ofs << addres.homeNumber << std::endl;
    ofs << phoneNumber << std::endl;
	ofs << idcrypt(password) << std::endl;
	ofs << idcrypt(login) << std::endl;
	ofs << user_results << std::endl;
	for (const auto& val : tResults)
		val.toFStream(ofs);
}

void User::fromFStream(std::ifstream& ifs)
{
	int temp;
	std::string tmp;
	getFSString(ifs, tmp);
	setName(tmp);
	getFSString(ifs, tmp);
	setSurname(tmp);
	getFSString(ifs, tmp);
	setCity(tmp);
	getFSString(ifs, tmp);
	setCountry(tmp);
	getFSString(ifs, tmp);
	setStreet(tmp);
	if (ifs >> temp) setHomeNumber(temp);
	else throw std::exception(" ������� � ���� �����������");
	getFSString(ifs, tmp);
	setPhone(tmp);
	getFSString(ifs, tmp);
	setPassword(idcrypt(tmp));
	getFSString(ifs, tmp);
	setLogin(idcrypt(tmp));
	if (goToLabel(ifs, user_results))
	{
		while (goToNextLabel(ifs, TestResult::tres_lable))
			addResult(TestResult(ifs));
	}
}

void User::showResults() const
{
	show_res( false);
}

void User::showNPResults() const
{
	show_res(true);
}

void User::show(int index) const
{
	std::cout << " --  ����������  ";
	if (index) std::cout << "#" << index <<"  --" << std::endl;
	else std::cout <<  "--" << std::endl;
	std::cout << "  ����    : " << login << std::endl;
	std::cout << "  ������   : " << password << std::endl;
	std::cout << "  ��'�     : " << fi.name << std::endl;
	std::cout << "  ������� : " << fi.surname << std::endl;
	std::cout << "  �����   : " << addres.country << std::endl;
	std::cout << "  ̳���    : " << addres.city << std::endl;
	std::cout << "  ������   : " << addres.street << std::endl;
	std::cout << "  ���.���  : " << addres.homeNumber << std::endl;
	std::cout << "  �������  : " << phoneNumber << std::endl;

}

void User::show_res(bool np) const
{
	int ind = 0;
	system("cls");
	if (tResults.empty())
	{
		std::cout << "  ���������� ����� ������....";
		return;
	}
	if(!np) std::cout << "   -=  ���������� �����  =-" << std::endl;
	else std::cout << "   -=  �� ������� �����  =-" << std::endl;
	std::cout << std::endl;
	for (const auto& val : tResults)
	{
		 ++ind;
		if (np)
		{
			if (!val.isPassed())val.showResult(ind);
		}
		else val.showResult(ind);
		std::cout << std::endl;
	}
	
}

void User::setPassword(const std::string& pass)
{
	if (!isAlNum(pass)) throw std::invalid_argument("�� �������� ������ ������");
		password = pass;
}

void User::setLogin(const std::string& login)
{
	if (isBlank(login)) throw std::invalid_argument("�� �������� ������ ����� �����������");
	this->login = login;
}

void User::setName(const std::string& name)
{
	if (isBlank(name)) throw std::invalid_argument("�� �������� ������ ���� �����������");
	fi.name = name;
}

void User::setSurname(const std::string& surname)
{
	if (isBlank(surname)) throw std::invalid_argument("�� �������� ������ ���볿 �����������");
	fi.surname = surname;
}

void User::setStreet(const std::string& street)
{
	if (isBlank(street)) throw std::invalid_argument("�� �������� ������ ������ �����������");
	addres.street = street;
}

void User::setCity(const std::string& city)
{
	if (isBlank(city)) throw std::invalid_argument("�� �������� ������ ���� �����������");
	addres.city = city;
}

void User::setCountry(const std::string& country)
{
	if (isBlank(country)) throw std::invalid_argument("�� �������� ������ ����� �����������");
	addres.country = country;
}

void User::setHomeNumber(int num)
{
	if(num <1 ) throw std::invalid_argument("�� �������� �������� ������ ������� �����������");
	addres.homeNumber = num;
}

void User::setPhone(const std::string& phone)
{
	if(phone.length() != 13)
		throw std::invalid_argument("�� �������� �������� ������ �������� �����������...\n����� ��������  ������� ���������  � 13 ������� ....");
	if(phone[0] != '+') 
		throw std::invalid_argument("�� �������� �������� ������ �������� �����������...\n����� �������� ���� ���������� � '+' ��� �����....");
	for (int i = 1; i < phone.length(); i++)
	   if(!isdigit(static_cast<unsigned char>(phone[i])))
		   throw std::invalid_argument("�� �������� �������� ������ �������� �����������\n����� �������� ���� ���������� ���� � ����....");
	phoneNumber = phone;
}
