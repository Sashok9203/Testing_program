#include "TestResult.h"



TestResult::TestResult(std::ifstream& ifs):rightAnswersCount(0), points(0), nextQuestionIndex(0), passed(false)
{
	 fromFStream(ifs); 
}

TestResult::TestResult(const std::string& name, const std::string& category, int testQuestionCount)
	:rightAnswersCount(0), points(0), nextQuestionIndex(0), passed(false)
{
	if ( isBlank(name) ||isBlank(category) || testQuestionCount <= 0)
		throw std::invalid_argument("������� �������� ������������ TestResult ");
	this->category = category;
	this->name = name;
	this->testQuestionCount = testQuestionCount;
}

void TestResult::setNextQuestionIndex(int index)
{
	if (index < 0 || index>testQuestionCount) throw std::exception("�� ����� ������ �������");
	this->nextQuestionIndex = index;
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
	ofs << nextQuestionIndex << std::endl;
}

int TestResult::getRating() const
{
	
	return (int)round((float)points/testQuestionCount);
}

double TestResult::getRightAnswersPercent() const
{
	double percent = (double)testQuestionCount * 12 / 100;
	return (double)points / percent;
}

void TestResult::fromFStream(std::ifstream& ifs)
{
	std::string tmp;
	try
	{
		if (goToLabel(ifs, tname_lable))
		{
			if (!getFSString(ifs, tmp)) throw invalid_file_format("����� ����� �� ��������");
			name = tmp;
		}
		if (goToLabel(ifs, tcat_lable))
		{
			if (!getFSString(ifs, tmp)) throw invalid_file_format("�������� ����� �� ��������");
			category = tmp;
		}
		if (!goToLabel(ifs, tres_data_lable))	 throw invalid_file_format("����� ����� �� ��������");
		
		int set = 1;
		int temp;
		while (set != 6 && ifs >> temp)
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
				setNextQuestionIndex(temp);
				break;
			}
			++set;
		}
		if (set < 6) throw std::invalid_argument(" �� �������� ��������� ����� �estResult");
	
	}
	catch (const std::invalid_argument& ex)
	{
		throw testing_invalid_file_format(ex.what());
	}
}

std::string TestResult::getResStr(int index ) const
{
	std::stringstream ss;
	ss << "    --  ��������� ����������  " ;
	if (index) ss << index << " --" << std::endl;
	else ss << " --" << std::endl;
	ss << "        �����           : " << name << std::endl;
	ss << "        ��������       : " << category << std::endl;
	ss << "        �������         : " << std::setprecision(2) << std::fixed << getRightAnswersPercent() << " %" << std::endl;
	ss << "        ³�� ������ : " << rightAnswersCount << " �� " << testQuestionCount << std::endl;
	ss << "        ������          : ";
	if (!passed)
	{
		ss << "�� ���������" << std::endl;
		return ss.str();
	}
	else ss <<  getRating() << std::endl;
	return ss.str();
}
