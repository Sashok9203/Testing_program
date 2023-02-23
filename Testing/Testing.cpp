#include "Testing.h"

void Testing::addQuestion(Test& instance)
{
	Menu<Test, Testing> editTest(
		" -=  Адміністратор  =-\n         -* Додати питання *-", "Завершити",
		{ {"Ввести",&Testing::createQuestion},
		  {"Завантажити",&Testing::loadQuestion} }, instance, *this);
	editTest.getMenuItem();
	save();
}

void Testing::editQuestion(Test& instance)
{
	int ind = getQuestionIndex(instance);
	Question& quest = instance.getQuestion(ind);
	system("cls");
	std::cout << quest.getString();
	std::cout << "         ------ Змінити ------" << std::endl;
	std::cout << "       [1] Питання" << std::endl;
	std::cout << "       [2] Варіанти відповідей" << std::endl;
	std::cout << "       [3] Правильні відповіді" << std::endl;
	std::cout << "       [4] Завершити" << std::endl;
	int select = getValue(1, 4);
	switch (select)
	{
	case 1:
		quest.setQuestion();
		break;
	case 2:
		quest.setAnswerVariant();
		break;
	case 3:
		quest.setAnswer();
		break;
	default:
		return;
	}
	save();
}

void Testing::delQuestion(Test& instance)
{
	int ind = getQuestionIndex(instance);
	instance.delQuestion(ind);
	std::cout << " Питання видалено....";
	system("pause>nul");
	save();
}

void Testing::createQuestion(Test& instance)
{
	instance.addQuestion();
	save();
}

void Testing::loadQuestion(Test& instance)
{
	std::string tmp = getWord("Введіть імя файлу :");
	std::ifstream ifs(tmp);
	if (!ifs) std::cout << " Не можливо відкрити файл " << tmp;
	instance.loadQuestion(ifs);
	save();
	std::cout << " Питання успішно завантажене з файлу \"" << tmp << "\"...";
	system("pause>nul");
}

void Testing::saveQuestion(Test& instance)
{
	int ind = getQuestionIndex(instance);
	Question& quest = instance.getQuestion(ind);
	std::string exfName = getWord(" Ведіть ім'я файлу в який буде збережено питання : ");
	std::ofstream ofs(exfName);
	if (!ofs)	std::cout << " Помилка при експоті питання в  файл  \"" << exfName << "\"";
	else
	{
		quest.toFStream(ofs);
		ofs.close();
		std::cout << " Питання успішно збережено в файл  \"" << exfName << "\"...";
	}
	system("pause>nul");
}
void Testing::Enter(Testing& instance)
{
	system("cls");
	std::cout << " -= Вхід в систему =-" << std::endl;
	LogPass lp = getLogPas(true);
	if (adminLogin == lp.login && adminPassword == lp.password) adminProcess();
	else if (users.count(lp.login) && lp.password == users[lp.login]->getPassword()) userProcess(lp.login);
	else
	{
		std::cout << "\n Не вірний логін або пароль....";
		system("pause>nul");
	}
}


void Testing::Registration(Testing& instance)
{
	int proc = 1;
	std::string tmp;
	LogPass lp;
	User* user = new User();
	do
	{
		system("cls");
		std::cout << "     -=  Реєстрація нового користувача  =-\n" << std::endl;
		try
		{
			switch (proc)
			{
			case 1:
				tmp = getWord("         Ім'я  : ");
				user->setName(tmp);
				break;
			case 2:
				tmp = getWord("         Прізвище  : ");
				user->setSurname(tmp);
				break;
			case 3:
				tmp = getWord("         Kраїна  : ");
				user->setCountry(tmp);
				break;
			case 4:
				tmp = getString("         Mісто  : ");
				user->setCity(tmp);
				break;
			case 5:
				tmp = getString("         Вулиця  : ");
				user->setStreet(tmp);
				break;
			case 6:
				std::cout << "         Номер будинку : ";
				user->setHomeNumber(getValue(1,1000));
				break;
			case 7:
				tmp = getWord("         Телефон в повному форматі  + і 12 цифр телефону : ");
				user->setPhone(tmp);
				break;
			case 8:
				lp = getLogPas();
				if (lp.login == adminLogin || users.count(lp.login)) throw std::exception(" Логін який ви ввели вже існує....");
				user->setPassword(lp.password);
				user->setLogin(lp.login);
			}
		}
		catch (const std::exception& ex)
		{
			std::wcout << ex.what();
			system("pause>nul");
			continue;
		}
		++proc;
	} while (proc!=9);
	usersLogins.push_back(lp.login);
	users.insert({ lp.login, user });
	std::cout << "         Користувач \"" << lp.login << "\" успішно зареестровані в системі...";
	system("pause>nul");
	save();
}

