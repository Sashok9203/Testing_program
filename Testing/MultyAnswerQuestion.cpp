#include "MultyAnswerQuestion.h"

void MultyAnswerQuestion::addRightAnswer(const int answerIndex)
{
	if (answerIndex<1 || answerIndex>answersVariants.size()) throw question_invalid_argument("������������ ������ ������ = " + std::to_string(answerIndex) + " ... �� ���� �� 1 �� " + std::to_string(answersVariants.size()));
	for (const int val : rightAnswers)
		if (val == answerIndex) return;
	rightAnswers.push_back(answerIndex);
}

void MultyAnswerQuestion::setAnswer()
{
	Question::setAnswer();
	rightAnswers.clear();
	do
	{
		system("cls");
		std::cout << getString();
		if (rightAnswers.size()) std::cout << answerToStr();
		std::cout << " ������ �������� ������� ������ :";
		int tmp = getValue(1, answersVariants.size());
		if (!isVectorExist(rightAnswers, tmp))
		{
			addRightAnswer(tmp);
			std::cout << " B����� ������ ������..." << std::endl;

			if (answersVariants.size() == rightAnswers.size())
			{
				system("pause>nul");
				break;
			}
			std::cout << " Esc ��������� ...  " << std::endl;
		}
	} while (_getch() != 27);

}

std::string MultyAnswerQuestion::answerToStr() const
{
	std::stringstream ss;
	ss << "\n³�����:" << std::endl;
	for (const int val : rightAnswers)
		ss << "      #" << val << "  " << answersVariants[val - 1] << std::endl;
	return ss.str();
}

int MultyAnswerQuestion::answerToQestion() const
{
	Question::answerToQestion();
	std::vector<int> vtmp;
	float point = (float)questionPoints / rightAnswers.size();
	float result = 0;
	std::cout << getString();
	do
	{
		std::cout << " ������  ������� :";
		int tmp = getValue(1, answersVariants.size());
		if (!isVectorExist(vtmp, tmp))
		{
			vtmp.push_back(tmp);
			std::cout << " B������� ������..." << std::endl;

			if (answersVariants.size() == vtmp.size())
			{
				system("pause>nul");
				break;
			}
			std::cout << " Esc ��������� ...  " << std::endl;
		}
		

	} while (_getch() != 27);

	for (const auto val : vtmp)
		if (isVectorExist(rightAnswers, val)) result += point;
		else result -= point;

	if (result >= 1) return round(result);
	return 1;
}

void MultyAnswerQuestion::toFStream(std::ofstream& ofs) const
{
	Question::toFStream(ofs);
	ofs <<  r_aswers_lable << std::endl;
	for (const int val : rightAnswers)
		ofs << val << std::endl;
	
}

void MultyAnswerQuestion::fromFStream(std::ifstream& ifs)
{
	int temp;
	std::string tmp;
	Question::fromFStream(ifs);
	goToLable(ifs, r_aswers_lable);
	try
	{
		while (ifs >> temp)
		{
			if (ifs.eof())
				throw question_invalid_file_format("̳���  \"" + std::string(r_aswers_lable) + "\" �� ��������");
			if (!ifs)
				throw question_invalid_argument(" ���� ����  \"" + std::string(r_aswers_lable) + "\"");
			 addRightAnswer(temp);
		}
		if(rightAnswers.empty()) throw question_invalid_argument("³����� ������� ���������� �������� ...");
	}
	catch (const question_invalid_argument& ex)
	{
		throw question_invalid_file_format(ex.what());
	}
}
