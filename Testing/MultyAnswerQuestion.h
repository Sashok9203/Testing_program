#pragma once
#include "Question.h"
#include <conio.h>
class MultyAnswerQuestion:  public Question
{
private:
	static constexpr char r_aswers_lable[] = "<r_aswers>";
	std::vector<int> rightAnswers;
    void  addRightAnswer(const int answerIndex);
public:
	MultyAnswerQuestion(): Question(MULTI_ANSWER_Q){}
	MultyAnswerQuestion(std::ifstream& ifs): Question(MULTI_ANSWER_Q) { fromFStream(ifs); };

	void setAnswer() override;
	std::string answerToStr() const override ;
	int answerToQestion() const override;
	void toFStream(std::ofstream& ofs) const override;
	void fromFStream(std::ifstream& ifs) override;
	
};