void Testing::createTest(Testing& instance)

{
	std::string category  = chooseCategory();
	if (category.empty()) return;
	Test* test  = new Test();
	test->setName(getString(" Ведіть ім'я тесту : "));
	Menu<Test,Testing> editTest(" -=  Адміністратор  =-\n         -* Створення тесту *-", "Завершити",
		{ {"Додати питання",&Testing::createQuestion},
		{"Редагувати питання",&Testing::editQuestion},
		{"Видалити питання",&Testing::delQuestion},
		{"Зберегти питання",&Testing::saveQuestion} }, *test,*this);
	editTest.getMenuItem();
	tests[category].push_back(test);
	save();
}

void Testing::impTest(Testing& instance)
{
	const std::string& category = instance.chooseCategory();
	if (category.empty()) return;
	const std::string fileName = getString(" Введіть ім'я файлу : ");
	Test* test = nullptr;
	try {test = new Test(fileName);}
	catch (std::exception& ex)
	{
		delete test;
		std::cout << ex.what();
		std::cout <<" Файл \"" << fileName << "\" не імпортовано...";
		system("pause>nul");
		return;
	}
	instance.tests[category].push_back(test);
	std::cout << " Файл \"" << fileName << "\" імпортовано...";
	system("pause>nul");
	save();
}

void Testing::editTest(Testing& instance)
{
	const std::string& category = instance.chooseCategory();
	if (isBlank(category)) return;
	const INT nameInd = instance.getTestIndex(category);
	if (nameInd<0) return;
	Test* test = tests[category].at(nameInd);
	Menu<Test, Testing> editTest(" -=  Адміністратор  =-\n         -* Редактування тесту *-", "Завершити",
		{ {"Додати питання",&Testing::createQuestion},
		{"Редагувати питання",&Testing::editQuestion},
		{"Видалити питання",&Testing::delQuestion},
		{"Завантажити питання",&Testing::loadQuestion},
		{"Зберегти питання",&Testing::saveQuestion}}, *test, instance);
	editTest.getMenuItem();
}

void Testing::delTest(Testing& instance)
{
	const std::string& category = instance.chooseCategory();
	if (isBlank(category)) return;
	int nameIndex = getTestIndex(category);
	if (nameIndex < 0) return;
	else
	{
		std::string tmp = tests[category].at(nameIndex)->getName();
		delete tests[category].at(nameIndex);
		tests[category].erase(tests[category].begin() + nameIndex);
		std::cout << " Тест \"" << tmp << "\" видалено...";
		system("pause>nul");
	}
	save();
}

void Testing::addCat(Testing& instance)
{
	std::string cat;
	bool isExist = true;
	do
	{
		system("cls");
		cat = getString(" Введіть назву категорії : ");
		if (tests.count(cat))
			std::cout << " Така категорія вже існує...";
		else
		{
			tests.insert({ cat, {} });
			categorys.push_back(cat);
			isExist = false;
			std::cout << " Категорію додано...";
		}
		system("pause>nul");
	} while (isExist);
	save();
}

void Testing::impCat(Testing& instance)
{
	std::string cName;
	std::string cfName = getWord(" Ведіть ім'я файлу з який буде завантажено розділ : ");
	std::ifstream ifs(cfName);
	if (!ifs)
	{
		std::cout << " Не можливо відкрити файл \"" << cfName << "\" ..." ;
		system("pause>nul");
		return;
	}

	if (goToLabel(ifs, tests_file_category_label))
	{
		if (!getFSString(ifs, cName))
		{
			std::cout << " Не вдалося завантажити каталог з файлу \"" << cfName << "\"";
			system("pause>nul");
			return;
		}
		if (!tests.count(cName))
		{
			tests.insert({ cName ,{} });
			categorys.push_back(cName);
			std::cout << " Розділ \"" << cName << "\" додано...." << std::endl;
		}
		while (goToLabel(ifs, Test::test_lable))
		{
			Test* tmp = new Test(ifs);
			bool found = false;
			for (const auto& val : tests[cName])
			{
				if (val->getName() == tmp->getName())
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				tests[cName].push_back(tmp);
				std::cout << " Тест \"" << tmp->getName() << "\" додано...." << std::endl;
			}
			else
			{
				std::cout << " Тест \"" << tmp->getName() << "\" вже існує...." << std::endl;
				delete tmp;
			}
		}
	}
	else std::cout << " Файл \"" << cfName << "\" не містить каталогу для завантаження";
	system("pause>nul");
	save();
}

