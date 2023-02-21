#include "SingleAnswerQuestion.h"


void SingleAnswerQuestion::setRightAnswer(const int answerIndex)
{
	if (answerIndex < 1 || answerIndex > answersVariants.size())
		throw question_invalid_argument("недопустимий ≥ндекс в≥дпов≥д≥ = " + std::to_string(answerIndex) + " ... маЇ бути в≥д 1 до " + std::to_string(answersVariants.size()));
	rightAnswer = answerIndex;
}

void SingleAnswerQuestion::toFStream(std::ofstream& ofs) const
{
	Question::toFStream(ofs);
	ofs << r_aswer_lable << std::endl ;
	ofs << rightAnswer << std::endl;
}

void SingleAnswerQuestion::fromFStream(std::ifstream& ifs)
{
	int temp;
	std::string tmp;
	Question::fromFStream(ifs);
	goToLable(ifs, r_aswer_lable);
	try 
	{
		if (!(ifs >> temp))
			throw question_invalid_argument(" п≥сл€ м≥тки  \"" + std::string(r_aswer_lable) + "\"");
		setRightAnswer(temp);
	}
	catch (const question_invalid_argument& ex)
	{
		throw question_invalid_file_format(ex.what());
	}
}

void SingleAnswerQuestion::setAnswer()
{
	Question::setAnswer();
	std::cout << getString();
	std::cout << " ¬вед≥ть правильний вар≥ант в≥дпов≥д≥ :";
	setRightAnswer(getValue(1, answersVariants.size()));
	
}

int SingleAnswerQuestion::answerToQestion() const
{
	Question::answerToQestion();
	std::cout << getString();
	std::cout << "¬аша в≥дпов≥дь :";
	if (getValue(1, answersVariants.size()) == rightAnswer) return  questionPoints;
	else return 1;
}











