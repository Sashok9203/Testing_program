#include "Test.h"




void Test::addQuestion( Question* question)
{
	 if(question->getQuestion() !="NoQuestion") questions.push_back(question); 
	 else  throw test_invalid_argument("�� ����������� ���� Question");
}

Test::Test(const std::string& fileName)
{
	loadTest(fileName);
}

Test::Test(std::ifstream& ifs)
{
	fromFStream(ifs);
}

Test::~Test()
{
	for (auto val : questions)
		delete val;
}

void Test::addQuestion()
{
	Question* tmp ;
	system("cls");
	std::cout << " ---- ��� ����� ----" << std::endl;
	std::cout << " [1] ���� � ����� �������� " << std::endl;
	std::cout << " [2] ���� � �������� ��������� " << std::endl;
	std::cout << " [3] ����� " << std::endl;
	int select = getValue(1, 3);
	switch (select)
	{
	case 1:
		tmp = new SingleAnswerQuestion();
		break;
	case 2:
		tmp = new MultyAnswerQuestion();
		break;
	default:
		return;
	}
	tmp->setQuestion();
	tmp->setAnswerVariant();
	tmp->setAnswer();
	addQuestion(tmp);
	std::cout << " ������� ������ �� �����...���� ��������� � ���� " << name+exp << std::endl;
}

void Test::delQuestion(int index)
{
	if (index < 0 || index >= questions.size()) throw test_invalid_argument("�� ����� ���e�� �������");
	questions.erase(questions.begin() + index);
}



void Test::loadQuestion(std::ifstream& ifs)
{
    std:: string tmp;
	while (std::getline(ifs, tmp),tmp[0] != '<')
	{
		if (!ifs) return;
			
	}
	if (tmp == Question::type_lables[Question::MULTI_ANSWER_Q])
	{
		questions.push_back(new MultyAnswerQuestion(ifs));
	}
	else if (tmp == Question::type_lables[Question::SINGLE_ANSWER_Q])
	{
		questions.push_back(new SingleAnswerQuestion(ifs));
	}
	else throw test_invalid_file_format("�� ���� ���� \"" + tmp + "\"");
}

 Question& Test::getQuestion(int index)
{
	return *questions[index];
}

void Test::showAll() const
{
	system("cls");
	if (questions.empty())
	{
		std::cout << "���� �� ������ ������..." << std::endl;
		return;
	}
	int ind = 1;
	for (const auto& val : questions)
	{
		std::cout << "   ������� #" << ind << std::endl;
		std::cout << val->getString();
		++ind;
	}
}

void Test::setName(const std::string& name)
{
	if (isBlank(name)) throw test_invalid_argument("����� ����� �� ���� ���� ������ ������");
	this->name = name;
	
}



void Test::loadTest(const std::string& fileName)
{
	if (isBlank(fileName)) throw test_invalid_argument("����� ������ �� ���� ���� ������ ������");
	std::ifstream ifs(fileName);
	if (!ifs) throw std::exception(("�� ������� ������� ����  \"" + fileName + "\" ! ! !").c_str());
	fromFStream(ifs);
	
}

void Test::saveTest(const std::string& fileName)
{
    if (fileName == "") throw std::exception("����� ����� �� ���� ���� ������ ������� ! ! !");
	std::ofstream file(fileName);
	if (!file) throw std::exception(("�� ������� ������� ���� \"" + fileName + "\" ! ! !").c_str());
	toFStream(file);
	file.close();

}

void Test::toFStream(std::ofstream& ofs) const
{
	ofs << name_lable << std::endl;
	ofs << name << std::endl;
	for (auto ptr : questions)
		ptr->toFStream(ofs);
}

void Test::fromFStream(std::ifstream& ifs)
{
	std::string tmp;
	goToLable(ifs, name_lable);
	try
	{

		if (!getFSString(ifs, tmp)) throw test_invalid_argument(" ������� ����� �����...");
		name = tmp;
		while (ifs)
			loadQuestion(ifs);
		ifs.close();
	}
	catch (const question_invalid_argument& ex)
	{
		throw question_invalid_file_format(ex.what());
	}
}
