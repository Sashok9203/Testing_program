#include "Testing.h"

void Testing::addQuestion(Test& instance)
{
	Menu<Test, Testing> editTest(" -=  ������������  =-\n         -* ������ ������� *-", "���������",
								 { {"������",&Testing::createQuestion},
								 {"�����������",&Testing::loadQuestion},
								 }, instance, *this);
	editTest.getMenuItem();
	save();
}

void Testing::editQuestion(Test& instance)
{
	int ind = getQuestionIndex(instance);
	Question& quest = instance.getQuestion(ind);
	system("cls");
	std::cout << quest.getString();
	std::cout << "    ------ ������ ------" << std::endl;
	std::cout << "    [1] �������" << std::endl;
	std::cout << "    [2] ������� ��������" << std::endl;
	std::cout << "    [3] ��������� ������" << std::endl;
	std::cout << "    [4] ���������" << std::endl;
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
	std::cout << " ������� ��������....";
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
	std::string tmp = getWord("������ ��� ����� :");
	std::ifstream ifs(tmp);
	if (!ifs) std::cout << " �� ������� ������� ���� " << tmp;
	instance.loadQuestion(ifs);
	save();
	std::cout << " ������� ������ ����������� � ����� \"" << tmp << "\"...";
	system("pause>nul");
}

void Testing::saveQuestion(Test& instance)
{
	int ind = getQuestionIndex(instance);
	Question& quest = instance.getQuestion(ind);
	std::string exfName = getWord(" ����� ��'� ����� � ���� ���� ��������� ������� : ");
	std::ofstream ofs(exfName);
	if (!ofs)	std::cout << " ������� ��� ������ ������� �  ����  \"" << exfName << "\"";
	else
	{
		quest.toFStream(ofs);
		ofs.close();
		std::cout << " ������� ������ ��������� � ����  \"" << exfName << "\"...";
	}
	system("pause>nul");
}
void Testing::Enter(Testing& instance)
{
	system("cls");
	std::cout << " -= ���� � ������� =-" << std::endl;
	LogPass lp = getLogPas(true);
	if (adminLogin == lp.login && adminPassword == lp.password) adminProcess();
	else if (users.count(lp.login) && lp.password == users[lp.login]->getPassword()) userProcess(lp.login);
	else
	{
		std::cout << "\n �� ����� ���� ��� ������....";
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
		std::cout << "     -=  ��������� ������ �����������  =-\n" << std::endl;
		try
		{
			switch (proc)
			{
			case 1:
				tmp = getWord("         ��'�  : ");
				user->setName(tmp);
				break;
			case 2:
				tmp = getWord("         �������  : ");
				user->setSurname(tmp);
				break;
			case 3:
				tmp = getWord("         K����  : ");
				user->setCountry(tmp);
				break;
			case 4:
				tmp = getString("         M����  : ");
				user->setCity(tmp);
				break;
			case 5:
				tmp = getString("         ������  : ");
				user->setCity(tmp);
				break;
			case 6:
				std::cout << "         ����� ������� : ";
				user->setHomeNumber(getValue(1,1000));
				break;
			case 7:
				tmp = getWord("         ������� � ������� ������  (+38) : ");
				user->setPhone(tmp);
				break;
			case 8:
				lp = getLogPas();
				if (lp.login == adminLogin || users.count(lp.login)) throw std::exception(" ���� ���� �� ����� ��� ����....");
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
	std::cout << "         ���������� \"" << lp.login << "\" ������ ������������� � ������...";
	system("pause>nul");
	save();
}

void Testing::createTest(Testing& instance)

{
	std::string category  = chooseCategory();
	if (category.empty()) return;
	Test* test  = new Test();
	test->setName(getString(" ����� ��'� �����"));
	Menu<Test,Testing> editTest(" -=  ������������  =-\n         -* ��������� ����� *-", "���������",
		{ {"������ �������",&Testing::createQuestion},
		{"���������� �������",&Testing::editQuestion},
		{"�������� �������",&Testing::delQuestion},
		{"�������� �������",&Testing::saveQuestion} }, *test,*this);
	editTest.getMenuItem();
	tests[category].push_back(test);
	save();
}

void Testing::impTest(Testing& instance)
{
	const std::string& category = instance.chooseCategory();
	if (category.empty()) return;
	const std::string fileName = getString(" ������ ��'� ����� : ");
	try 
	{
		instance.tests[category].push_back(new Test(fileName));
		std::cout << " ���� " << fileName << " �����������...";
		system("pause>nul");
	}
	catch (test_invalid_argument& ex)
	{
		std::cout << ex.what();
		system("pause>nul");
	}
	save();
}

void Testing::editTest(Testing& instance)
{
	const std::string& category = instance.chooseCategory();
	if (isBlank(category)) return;
	const INT nameInd = instance.getTestIndex(category);
	if (nameInd<0) return;
	Test* test = tests[category].at(nameInd);
	Menu<Test, Testing> editTest(" -=  ������������  =-\n         -* ������������ ����� *-", "���������",
		{ {"������ �������",&Testing::createQuestion},
		{"���������� �������",&Testing::editQuestion},
		{"�������� �������",&Testing::delQuestion},
		{"����������� �������",&Testing::loadQuestion},
		{"�������� �������",&Testing::saveQuestion}}, *test, instance);
	editTest.getMenuItem();
	save();
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
		std::cout << " ���� \"" << tmp << "\" ��������...";
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
		cat = getString(" ������ ����� ������� : ");
		if (tests.count(cat))
			std::cout << " ���� �������� ��� ����...";
		else
		{
			tests.insert({ cat, {} });
			categorys.push_back(cat);
			isExist = false;
			std::cout << " �������� ������...";
		}
		system("pause>nul");
	} while (isExist);
	save();
}

void Testing::impCat(Testing& instance)
{
	std::string cName;
	std::string cfName = getWord(" ����� ��'� ����� � ���� ���� ����������� ����� : ");
	std::ifstream ifs(cfName);
	if (!ifs)
	{
		std::cout << " �� ������� ������� ���� \"" << cfName << "\" ..." ;
		system("pause>nul");
		return;
	}

	if (goToLable(ifs, tests_file_category_label))
	{
		if (!getFSString(ifs, cName))
		{
			std::cout << " �� ������� ����������� ������� � ����� \"" << cfName << "\"";
			system("pause>nul");
			return;
		}
		if (!tests.count(cName))
		{
			tests.insert({ cName ,{} });
			std::cout << " ����� \"" << cName << "\" ������...." << std::endl;
		}
		while (goToLable(ifs, Test::name_lable))
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
				std::cout << " ���� \"" << tmp->getName() << "\" ������...." << std::endl;
			}
			else
			{
				std::cout << " ���� \"" << tmp->getName() << "\" ��� ����...." << std::endl;
				delete tmp;
			}
		}
	}
	else std::cout << " ���� \"" << cfName << "\" �� ������ �������� ��� ������������";
	system("pause>nul");
	save();
}

