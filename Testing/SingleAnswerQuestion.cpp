#include "SingleAnswerQuestion.h"


void SingleAnswerQuestion::setRightAnswer(const int answerIndex)
{
	if (answerIndex < 1 || answerIndex > answersVariants.size())
		throw question_invalid_argument("������������ ������ ������ = " + std::to_string(answerIndex) + " ... �� ���� �� 1 �� " + std::to_string(answersVariants.size()));
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
			throw question_invalid_argument(" ���� ����  \"" + std::string(r_aswer_lable) + "\"");
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
	std::cout << " ������ ���������� ������ ������ :";
	setRightAnswer(getValue(1, answersVariants.size()));
	
}

int SingleAnswerQuestion::answerToQestion() const
{
	Question::answerToQestion();
	std::cout << getString();
	std::cout << "���� ������� :";
	if (getValue(1, answersVariants.size()) == rightAnswer) return  questionPoints;
	else return 1;
}











