#pragma once
#include "Question.h"
class SingleAnswerQuestion: public Question
{
private:
	static constexpr char r_aswer_lable[]  = "<r_aswer>";
	int rightAnswer ;
	void setRightAnswer(const int index);
public:
	SingleAnswerQuestion(): Question(SINGLE_ANSWER_Q), rightAnswer(1) {}
	SingleAnswerQuestion(std::ifstream& ifs): Question(SINGLE_ANSWER_Q) { fromFStream(ifs); };

	void setAnswer() override;
	void toFStream (std::ofstream& ofs) const override;
	void fromFStream(std::ifstream& ifs) override;
	int  answerToQestion() const override;
	std::string answerToStr() const override { return std::string(rightAnswer + "# " + answersVariants[rightAnswer]); };
	
};

