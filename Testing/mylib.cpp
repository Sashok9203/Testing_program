#include "mylib.h"


void saveStrToFile(const std::string title,const std::string str)
{
	std::cout << title << std::endl;
	char ch = _getch();
	if (ch == 27) return;
	std::string path = getWord(" Веедіть ім'я файлу : ");
	std::ofstream file(path);
	if (!file)
	{
		std::cout << " Не можливо створити файл \"" << path << "\"...";
		system("pause>nul");
		return;
	}
	file << str;
	file.close();
	std::cout << " Збережено в  файл \"" << path << "\"...";
	system("pause>nul");
}

std::string idcrypt(const std::string& str)
{
	std::string ss(str);
	for (int i = 0; i < ss.size(); i++)
	   ss[i] = str[i] ^ 'K';
	return ss;
}

bool isFileExist(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (file)
	{
		file.close();
		return true;
	}
	return false;
}
LogPass getLogPas(bool hidePass)
{
	int proc = 1;
	std::string log, pass;
	do {
		switch (proc)
		{
		case 1:
			std::cout << "      Логін : ";
			std::cin >> log;
			if (isBlank(log) || !isAlNum(log))
			{
				std::cout << "      Логін не повинен містити пробіли,спец.символи та кирилицю..." << std::endl;
				system("pause>nul");
				continue;
			}
			break;
		case 2:
			std::cout << "      Пароль : ";
			if (!hidePass)std::cin >> pass;
			else pass = getPassword();
			if (isBlank(pass) || !isAlNum(log))

			{
				std::cout << "      Пароль не повинен містити пробіли,спец.символи та кирилицю..." << std::endl;
				system("pause>nul");
				continue;
			}

		}
		++proc;
	} while (proc != 3);

	return { log,pass };
}
bool goToLabel(std::ifstream& ifs, const std::string& lable)
{
	std::string tmp;
	std::streampos pos = ifs.tellg();
	while ((ifs >> tmp),tmp != lable)
		if (!ifs)
		{
			ifs.clear();
			ifs.seekg(pos);
			return false;
		}
    return true;
}

bool goToNextLabel(std::ifstream& ifs, const std::string& lable)
{
	std::string tmp;
	std::streampos pos = ifs.tellg();
	if(!(ifs >> tmp)||tmp != lable)
	{
		ifs.clear();
		ifs.seekg(pos);
		return false;
	}
	return true;
}

int getValue(int min, int max)
{
	std::cout << " --> ";
	int value;
	while (!(std::cin >> value) || value < min || value > max)
	{
		std::cout << " Невірний ввід..." << std::endl;
		std::cout << " --> ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	std::cin.ignore(1000, '\n');
	return value;
}

std::string getText(const std::string& title, int blankCount)
{
	std::stringstream ss;
	std::string tmp;
	std::cout << title << std::endl;
	while (std::getline(std::cin, tmp), !isBlank(tmp))
		ss <<std::string(blankCount,' ') << tmp << '\n';
	tmp = ss.str();
    if(!tmp.empty()) tmp.pop_back();
	return tmp;
}
std::string getWord(const std::string& title)
{
	std::string tmp;
	std::cout << title;
	do{	std::cin >> tmp;} 
	while (isBlank(tmp));
	return tmp;
}
bool getFWord(const std::string& fileName, const std::string& label, std::string& str)
{
	std::ifstream ifs(fileName);
	if (!ifs) throw std::exception(("Не можливо відкрити файл " + label).c_str());
	if (goToLabel(ifs, label) && getFSWord(ifs, str))
	{
		ifs.close();
		return true;
	}
	ifs.close();
	return false;
	
}
bool getFSWord(std::ifstream& ifs, std::string& str)
{
	
	std::streampos pos; 
	while (pos = ifs.tellg(), (ifs >> str) && isBlank(str));
	ifs.clear();
	if (str.front() == '<' || !ifs)
	{
		ifs.seekg(pos);
		str.clear() ;
		return false;
	}
	return true;
}
std::string getPassword()
{
	std::string tmp;
	char ch;
	COORD coord = getCursor();
	while (ch = _getch(), ch != 13)
	{
		if (ch != 8)
		{
			++coord.X;
			std::cout << "*";
			tmp += ch;
		}
		else if (!tmp.empty())
		{
			--coord.X;
			setCursor(coord.X, coord.Y);
			std::cout << " ";
			setCursor(coord.X, coord.Y);
			tmp.pop_back();
		}
	}
	return tmp;
}
bool fileCopy(const std::string& from, const std::string& to)
{
	std::ifstream ifs(from, std::ifstream::binary);
	char* buffer;
	int length;
	if (ifs) {
		
		ifs.seekg(0, ifs.end);
		length = (int)ifs.tellg();
		ifs.seekg(0, ifs.beg);

		buffer = new char[length];


		ifs.read(buffer, length);

		if (!ifs) return false;
			
		ifs.close();


	    std::ofstream ofs(to, std::ofstream::binary);
		if (ofs)
		{
			ofs.write(buffer, length);
			ofs.close();
			delete[] buffer;
		}
		else return false;
		return true;
	}
	return false;
}
bool getFSString(std::ifstream& ifs, std::string& str)
{
	std::streampos pos;
	while (pos = ifs.tellg(), std::getline(ifs, str), isBlank(str) && ifs);
	
	if (!ifs || str.front() == '<')
	{
		ifs.clear();
		ifs.seekg(pos);
		str.clear();
		return false;
	}
	return true;
}
bool getFSText(std::ifstream& ifs, std::string& str)
{
	std::streampos pos;
	std::ostringstream ss;
	while (pos = ifs.tellg(), std::getline(ifs, str), ifs)
	{
		if (!isBlank(str))
		{
			if (str.front() == '<')
			{
				ifs.seekg(pos);
				break;
			}
			ss << str << "\n";
		}
	}
	str = ss.str();
	if(!str.empty()) str.pop_back();
	return !isBlank(str);
}
std::string getString(const std::string& title)
{
	std::string tmp;
	std::cout << title ;
	do { std::getline(std::cin, tmp); } while (isBlank(tmp));
	return tmp;
}
bool isBlank(const std::string& str) 
{
	if (!str.empty())
		for (char ch : str)
			if (!isblank(static_cast<unsigned char>(ch))) return false;
	return true;
}

bool isAlNum(const std::string& str)
{
	if (!str.empty())
		for (char ch : str)
			if (!isalnum(static_cast<unsigned char>(ch))) return false;
	return true;
}

bool isDigit(const std::string& str)
{
	if (!str.empty())
		for (char ch : str)
			if (!isdigit(static_cast<unsigned char>(ch))) return false;
	return true;
}


void setCursor(short x, short y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD { x,y });
}

COORD getCursor()
{

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		return csbi.dwCursorPosition;
	}
	return COORD {};
}