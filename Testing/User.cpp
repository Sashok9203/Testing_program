#include "User.h"

void User::delResult(int ind)
{
	if (ind < 0 || ind >= tResults.size()) throw std::exception(" Невірний індекс масиву результатів");
	tResults.erase(tResults.begin() + ind);
}

 TestResult& User::getTestResult(int index)
{
	if (index < 0 || index >= tResults.size()) throw std::exception(" Невірний індекс масиву результатів");
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
	else throw std::exception(" Помилка в файлі користувача");
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

std::string User::getResStr() const
{
	return  show_res( false);
}

std::string User::getNPResStr() const
{
	return show_res(true);
}

std::string User::getUserStr(int index) const
{
	std::stringstream ss;
	ss << " --  Користувач  ";
	if (index) ss << "#" << index <<"  --" << std::endl;
	else ss <<  "--" << std::endl;
	ss << "  Логін    : " << login << std::endl;
	ss << "  Пароль   : " << password << std::endl;
	ss << "  Ім'я     : " << fi.name << std::endl;
	ss << "  Прізвище : " << fi.surname << std::endl;
	ss << "  Країна   : " << addres.country << std::endl;
	ss << "  Місто    : " << addres.city << std::endl;
	ss << "  Вулиця   : " << addres.street << std::endl;
	ss << "  Ном.буд  : " << addres.homeNumber << std::endl;
	ss << "  Телефон  : " << phoneNumber << std::endl;
	return ss.str();
}

std::string User::show_res(bool np) const
{
	std::stringstream ss;
	int ind = 0;
	if (tResults.empty())
	{
		ss << "  Результати тестів відсутні....";
		return ss.str();
	}
	if(!np) ss << "   -=  Результати тестів  =-" << std::endl;
	else ss << "   -=  Не завершені тести  =-" << std::endl;
	ss << std::endl;
	for (const auto& val : tResults)
	{
		++ind;
		if (np) { if (!val.isPassed()) ss << val.getResStr(ind); }
		else ss << val.getResStr(ind);
		ss << std::endl;
	}
	return ss.str();
}

void User::setPassword(const std::string& pass)
{
	if (!isAlNum(pass)) throw std::invalid_argument("Не коректна строка пароля");
		password = pass;
}

void User::setLogin(const std::string& login)
{
	if (isBlank(login)) throw std::invalid_argument("Не коректна строка логіну користувача");
	this->login = login;
}

void User::setName(const std::string& name)
{
	if (isBlank(name)) throw std::invalid_argument("Не коректна строка імені користувача");
	fi.name = name;
}

void User::setSurname(const std::string& surname)
{
	if (isBlank(surname)) throw std::invalid_argument("Не коректна строка фамілії користувача");
	fi.surname = surname;
}

void User::setStreet(const std::string& street)
{
	if (isBlank(street)) throw std::invalid_argument("Не коректна строка вулиці користувача");
	addres.street = street;
}

void User::setCity(const std::string& city)
{
	if (isBlank(city)) throw std::invalid_argument("Не коректна строка міста користувача");
	addres.city = city;
}

void User::setCountry(const std::string& country)
{
	if (isBlank(country)) throw std::invalid_argument("Не коректна строка країни користувача");
	addres.country = country;
}

void User::setHomeNumber(int num)
{
	if(num <1 ) throw std::invalid_argument("Не коректна значення номеру будинку користувача");
	addres.homeNumber = num;
}

void User::setPhone(const std::string& phone)
{
	if(phone.length() != 13)
		throw std::invalid_argument("Не коректне значення номеру телефону користувача...\nНомер телефону  повинен скадатися  з 13 символів ....");
	if(phone[0] != '+') 
		throw std::invalid_argument("Не коректне значення номеру телефону користувача...\nНомер телефону може починатися з '+' або цифри....");
	for (int i = 1; i < phone.length(); i++)
	   if(!isdigit(static_cast<unsigned char>(phone[i])))
		   throw std::invalid_argument("Не коректне значення номеру телефону користувача\nНомер телефону може складатися лише з цифр....");
	phoneNumber = phone;
}
