#pragma once
#include <string>
#include "Test.h"
#include <fstream>
#include "TestingExceptions.h"
class TestResult
{
private:
	static constexpr char tres_lable[]  = "<tres>";
	static constexpr char tname_lable[] = "<tname>";
	static constexpr char tcat_lable[]  = "<tcat>";
	
	bool passed;
	std::string name;
	std::string category;
	int testQuestionCount;
	int rightAnswersCount;
	int points;
	int lastQuestionIndex;
	
public:
	static constexpr char tres_data_lable[] = "<tresdata>";

	TestResult():TestResult("NoName","NoCat", 1) {}
	TestResult(std::ifstream& ifs) { fromFStream(ifs); }
	TestResult(const std::string& name, const std::string& category, int testQuestionCount);
	const std::string& getName() const { return name; }
	void addPoints(int points) { this->points += points; };
	void addRightAnswer() { ++rightAnswersCount; }
	void setTestQuestionCount(int count) { testQuestionCount = count; }
	void setLastQuestionIndex(int index);
	void setCategory(const std::string cat) { category = cat; }
	const std::string& getCategory() const { return category; }
	int getLastQuestionIndex()const { return lastQuestionIndex; }
	void setPassed(bool passed) { this->passed = passed; }
	void setName(const std::string& name) { this->name = name; }
	bool isPassed() const { return passed; }
	void toFStream(std::ofstream& ofs) const;
	int getRating() const;
	float getRightAnswersPercent() const;
	void fromFStream(std::ifstream& ifs);
	void showResult(int index = 0) const;


};

