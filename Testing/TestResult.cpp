#include "TestResult.h"



TestResult::TestResult(const std::string& name, const std::string& category, int testQuestionCount)
	:rightAnswersCount(0), points(0), lastQuestionIndex(0), passed(false)
{
	if ( isBlank(name) ||isBlank(category) || testQuestionCount <= 0)
		throw std::invalid_argument("Невірний аргумент конструктора TestResult ");
	this->category = category;
	this->name = name;
	this->testQuestionCount = testQuestionCount;
}

void TestResult::setLastQuestionIndex(int index)
{
	if (index < 0 || index>testQuestionCount) throw std::exception("Не вірний індекс питання");
	this->points = points;
}

void TestResult::toFStream(std::ofstream& ofs) const
{
	ofs << tres_lable << std::endl;
	ofs << tname_lable << std::endl;
	ofs << name << std::endl;
	ofs << tcat_lable << std::endl;
	ofs << category << std::endl;
	ofs << tres_data_lable << std::endl;
	ofs << passed << std::endl;
	ofs << points << std::endl;
	ofs << testQuestionCount << std::endl;
	ofs << rightAnswersCount << std::endl;
	ofs << lastQuestionIndex << std::endl;
}

int TestResult::getRating() const
{
	
	return (int)round((float)points/testQuestionCount);
}

float TestResult::getRightAnswersPercent() const
{
	float percent = (float)testQuestionCount * 12 / 100;
	return (float)points / percent;
}

void TestResult::fromFStream(std::ifstream& ifs)
{
	//if(!goToLable(ifs,tres_lable))throw invalid_file_format("Mітку " + std::string(tres_lable) + " не знайдено");
	
	std::string tmp;
	try
	{
		if (goToLable(ifs, tname_lable))
		{
			if (!getFSWord(ifs, tmp)) throw invalid_file_format("Назву тесту не знайдено");
			name = tmp;
		}
		if (goToLable(ifs, tcat_lable))
		{
			if (!getFSWord(ifs, tmp)) throw invalid_file_format("Категорію тесту не знайдено");
			category = tmp;
		}
		int set = 1;
		int temp;
		while (ifs >> temp)
		{
			switch (set)
			{
			case 1:
				passed = temp;
				break;
			case 2:
				addPoints(temp);
				break;
			case 3:
				testQuestionCount = temp;
				break;
			case 4:
				rightAnswersCount = temp;
				break;
			default:
				setLastQuestionIndex(temp);
				break;
			}
			++set;
		}
		if (set != 5) throw std::invalid_argument(" не вистачае параметрів класу ТestResult");
	
	}
	catch (const std::invalid_argument& ex)
	{
		throw testing_invalid_file_format(ex.what());
	}
}

void TestResult::showResult(int index ) const
{
    std::cout << " --  Результат тестування  " ;
	if (index) std::cout << index << " --" << std::endl;
	std::cout << "  Назва           : " << name << std::endl;
	std::cout << "  Категорія       : " << category << std::endl;
	std::cout << "  Процент         : " << getRightAnswersPercent() << " %" << std::endl;
	std::cout << "  Вірні відповіді : " << rightAnswersCount << " из " << testQuestionCount << std::endl;
	if (!passed)
	{
		std::cout << " Тест не завершено" << std::endl;
		return;
	}
	std::cout << "  Оцінка          : " << getRating() << std::endl;
}
