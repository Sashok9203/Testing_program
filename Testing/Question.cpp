#include "Question.h"

void Question::set_question(const std::string& question)
{
	if (isBlank(question)) throw question_invalid_argument("��������� �� ���� ���������� � ������...");
	this->question = question;
}
void Question::addAnswer(const std::string& answer)
{
	if (isBlank(answer)) throw question_invalid_argument("��������� �� ���� ���������� � ������ ... ");
	answersVariants.push_back(answer);
}

void Question::delAnswer(const int index)
{
	if (index<1 || index>answersVariants.size()) throw question_invalid_argument("������������ ������ ������ = " + std::to_string(index) + " ... �� ���� �� 1 �� " + std::to_string(answersVariants.size()));
	answersVariants.erase(answersVariants.begin() + index - 1);
}

void Question::replaceAnswer(const std::string answer, const int index)
{
	if (index<1 || index>answersVariants.size()) throw question_invalid_argument("������������ ������ ������ = " + std::to_string(index) + " ... �� ���� �� 1 �� " + std::to_string(answersVariants.size()));
	if (isBlank(answer)) throw question_invalid_argument("��������� �� ���� ���������� � ������ ... ");
	answersVariants[index - 1] = answer;
}
int Question::answerToQestion() const
{
	if (answersVariants.empty()) throw question_invalid_argument("��������� ���� ������� ... ������� ������ ������....");
	return 0;
}
void Question::setAnswer()
{
	if (answersVariants.empty()) throw question_invalid_argument("���������� ������� �� ������� ... ������� ������ ������....");
}
void Question::setAnswerVariant()
{
	int select;
	bool error = false;
	do
	{
		system("cls");
		if (!answersVariants.empty() && !error)
		{
			
			std::cout << getString();
			std::cout << " ------------------" << std::endl;
			std::cout << "   [1] ������" << std::endl;
			std::cout << "   [2] �������" << std::endl;
			std::cout << "   [3] ��������" << std::endl;
			std::cout << "   [4] ���������" << std::endl;
			select = getValue(1, 4);
		}
		else if (!error) select = 1;
		else
		{
			error = false;
			std::cout << answerVariantToStr();
		}
		try
		{
			switch (select)
			{
			case 2:
				std::cout << "������ ������ ������� ��� ����� : ";
				replaceAnswer(getText("������ ������ ������ (�������� Enter ��� ����������):"), getValue(1, answersVariants.size()));
				std::cout << " ������ ������ �������...";
				break;
			case 1:
				addAnswer(getText("������ ������ ������ (�������� Enter ��� ����������):"));
				std::cout << " ������ ������ ������...";
				break;
			case 3:
				std::cout << "������ ������ ������� ��� ��������� : ";
				delAnswer(getValue(1, answersVariants.size()));
				std::cout << " ������ ������ ��������...";
			}

		}
		catch (const question_invalid_argument& ex)
		{
			std::cout << ex.what();
			std::cout << "��������� �� ���...";
			error = true;
		}
		if (select != 4) system("pause>nul");
	} while (select != 4);
}

std::string Question::answerVariantToStr() const
{
	std::stringstream ss;
	int index = 1;
	ss << "\n     ������� ������:\n" << std::endl;
	for (const std::string& val : answersVariants)
	{
		ss << "           #" << index << "  " << val << std::endl;
		++index;
	}
	ss << std::endl;
	return ss.str();
}

std::string Question::getString() const
{
	std::stringstream ss;
	ss << question <<std::endl;
	ss << answerVariantToStr();
	return ss.str();
}

void Question::setQuestion()
{
	bool flag = false;
	do
	{
		system("cls");
		try 
		{
			set_question(getText("������ ����� ������� :",blanks));
			flag = true;
		}
		catch (const question_invalid_argument& ex)
		{
			std::cout << ex.what() << std::endl;
			std::cout << " ��������� �� ���...." << std::endl;
			system("pause>nul");
		}
	} while (!flag);
}

void Question:: toFStream(std::ofstream& ofs) const
{
	ofs << question_start_label << std::endl;
	ofs << type_lables[type] << std::endl ;
	ofs << question_lable << std::endl ;
	ofs << question << std::endl;
	ofs << answers_lable << std::endl ;
	for (const std::string& val : answersVariants)
		ofs << val << std::endl;
}

void Question::fromFStream(std::ifstream& ifs)
{
	std::string tmp;
	if(!goToNextLabel(ifs, question_lable)) throw question_invalid_file_format("������� ���� \"" + std::string(question_lable) +"\"...");
	try 
	{
		getFSText(ifs, tmp);
		set_question(tmp);
	}
	catch (const question_invalid_argument& ex)
	{
		throw question_invalid_file_format(ex.what());
	}
	if(!goToNextLabel(ifs, answers_lable)) throw question_invalid_file_format("������� ���� \"" + std::string(answers_lable) + "\"...");;
	try
	{
		while (getFSString(ifs,tmp))
			addAnswer(tmp);
		if (answersVariants.empty()) throw question_invalid_argument("������ ������� ��������...");
	}
	catch (const question_invalid_argument& ex)
	{
		throw question_invalid_file_format(ex.what());
	}
}


