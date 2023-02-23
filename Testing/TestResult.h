#pragma once
#include <string>
#include "Test.h"
#include <fstream>
#include "TestingExceptions.h"
#include <iomanip>
class TestResult
{
private:
	
	static constexpr char tname_lable[] = "<tname>";
	static constexpr char tcat_lable[]  = "<tcat>";
	static constexpr char tres_data_lable[] = "<tresdata>";
	
	bool passed;
	std::string name;
	std::string category;
	int testQuestionCount;
	int rightAnswersCount;
	int points;
	int nextQuestionIndex;
	
public:
	
	static constexpr char tres_lable[] = "<tres>";
	TestResult():TestResult("NoName","NoCat", 1) {}
	TestResult(std::ifstream& ifs);
	TestResult(const std::string& name, const std::string& category, int testQuestionCount);
	const std::string& getName() const { return name; }
	void addPoints(int points) { this->points += points; };
	void addRightAnswer() { ++rightAnswersCount; }
	void setTestQuestionCount(int count) { testQuestionCount = count; }
	void setNextQuestionIndex(int index);
	void setCategory(const std::string cat) { category = cat; }
	const std::string& getCategory() const { return category; }
	int getNextQuestionIndex()const { return nextQuestionIndex; }
	void setPassed(bool passed) { this->passed = passed; }
	void setName(const std::string& name) { this->name = name; }
	bool isPassed() const { return passed; }
	void toFStream(std::ofstream& ofs) const;
	int getRating() const;
	double getRightAnswersPercent() const;
	void fromFStream(std::ifstream& ifs);
	void showResult(int index = 0) const;
};

