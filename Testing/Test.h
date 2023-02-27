#pragma once
#include <string>
#include <vector>
#include "Question.h"
#include <fstream>
#include "mylib.h"
#include "TestExceptions.h"
#include "SingleAnswerQuestion.h"
#include "MultyAnswerQuestion.h"

class Test
{
private:
	
	std::string name;
	std::vector<Question*>questions;
	void addQuestion( Question* question) ;

public:
	static constexpr char exp[] = ".test";
	static constexpr char name_lable[] = "<test_name>";
	static constexpr char test_lable[] = "<test>";
	Test():name("NoNameTest") {};
	Test(const std::string& fileName);
	Test(std::ifstream& ifs);
	~Test();

	void addQuestion();
	void delQuestion(int index);
	
	void loadQuestion(std::ifstream& ifs);
	Question& getQuestion(int index);
	void showAll() const;
	const std::string& getName() const { return name; }
	void setName(const std::string& name);
	void loadTest(const std::string& fileName);
	void saveTest(const std::string& fileName = "");
	void toFStream(std::ofstream& ofs) const;
	void fromFStream(std::ifstream& ifs);
	int getQuestCount() const { return (int)questions.size(); }
};