void Testing::expCat(Testing& instance)
{
	std::string cName = chooseCategory();
	if (isBlank(cName)) return;
	std::string exfName = getWord(" Ведіть ім'я файлу в який буде експортовано розділ : ");
	std::ofstream ofs(exfName);
	if (!ofs)
	{
		std::cout << " Помилка при експоті розділу... \"" << cName << "\" в  файл  \"" << exfName<<"\"";
		system("pause>nul");
		return;
	}
	ofs << tests_file_category_label << std::endl;
	ofs << cName << std::endl;
	for (const auto& val : tests[cName])
		val->toFStream(ofs);
	ofs.close();
	std::cout << " Розділ \"" << cName << "\" експортований в  файл  \"" << exfName << "\"";
	system("pause>nul");
}

void Testing::expTest(Testing& instance)
{
	std::string cName = chooseCategory();
	if (isBlank(cName)) return;
	int ind = getTestIndex(cName);
	if (ind < 0) return;
	std::string tName = tests[cName].at(ind)->getName();
	std::string exfName = getWord(" Ведіть ім'я файлу в який буде експортовано тест : ");
	std::ofstream ofs(exfName);
	if (!ofs)
	{
		std::cout << " Помилка при експоті тесту... \"" << cName << "\" в  файл  \"" << exfName << "\"";
		system("pause>nul");
		return;
	}
	tests[cName].at(ind)->toFStream(ofs);
	ofs.close();
	std::cout << " Тест  \"" << tName << "\" експортований в  файл  \"" << exfName << "\"";
	system("pause>nul");
}

void Testing::showTest(Testing& instance)
{
	system("cls");
	std::string cat = chooseCategory();
	if (cat.empty()) return;
	int index = getTestIndex(cat);
	if (index < 0) return;
	system("cls");
	tests[cat].at(index)->showAll();
	system("pause>nul");
}

void Testing::delCat(Testing& instance)
{
	int catInd = getCategoryIndex();
	if (catInd < 0) return;
	std::string cName = categorys[catInd];
	for (const auto& v : tests[cName])
		delete v;
	tests.erase(cName);
	categorys.erase(categorys.begin() + catInd);
	std::cout << " Розділ   \"" << cName << "\" видалено...";
	system("pause>nul");
	save();
}

void Testing::addUsr(Testing& instance)
{
	Registration(instance);
}

void Testing::editUsr(Testing& instance)
{
	int ind;
	if (ind = getUserIndex(), ind < 0) return;
	Menu<User, Testing> userEdit(
		" -=  Адміністратор  =-\n          -= Редагування \"" + usersLogins[ind] + "\" =-", "Завершити",
		 { {"Змінити дані",     &Testing::editUserData},
		   {"Видалити рез.тестів",&Testing::delUserTRes},
		   {"Показати рез.тестів",&Testing::showUserTRes},
		   {"Показати не завершені тести",&Testing::userNPTestsRes} },
		*users.at(usersLogins[ind]), instance);
	userEdit.getMenuItem();
}

void Testing::delUsr(Testing& instance)
{
	int ind;
	if (ind = getUserIndex(), ind < 0) return;
	users.erase(usersLogins[ind]);
	usersLogins.erase(usersLogins.begin() + ind);
	std::cout << " Користувача видалено из системи....";
	system("pause>nul");
	save();
}

void Testing::showUsr(Testing& instance)
{
	system("cls");
	if (usersLogins.empty())
		std::cout << " Немає зареєстрованих юзерів....";
	else
		for (const auto& val : usersLogins)
			std::cout << users.at(val)->getUserStr() << std::endl;
    system("pause>nul");
}