void Testing::expCat(Testing& instance)
{
	std::string cName = chooseCategory();
	if (isBlank(cName)) return;
	std::string exfName = getWord(" ����� ��'� ����� � ���� ���� ������������ ����� : ");
	std::ofstream ofs(exfName);
	if (!ofs)
	{
		std::cout << " ������� ��� ������ ������... \"" << cName << "\" �  ����  \"" << exfName<<"\"";
		system("pause>nul");
		return;
	}
	ofs << tests_file_category_label << std::endl;
	ofs << cName << std::endl;
	for (const auto& val : tests[cName])
		val->toFStream(ofs);
	ofs.close();
	std::cout << " ����� \"" << cName << "\" ������������� �  ����  \"" << exfName << "\"";
	system("pause>nul");
}

void Testing::expTest(Testing& instance)
{
	std::string cName = chooseCategory();
	if (isBlank(cName)) return;
	int ind = getTestIndex(cName);
	if (ind < 0) return;
	std::string tName = tests[cName].at(ind)->getName();
	std::string exfName = getWord(" ����� ��'� ����� � ���� ���� ������������ ���� : ");
	std::ofstream ofs(exfName);
	if (!ofs)
	{
		std::cout << " ������� ��� ������ �����... \"" << cName << "\" �  ����  \"" << exfName << "\"";
		system("pause>nul");
		return;
	}
	tests[cName].at(ind)->toFStream(ofs);
	ofs.close();
	std::cout << " ����  \"" << tName << "\" ������������� �  ����  \"" << exfName << "\"";
	system("pause>nul");
}

void Testing::showTest(Testing& instance)
{
	system("cls");
	std::string cat = chooseCategory();
	if (cat.empty()) return;
	int index = getTestIndex(cat);
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
	std::cout << " �����   \"" << cName << "\" ��������...";
	system("pause>nul");
	save();
}

void Testing::addUsr(Testing& instance)
{
	Registration(instance);
}

void Testing::editUsr(Testing& instance)
{
	/*int ind;
	if (ind = getUserIndex(), ind < 0) return;
	Menu<User, Testing> testsEdit(" -=  ������������  =-\n          -*  ����������� �����������  *-", "���������",
									 { {"������ ���� ",&Testing::editUser},
									 {"�������� ���.�����",&Testing::delTRes},
									 {"�������� ���.�����",&Testing::showTRes} }, *users.at(usersLogins[ind]), instance);
	testsEdit.getMenuItem();*/
}

