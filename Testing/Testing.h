#pragma once
#include <string>
#include <fstream>
#include "mylib.h"
#include <map>
#include "Test.h"
#include "Menu.h"
#include "User.h"
#include <stdio.h>

class Testing
{
private:
	
	const char* admin_file = "data.adm" ;
	const char* tests_file = "tests.tst";
	const char* admin_log_label = "<log_admin>";
	const char* admin_pass_label = "<pass_admin>";
	const char* admin_users_label = "<admin_users>";
	const char* tests_file_category_label = "<test_category>";
	const char* admin_user_label = "<user>";
	
	std::string adminLogin;
	std::string adminPassword;

	std::map<std::string, std::vector<Test*>> tests;
	std::vector<std::string> categorys;

	std::vector<std::string> usersLogins;
	std::map<std::string, User*> users;

	void load_tests();
	void load_users();
	void save();
	void userProcess(const std::string& userLogin);
	void adminProcess();
	void addCategory(const std::string& category);
	bool showTests(const std::string& category) const;
	bool showCategory() const;
	bool showUsers(bool index = false) const;
	
	const std::string& chooseCategory() const;
	const std::string& chooseTest(const std::string& category) const;
	int getTestIndex(const std::string& category) const;
	int getUserIndex() const;
	int getCategoryIndex() const;
	int getQuestionIndex(const Test& test);
	void passTest(Test& test, TestResult& tr);


	/// �������  ���� createQuest
	void createQuestion(Test& instance);
	void loadQuestion(Test& instance);

	/// �������  ���� editTest
	void addQuestion(Test& instance);
	void editQuestion(Test& instance);
	void delQuestion(Test& instance);
	void saveQuestion(Test& instance);

	//������� ����  enterReg 
	 void Enter(Testing& instance);
	 void Registration(Testing& instance);


	//������� ����  adminMenu 
	 void adminStatProc(Testing& instance);
	 void adminTestsEdit(Testing& instance);
	 void adminUserEdit(Testing& instance);

	//������� ���� testsEdit
	 void adminTest(Testing& instance);
	 void adminCat(Testing& instance);
	 void showTestHierarchy(Testing& instance);

	 //������� ���� adminTest
	 void createTest(Testing& instance);
	 void impTest(Testing& instance);
	 void editTest(Testing& instance);
	 void delTest(Testing& instance);
	 void expTest(Testing& instance);
	 void showTest(Testing& instance);

	 //������� ���� adminCat
	 void addCat(Testing& instance);
	 void impCat(Testing& instance);
	 void expCat(Testing& instance);
	 void delCat(Testing& instance);

	 //������� ���� dminUserEdit

	void  addUsr (Testing& instance);
	void  editUsr (Testing& instance);
	void  delUsr (Testing& instance);
	void  showUsr(Testing& instance);
	
public:
	Testing();
	~Testing();
	void start();
};