void Testing::editUserData(User& instance)
{
	int temp,select;
	std::string tmp;
	do
	{
		system("cls");
		std::cout << instance.getUserStr();
		std::cout << "        ------------------------\n" << std::endl;
		std::cout << "          ------ Змінити ------" << std::endl;
		std::cout << "          [1] Ім'я" << std::endl;
		std::cout << "          [2] Прізвище" << std::endl;
		std::cout << "          [3] Країну" << std::endl;
		std::cout << "          [4] Місто" << std::endl;
		std::cout << "          [5] Вулицю" << std::endl;
		std::cout << "          [6] Номер будинку" << std::endl;
		std::cout << "          [7] Номер телефону" << std::endl;
		std::cout << "          [8] Пароль" << std::endl;
		std::cout << "          [9] Логін" << std::endl;
		std::cout << "          [10] Завершити" << std::endl;
	    select = getValue(1, 10);
		switch (select)
		{
		case 1:
			std::cout << " Ім'я користувача : \"" << instance.getFI().name <<"\""<< std::endl;
			instance.setName(getWord(" Введіть нове ім'я : "));
			std::cout << " Ім'я користувача змінено на  \"" << instance.getFI().name << "\"" << std::endl;
			break;
		case 2:
			std::cout << " Прізвище користувача : \"" << instance.getFI().surname << "\"" << std::endl;
			instance.setSurname(getWord(" Введіть нове прізвище : "));
			std::cout << " Прізвище користувача змінено на  \"" << instance.getFI().surname << "\"" << std::endl;

			break;
		case 3:
			std::cout << " Країна користувача : \"" << instance.getAddres().country << "\"" << std::endl;
			instance.setCountry(getString(" Введіть країну : "));
			std::cout << " Країна користувача змінена на  \"" << instance.getAddres().country << "\"" << std::endl;

			break;
		case 4:
			std::cout << " Місто користувача : \"" << instance.getAddres().city << "\"" << std::endl;
			instance.setCity(getString(" Введіть місто : "));
			std::cout << " Місто користувача змінено на  \"" << instance.getAddres().city << "\"" << std::endl;

			break;
		case 5:
			std::cout << " Вулиця користувача : \"" << instance.getAddres().street << "\"" << std::endl;
			instance.setStreet(getString(" Введіть вулицю : "));
			std::cout << " Вулиця користувача змінена на  \"" << instance.getAddres().street << "\"" << std::endl;
			break;
		case 6:
			std::cout << " Номер будинку користувача : \"" << instance.getAddres().homeNumber << "\"" << std::endl;
			std::cout << " Введіть номер будинку : ";
			std::cin >> temp;
			instance.setHomeNumber(temp);
			std::cout << " Номер будинку користувача змінений на  \"" << instance.getAddres().homeNumber << "\"" << std::endl;
			break;
		
		case 7:
			std::cout << " Номер телефону користувача : \"" << instance.getPhone()<< "\"" << std::endl;
			instance.setPhone(getWord(" Введіть номер телефону : "));
			std::cout << " Номер телефону змінений на  \"" << instance.getPhone() << "\"" << std::endl;
			break;
		case 8:
			std::cout << " Пароль користувача : \"" << instance.getPassword() << "\"" << std::endl;
			instance.setPassword(getWord(" Введіть новий пароль : "));
			std::cout << " Проль змінений на  \"" << instance.getPassword() << "\"" << std::endl;
			break;
		case 9:
			std::cout << " Логін користувача : \"" << instance.getlogin() << "\"" << std::endl;
			instance.setLogin(getWord(" Введіть новий логін : "));
			std::cout << " Логін змінений на  \"" << instance.getlogin() << "\"" << std::endl;
			std::cout << " Зміна вступить в силу після перезавантаження программи..." << std::endl;
			break;
		default:
			return;
		}
		save();
		if (select != 10)system("pause>nul");
	} while (select != 10);
	
}

void Testing::delUserTRes(User& instance)
{
	system("cls");
	std::cout << instance.getResStr();
	std::cout << " Оберіть результат тестування : ";
	instance.delResult(getValue(1, instance.getResultsCount())-1);
	std::cout << " Результат тестування видалено ...";
	system("pause>nul");
	save();
}

void Testing::showUserTRes(User& instance)
{
	system("cls");
	std::cout << instance.getResStr();
	system("pause>nul");
}

void Testing::userStat(Testing& instance)
{
	system("cls");
	int ind = getUserIndex();
	system("cls");
	std::string ss;
	User& user = *users.at(usersLogins[ind]);
	ss = user.getStatStr();
	std::cout << ss;
	saveStrToFile("\n Бажаєте зберегти статистику (Tab)?", ss);
}