void Testing::delUsr(Testing& instance)
{
	int ind;
	if (ind = getUserIndex(), ind < 0) return;
	users.erase(usersLogins[ind]);
	usersLogins.erase(usersLogins.begin() + ind);
	std::cout << " ����������� �������� �� �������....";
	system("pause>nul");
}

void Testing::showUsr(Testing& instance)
{
	bool showUsers();
}


void Testing::adminTestsEdit(Testing & instance)
{
    Menu<Testing, Testing> testsEdit(" -=  ������������  =-\n          -*  �����������  *-","���������",
		{ {"����������� �����",&Testing::adminTest},///
		{"���������� ������",&Testing::adminCat},///
		{"�������� �������� �����",&Testing::showTestHierarchy} }, instance,instance);///
	testsEdit.getMenuItem();
	
}

void Testing::adminStatProc(Testing& instance)
{
	std::string cat = chooseCategory();
	int index = getTestIndex(cat);
	Test& test = *tests[cat].at(index);
	TestResult tr;
	tr.setCategory(cat);
	passTest(test, tr);
}

void Testing::adminUserEdit(Testing& instance)
{
	Menu<Testing, Testing> adminUserEdit(" -= ������������ = -\n - *����������� ������������ * -", "���������",
	{ { "������", & Testing::addUsr },
	 { "����������",&Testing::editUsr },
	 { "��������",&Testing::delUsr },
	 { "��������",&Testing::showUsr } }, instance, instance);
}






void Testing::load_tests()
{
	std::string tmpCat,tmp;
	std::ifstream ifs(tests_file);
	while (goToLable(ifs, tests_file_category_label))
	{
		if (getFSString(ifs, tmpCat)) addCategory(tmpCat);
		else return;
		while (goToLable(ifs, Test::name_lable))
			tests[tmpCat].push_back(new Test(ifs));
    }
	ifs.close();
}

void Testing::load_users()
{
	
	std::ifstream ifs(admin_file);
	if (goToLable(ifs, admin_users_label))
	{
		while (goToLable(ifs, admin_user_label))
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
	else throw invalid_file_format("̳��� " + std::string(admin_users_label)
		+ " �� �������� ");
	ifs.close();
}







void Testing::save()
{
	std::ofstream ofs(admin_file);
	if (!ofs) throw std::exception(("�� ������� ������� ���� " + std::string(admin_file)).c_str());
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
	if (!ofs) throw std::exception(("�� ������� ������� ���� " + std::string(tests_file)).c_str());
	for (auto const& val : tests)
	{
		ofs << tests_file_category_label << std::endl;
		ofs << val.first << std::endl;
		for (auto& q : val.second)
			 q->toFStream(ofs);
	}
	ofs.close();
}

void Testing::userProcess(const std::string& userLogin)
{
	system("cls");
	users[userLogin]->show(12);
	system("pause>nul");
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
		if (!getFWord(admin_file, admin_pass_label, tmp)) throw std::exception("������� ������������ ������ �������������");
		adminPassword = idcrypt(tmp);
		if (!getFWord(admin_file, admin_log_label, tmp)) throw std::exception("������� ������������ ����� �������������");
		adminLogin = idcrypt(tmp);
		load_tests();
		load_users();
	}
	else
	{
		std::cout << " -=  ������������  =-" << std::endl;
		LogPass tmp = getLogPas();
		adminLogin = tmp.login;
		adminPassword = tmp.password;
		
		std::cout << "\n ���� �� ������ ������������� �����������\n ��������� ������ �� ������...";
		system("pause>nul");
	}
}

Testing::~Testing()
{
	save();
	for (auto& val : tests)
		for (auto& v : val.second)
			delete v;
	for (auto& val : users)
				delete val.second;
}


void Testing::adminProcess()
{
	Menu<Testing, Testing> adminMenu(" -=  ������������  =-","�����",
		{ {"����������",&Testing::adminStatProc},
		{"��������� �������",&Testing::adminTestsEdit},
		{"��������� �������������",&Testing::adminUserEdit} },*this, * this);

	system("cls");
	std::cout << " �� ������ �� ������������";
	system("pause>nul");
	system("cls");
	adminMenu.getMenuItem();
}





void Testing::addCategory(const std::string& category)
{
	if(isBlank(category)) throw std::invalid_argument(" ����� ������� �� ���� ���� ������");
	if (!tests.count(category))
	{
		tests.insert({ category, {} });
		categorys.push_back(category);
	}
}

