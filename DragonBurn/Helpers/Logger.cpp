#include "Logger.h"


Logger::Logger(HANDLE hConsole)
{
	this->hConsole = hConsole;
}

void Logger::Info(const std::string& ctx) const
{
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "[i]" << ctx << '\n';
}

void Logger::Warning(const std::string& ctx, bool pause = false) const
{
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "[!]" << ctx << '\n';

	if (pause) 
	{
		SetConsoleTextAttribute(hConsole, 8);
		system("pause");
	}

}

void Logger::Error(const std::string& ctx, bool fatal = true) const
{
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "[X]" << ctx << '\n';

	SetConsoleTextAttribute(hConsole, 8);
	system("pause");

	if (fatal)
		exit(0);
}

void Logger::Fine(const std::string& ctx) const
{
	SetConsoleTextAttribute(hConsole, 2);
	std::cout << "[+]" << ctx << '\n';
}

void Logger::Debug(const std::string& ctx) const
{
#ifdef _DEBUG
	std::string line = "[Debug]" + ctx + '\n';

	SetConsoleTextAttribute(hConsole, 9);
	std::cout << line;
#endif
}

void Logger::Custom(const std::string& ctx, int color) const
{
	SetConsoleTextAttribute(hConsole, color);
	std::cout << ctx << '\n';
}

void Logger::PreviousLine() const
{
	std::cout << "\033[1A\033[0G                                                                                \033[0G";
}