void Testing::testStat(Testing& instance)
{
	system("cls");
	std::stringstream ss;
	std::string cat = chooseCategory();
	int ind = getTestIndex(cat);
	ss << getTestStat(ind,cat);
	std::cout << ss.str();
	saveStrToFile("\n Бажаєте зберегти статистику (Tab) ?", ss.str());
}

void Testing::catStat(Testing& instance)
{
	system("cls");
	std::stringstream ss;
	std::string cat = chooseCategory();
	ss << getCatStat(cat);
	std::cout << ss.str();
	saveStrToFile("\n Бажаєте зберегти статистику (Tab) ?", ss.str());
}

void Testing::totalTest(Testing& instance)
{
	system("cls");
	std::stringstream ss;
	ss << "      ############## Сумарна статистика ##############\n" << std::endl;
	for (const auto& val : tests)
		ss << getCatStat(val.first);
	ss << "      ################################################\n" << std::endl;
	std::cout << ss.str();
	saveStrToFile("\n Бажаєте зберегти статистику (Tab) ?", ss.str());
}


void Testing::adminTestsEdit(Testing & instance)
{
    Menu<Testing, Testing> testsEdit(
		" -=  Адміністратор  =-\n          -*  Редагування  *-","Завершити",
		{ {"Редагування тестів",&Testing::adminTest},///
		{"Редагувати розділів",&Testing::adminCat},///
		{"Показати тести",&Testing::showTest},
		{"Показати ієрархію тестів",&Testing::showTestHierarchy} },
		 instance,instance);///
	testsEdit.getMenuItem();
}

void Testing::adminStatProc(Testing& instance)
{
	Menu<Testing, Testing> adminStat(
		" -=  Адміністратор  =-\n          --  Статистика  --", "Завершити",
		{ {"По користувачу",&Testing::userStat},
		  {"По тестах",     &Testing::testStat},///
		  {"По розділах",   &Testing::catStat},///
		  {"Загальна",      &Testing::totalTest} },	instance, instance);///
	adminStat.getMenuItem();

}

void Testing::adminUserEdit(Testing& instance)
{
	Menu<Testing, Testing> adminUserEdit(
		" -= Адміністратор = -\n - *Редагування користувачів * -", "Завершити",
	    { { "Додати", & Testing::addUsr },
	      { "Редагувати",&Testing::editUsr },
	      { "Видалити",&Testing::delUsr },
	      { "Показати",&Testing::showUsr } }
	      , instance, instance);
	adminUserEdit.getMenuItem();
}

void Testing::adminLPEdit(Testing& instance)
{
	bool seted = false;
	system("cls");
	do
	{
		system("cls");
		std::cout << " -=  Адміністратор  =-" << std::endl;
		LogPass tmp = getLogPas();
		if (!users.count(tmp.login))
		{
			adminLogin = tmp.login;
			adminPassword = tmp.password;
			std::cout << "\n Логін та пароль адміністратора встановлено";
			system("pause>nul");
			save();
			seted = true;
		}
		else
		{
			std::cout << " Такий логін вже існує в системі ....";
			system("pause>nul");
		}
	} while (!seted);
}

void Testing::load_tests()
{
	std::string tmpCat,tmp;
	std::ifstream ifs(tests_file);
	while (goToLabel(ifs, tests_file_category_label))
	{
		if (getFSString(ifs, tmpCat)) addCategory(tmpCat);
		else return;
		
		while (goToNextLabel(ifs, Test::test_lable))
		{
			Test* test = nullptr;
			try	{test = new Test(ifs);}
			catch (const std::exception& ex)
			{
				std::cout << ex.what()  << std::endl;;
				system("pause>nul");
				continue;
			}
			tests[tmpCat].push_back(test);
		}
    }
	ifs.close();
}

void Testing::load_users()
{
	
	std::ifstream ifs(admin_file);
	if (goToLabel(ifs, admin_users_label))
	{
		while (goToLabel(ifs, admin_user_label))
		{
			User* user = nullptr;
			try	{ user = new User(ifs);	}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
				system("pause>nul");
				delete user;
				continue;
			}	
			usersLogins.push_back(user->getlogin());
			users.insert({ user->getlogin(),user });
		}
	}
	else throw invalid_file_format("Мітка " + std::string(admin_users_label)
		+ " не знайдена ");
	ifs.close();
}