void Testing::adminTest(Testing& instance)
{
	Menu<Testing, Testing> testsEdit(" -=  ������������  =-\n         -*  ����������� �����  *-", "���������",
									 { {"C�������",&Testing::createTest},///
									 {"����������",&Testing::editTest},///
									 {"��������",&Testing::delTest},///
									 {"��������",&Testing::showTest},
									 {"�����������",&Testing::impTest},////
									 {"������������",&Testing::expTest}, }, instance, instance);///
	testsEdit.getMenuItem();
}

void Testing::adminCat(Testing& instance)
{
	Menu<Testing, Testing> testsEdit(" -=  ������������  =-\n          -* ����������� ������ *-", "���������",
									 { 
									 {"������",&Testing::addCat},///
									 {"��������",&Testing::delCat},///
									 {"�����������",&Testing::impCat},///
									 {"������������",&Testing::expCat},}, instance, instance);///
	testsEdit.getMenuItem();
}

void Testing::showTestHierarchy(Testing& instance)
{
	system("cls");
	if (tests.empty())
	{
		std::cout << "   ����� �������" << std::endl;
		system("pause>nul");
		return ;
	}
	std::cout << "    -= ����� =-" << std::endl;
	for (auto const& val : tests)
	{
		std::cout << "  " << "*" << val.first << std::endl;
		if (val.second.empty())
		{
			std::cout << "     ����� �������..." << std::endl;
			continue;
		}
		for (auto const& q : val.second)
			std::cout << "     " << q->getName() << std::endl;
	}
	system("pause>nul");
}

bool Testing::showTests(const std::string& category) const
{
	if (!tests.count(category)) throw std::invalid_argument(" �� ���� ���� �������");
	int ind = 1;
	if (tests.at(category).empty())
	{
		std::cout << "     ����� �������..." << std::endl;
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
		std::cout << "     ������� �������..." << std::endl;
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

bool Testing::showUsers(bool index) const
{
	system("cls");
	if (usersLogins.empty())
	{
		std::cout << " ���� ������������� �����....";
		system("pause>nul");
		return false;
	}
	int ind = 1;
	for (const auto& val : usersLogins)
	{
		if (index) users.at(val)->show(ind);
		else users.at(val)->show();
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
	std::cout << " ������ test " << std::endl;
	try
	{
		if (showTests(category))
			sel = getValue(1, categorys.size());
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
	if (showUsers(true))
	{
		std::cout << " ������ ����������� : ";
		return getValue(1, usersLogins.size()) - 1;
	}
	return -1;
}

int Testing::getCategoryIndex() const
{
	system("cls");
	int sel;
	std::cout << " ������ �������� " << std::endl;
	if (showCategory())
		sel = getValue(1, categorys.size());
	else return -1;
	return sel - 1;
}

int Testing::getQuestionIndex(const Test& test)
{
	system("cls");
	test.showAll();
	std::cout << " ������ ������ ����� : ";
	return getValue(1,test.getQuestCount()) - 1;
}

void Testing::passTest(Test& test, TestResult& tr)
{
	if (tr.getName() == "NoName")
	{
		tr.setName(test.getName());
		tr.setTestQuestionCount(test.getQuestCount());
	}
	
	for (int i = tr.getLastQuestionIndex(); i < test.getQuestCount(); i++)
	{
		system("cls");
		const Question* q = &test.getQuestion(i);
		std::cout << "          -= "<<test.getName() << " =-"<< std::endl;
		std::cout << "                 ������� " << i + 1 << "/" << test.getQuestCount() << std::endl << std::endl;
		int points = q->answerToQestion();
		if (points == 12) tr.addRightAnswer();
		tr.addPoints(points);
		tr.setLastQuestionIndex(i);
		std::cout << " ³������ ��������..." << std::endl;
		if (i != test.getQuestCount() - 1)
		{
			std::cout << " ��� ����������� ��������� ���� ��� ������...Esc ��� ����������." << std::endl;
			if (_getch() == 27)
			{
				system("cls");
				std::cout << " ���� ���������...������ ��������� � ������� ��� ��� ���...." << std::endl;
				tr.showResult();
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
	std::cout << " ���� ��������� ..." << std::endl;
	tr.showResult();
	system("pause>nul");
}

const std::string& Testing::chooseCategory() const
{
	
	int sel = getCategoryIndex();
	if (sel >= 0) return categorys[sel];
	else return std::string();
}

void Testing::start()
{	
	Menu<Testing,Testing> enterReg("��������� ����������","���������",
			{ {"����",&Testing::Enter},
			{"���������",&Testing::Registration} },*this,* this);
	enterReg.getMenuItem();
	save();
}
