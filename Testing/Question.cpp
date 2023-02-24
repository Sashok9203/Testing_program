#include "Question.h"

void Question::set_question(const std::string& question)
{
	if (isBlank(question)) throw question_invalid_argument("запитання не може складатися з пробілів...");
	this->question = question;
}
void Question::addAnswer(const std::string& answer)
{
	if (isBlank(answer)) throw question_invalid_argument("запитання не може складатися з пробілів ... ");
	answersVariants.push_back(answer);
}

void Question::delAnswer(const int index)
{
	if (index<1 || index>answersVariants.size()) throw question_invalid_argument("недопустимий індекс відповіді = " + std::to_string(index) + " ... має бути від 1 до " + std::to_string(answersVariants.size()));
	answersVariants.erase(answersVariants.begin() + index - 1);
}

void Question::replaceAnswer(const std::string answer, const int index)
{
	if (index<1 || index>answersVariants.size()) throw question_invalid_argument("недопустимий індекс відповіді = " + std::to_string(index) + " ... має бути від 1 до " + std::to_string(answersVariants.size()));
	if (isBlank(answer)) throw question_invalid_argument("запитання не може складатися з пробілів ... ");
	answersVariants[index - 1] = answer;
}
int Question::answerToQestion() const
{
	if (answersVariants.empty()) throw question_invalid_argument("неможливо дати відповіть ... варіанти відповіді відсутні....");
	return 0;
}
void Question::setAnswer()
{
	if (answersVariants.empty()) throw question_invalid_argument("встановити відповідь не можливо ... варіанти відповіді відсутні....");
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
			std::cout << "   [1] Додати" << std::endl;
			std::cout << "   [2] Замінити" << std::endl;
			std::cout << "   [3] Видалити" << std::endl;
			std::cout << "   [4] Завершити" << std::endl;
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
				std::cout << "Введіть індекс варіанту для заміни : ";
				replaceAnswer(getText("Введіть варіант відповіді (подвійний Enter для завершення):"), getValue(1, answersVariants.size()));
				std::cout << " Варіант відповіді замінено...";
				break;
			case 1:
				addAnswer(getText("Введіть варіант відповіді (подвійний Enter для завершення):"));
				std::cout << " Варіант відповіді додано...";
				break;
			case 3:
				std::cout << "Введіть індекс варіанту для видалення : ";
				delAnswer(getValue(1, answersVariants.size()));
				std::cout << " Варіант відповіді видалено...";
			}

		}
		catch (const question_invalid_argument& ex)
		{
			std::cout << ex.what();
			std::cout << "Спробуйте ще раз...";
			error = true;
		}
		if (select != 4) system("pause>nul");
	} while (select != 4);
}

std::string Question::answerVariantToStr() const
{
	std::stringstream ss;
	int index = 1;
	ss << "\n     Варіанти відповіді:\n" << std::endl;
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
			set_question(getText("Введіть текст питання :",blanks));
			flag = true;
		}
		catch (const question_invalid_argument& ex)
		{
			std::cout << ex.what() << std::endl;
			std::cout << " Спробуйте ще раз...." << std::endl;
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
	if(!goToNextLabel(ifs, question_lable)) throw question_invalid_file_format("відсутня мітка \"" + std::string(question_lable) +"\"...");
	try 
	{
		getFSText(ifs, tmp);
		set_question(tmp);
	}
	catch (const question_invalid_argument& ex)
	{
		throw question_invalid_file_format(ex.what());
	}
	if(!goToNextLabel(ifs, answers_lable)) throw question_invalid_file_format("відсутня мітка \"" + std::string(answers_lable) + "\"...");;
	try
	{
		while (getFSString(ifs,tmp))
			addAnswer(tmp);
		if (answersVariants.empty()) throw question_invalid_argument("відсутні варіанти відповідей...");
	}
	catch (const question_invalid_argument& ex)
	{
		throw question_invalid_file_format(ex.what());
	}
}