void Testing::save()
{
	std::ofstream ofs(admin_file);
	if (!ofs) throw std::exception(("Не можливо відкрити файл " + std::string(admin_file)).c_str());
	ofs << admin_log_label << std::endl;
	ofs << idcrypt(adminLogin) << std::endl;
	ofs << admin_pass_label << std::endl;
	ofs << idcrypt(adminPassword) << std::endl;
	ofs << admin_users_label << std::endl;
	for (auto const& val : users)
	{
		ofs << admin_user_label << std::endl;
		val.second->toFStream(ofs);
	}
	ofs.close();

	ofs.open(tests_file);
	if (!ofs) throw std::exception(("Не можливо відкрити файл " + std::string(tests_file)).c_str());
	for (auto const& val : tests)
	{
		ofs << tests_file_category_label << std::endl;
		ofs << val.first << std::endl;
		for (auto& q : val.second)
			 q->toFStream(ofs);
	}
	ofs.close();
}



Testing::Testing()
{
	std::string tmp;
	if (!isFileExist(tests_file))
	{
		std::ofstream file(tests_file);
		file << tests_file_category_label << std::endl;
		file.close();
	}
	if (isFileExist(admin_file))
	{
		try
		{
			if (!getFWord(admin_file, admin_pass_label, tmp)) throw std::exception("Помилка завантаження пароля адміністратора");
			adminPassword = idcrypt(tmp);
			if (!getFWord(admin_file, admin_log_label, tmp)) throw std::exception("Помилка завантаження логіна адміністратора");
			adminLogin = idcrypt(tmp);
			load_tests();
			load_users();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
			system("pause>nul");
		}
		
	}
	else
	{
		adminLPEdit(*this);
	}
}

Testing::~Testing()
{
	for (auto& val : tests)
		for (auto& v : val.second)
			delete v;
	for (auto& val : users)
				delete val.second;
}


void Testing::userProcess(const std::string& userLogin)
{
	system("cls");
	Menu<User, Testing> userMenu(" -= " + users[userLogin]->getFI().name + "  " + users[userLogin]->getFI().surname + " =-", "Вихід",
								 { {"Пройти тест",    &Testing::userPassTest},
								   {"Результати тестів",&Testing::userTestsRes},
								   {"Незавершені тести",&Testing::userNPTestsRes},
								  { "Змінити особисті дані",&Testing::editUserData } },
								  *users[userLogin], *this);
    userMenu.getMenuItem();
}

void Testing::adminProcess()
{
	system("cls");
	Menu<Testing, Testing> adminMenu(" -=  Адміністратор  =-","Вихід",
		{ {"Статистика",&Testing::adminStatProc},
		{"Управління тестами",&Testing::adminTestsEdit},
		{"Управління користувачами",&Testing::adminUserEdit},
        {"Зміна логіна і пароля",&Testing::adminLPEdit}},*this, * this);
	adminMenu.getMenuItem();
}

void Testing::userPassTest(User& instance)
{
	system("cls");
	std::string cat = chooseCategory();
	int testInd = getTestIndex(cat);
	if (testInd < 0) return;
	Test* test = tests[cat].at(testInd);
	TestResult* tPtr = nullptr;
	TestResult tRes;
	bool exist = false;
	for (int i = 0; i < instance.getResultsCount(); i++)
		if (test->getName() == instance.getTestResult(i).getName())
		{
			tPtr = &instance.getTestResult(i);
			exist = true;
			break;
		}
	if (tPtr && tPtr->isPassed())
	{
		std::cout << " Цей тест вже пройдений....";
		system("pause>nul");
		return;
	}
	if (!tPtr)
	{
		tRes.setCategory(cat);
		tPtr = &tRes;
	}
	passTest(*test, *tPtr);
	if (!exist) instance.addResult(*tPtr);
	save();
}

void Testing::userTestsRes(User& instance)
{
	showUserTRes(instance);
	
}

void Testing::userNPTestsRes(User& instance)
{
	system("cls");
	std::cout << instance.getNPResStr();
	system("pause>nul");
}

void Testing::addCategory(const std::string& category)
{
	if(isBlank(category)) throw std::invalid_argument(" Назва категорії не може бути пустою");
	if (!tests.count(category))
	{
		tests.insert({ category, {} });
		categorys.push_back(category);
	}
}

void Testing::adminTest(Testing& instance)
{
	Menu<Testing, Testing> testsEdit(
		" -=  Адміністратор  =-\n         -*  Редагування тестів  *-", "Завершити",
		{ {"Cтворити",&Testing::createTest},///
		  {"Редагувати",&Testing::editTest},///
		  {"Видалити",&Testing::delTest},///
		  {"Імпортувати",&Testing::impTest},////
		  {"Експортувати",&Testing::expTest}, }, instance, instance);///
	testsEdit.getMenuItem();
}

void Testing::adminCat(Testing& instance)
{
	Menu<Testing, Testing> testsEdit(
		" -=  Адміністратор  =-\n          -* Редагування розділів *-", "Завершити",
		{{"Додати",&Testing::addCat},///
		{"Видалити",&Testing::delCat},///
		{"Імпортувати",&Testing::impCat},///
		{"Експортувати",&Testing::expCat},}, instance, instance);///
	testsEdit.getMenuItem();
}

void Testing::showTestHierarchy(Testing& instance)
{
	system("cls");
	if (tests.empty())
	{
		std::cout << "        Тести відсутні" << std::endl;
		system("pause>nul");
		return ;
	}
	std::cout << "                      -= Тести =-\n" << std::endl;
	for (auto const& val : tests)
	{
		std::cout << "       " << "*" << val.first <<"*"<< std::endl;
		if (val.second.empty())
		{
			std::cout << "          Тести відсутні..." << std::endl;
			continue;
		}
		for (auto const& q : val.second)
			std::cout << "             " << q->getName() << std::endl;
		std::cout  << std::endl;
	}
	system("pause>nul");
}

bool Testing::showTests(const std::string& category) const
{
    if (!tests.count(category)) throw std::invalid_argument(" Не існує такої категорії");
	int ind = 1;
	if (tests.at(category).empty())
	{
		std::cout << "     Тести відсутні..." << std::endl;
		system("pause>nul");
		return false;
	}
	for (const auto& val : tests.at(category))
	{
		std::cout << "     [" << ind << "] " << val->getName() << std::endl;
		++ind;
	}
	return true;
}

bool Testing::showCategory() const
{
	if (categorys.empty())
	{
		std::cout << "     Категорії відсутні..." << std::endl;
		system("pause>nul");
		return false;
	}
	int ind = 1;
	for (const auto& val : categorys)
	{
		std::cout << "     [" << ind << "] " << val << std::endl;
		++ind;
	}
	return true;
}

bool Testing::showUsers() const
{
	system("cls");
	if (usersLogins.empty())
	{
		std::cout << " Немає зареєстрованих юзерів....";
		system("pause>nul");
		return false;
	}
	int ind = 1;
	for (const auto& val : usersLogins)
	{
    	std::cout<<users.at(val)->getSUserInfo(ind);
		ind++;
	}
	return true;
}

const std::string& Testing::chooseTest(const std::string& category) const
{
	int sel = getTestIndex(category);
	if (sel>=0) return tests.at(category).at(sel)->getName();
	else return std::string();
}

int Testing::getTestIndex(const std::string& category) const
{
	system("cls");
	int sel;
	std::cout << " Оберіть тест " << std::endl;
	try
	{
		if (showTests(category))
			sel = getValue(1, tests.at(category).size());
		else return -1;
	}
	catch (std::invalid_argument& ex)
	{
		std::cout << ex.what();
		return -1;
	}
	return sel - 1;
}

int Testing::getUserIndex() const
{
	if (showUsers())
	{
		std::cout << " Оберіть користувача : ";
		return getValue(1, usersLogins.size()) - 1;
	}
	return -1;
}

int Testing::getCategoryIndex() const
{
	system("cls");
	int sel;
	std::cout << " Оберіть категорію " << std::endl;
	if (showCategory())
		sel = getValue(1, categorys.size());
	else return -1;
	return sel - 1;
}

int Testing::getQuestionIndex(const Test& test)
{
	system("cls");
	test.showAll();
	std::cout << " Введіть індекс тесту : ";
	return getValue(1,test.getQuestCount()) - 1;
}

void Testing::passTest(Test& test, TestResult& tr)
{
	if (tr.getName() == "NoName")
	{
		tr.setName(test.getName());
		tr.setTestQuestionCount(test.getQuestCount());
	}
	
	for (int i = tr.getNextQuestionIndex() ; i < test.getQuestCount(); i++)
	{
		system("cls");
		const Question* q = &test.getQuestion(i);
		std::cout << "          -= "<<test.getName() << " =-"<< std::endl;
		std::cout << "                 Питання " << i + 1 << "/" << test.getQuestCount() << std::endl << std::endl;
		int points = q->answerToQestion();
		if (points == 12) tr.addRightAnswer();
		tr.addPoints(points);
		tr.setNextQuestionIndex(i+1);
		std::cout << " Відповідь прийнята..." << std::endl;
		if (i != test.getQuestCount() - 1)
		{
			std::cout << " Для продовження натисніть будь яку клавішу...Esc для завершення." << std::endl;
			if (_getch() == 27)
			{
				system("cls");
				std::cout << " Тест перервано...можете подовжити в зручний для вас час...." << std::endl;
				std::cout << tr.getResStr();
				system("pause>nul");
				return;
			}
		}
		else
		{
			system("pause>nul");
			break;
		}
	}
	system("cls");
	tr.setPassed(true);
	std::cout << " Тест завершено ..." << std::endl;
    std::cout << tr.getResStr();
	system("pause>nul");
}

std::string Testing::getTestStat(int ind, const std::string& cat) const
{
	if (!tests.count(cat) || ind < 0 || ind >= tests.at(cat).size()) throw std::exception("  Невірний аргумент функції");
	std::stringstream ss;
	int averRating = 0, startTestCount = 0, passTestCount = 0;
	double averRAnsverRepcent = 0;
	std::map<User*, TestResult> tmp;
	system("cls");
	std::string tName = tests.at(cat).at(ind)->getName();
	for (const auto& val : users)
	{
		for (int i = 0; i < val.second->getResultsCount(); i++)
		{
			if (val.second->getTestResult(i).getName() == tName)
			{
				tmp.insert({ val.second ,val.second->getTestResult(i) });
				startTestCount++;
				if (val.second->getTestResult(i).isPassed())
				{
					averRating += val.second->getTestResult(i).getRating();
					averRAnsverRepcent += val.second->getTestResult(i).getRightAnswersPercent();
					passTestCount++;
				}
			}
		}
	}
	averRAnsverRepcent = (averRAnsverRepcent != 0) ? averRAnsverRepcent /= passTestCount : 0;
	averRating = (passTestCount == 0) ? 0 : round((float)averRating / (float)passTestCount);
	ss << "          --------------  Тест  --------------" << std::endl;
	ss << "          Назва               : " << tName << std::endl;
	ss << "          Розділ              : " << cat << std::endl;
	ss << "          Середня оціка       : " << averRating << std::endl;
	ss << "          Кількість пр.відп.  : " << std::fixed << std::setprecision(2) << averRAnsverRepcent << " %" << std::endl;
	ss << "          Розочали  тест      : " << startTestCount << std::endl;
	ss << "          Завершили тест      : " << passTestCount << std::endl;
	ss << "          ------------------------------------" << std::endl << std::endl;
	ss << "          ------------------------------------" << std::endl;
	for (const auto& val : tmp)
	{
		ss << val.first->getShortStatStr() << std::endl;
		ss << val.second.getResStr() << std::endl;
		ss << "           ------------------------------------" << std::endl << std::endl;
	}
	return ss.str();
}

std::string Testing::getCatStat(const std::string& cat) const
{
	if (!tests.count(cat)) throw std::exception("  Невірний аргумент функції");
	std::stringstream ss;
	ss << "    -=-=-=-=-=-=-= Розділ " << cat << " =-=-=-=-=-=-\n" << std::endl;
	for (int i = 0; i < tests.at(cat).size(); i++)
	{

		ss << getTestStat(i, cat);
		ss << "         *****************************************\n" << std::endl;
	}
	return ss.str();
}

const std::string& Testing::chooseCategory() const
{
	
	int sel = getCategoryIndex();
	if (sel >= 0) return categorys[sel];
	else return std::string();
}

void Testing::start()
{	
	Menu<Testing,Testing> enterReg(
		    "Программа тестування","Завершити",
			{ {"Вхід",&Testing::Enter},
			{"Реєстрація",&Testing::Registration} }, 
		    *this,* this);
	enterReg.getMenuItem();
	save();
}
