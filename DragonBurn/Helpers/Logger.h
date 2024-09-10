#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

namespace Log 
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	inline void Info(std::string ctx) 
	{
		SetConsoleTextAttribute(hConsole, 8);
		std::cout << "[i]" << ctx << '\n';
	}

	inline void Warning(std::string ctx, bool pause = false)
	{
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << "[!]" << ctx << '\n';

		if (pause)
			system("pause");
	}

	inline void Error(std::string ctx, bool fatal = true)
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "[X]" << ctx << '\n';
		system("pause");
		if(fatal)
			exit(0);
	}

	inline void Fine(std::string ctx)
	{
		SetConsoleTextAttribute(hConsole, 2);
		std::cout << "[+]" << ctx << '\n';
	}

	inline void Debug(std::string ctx)
	{
		SetConsoleTextAttribute(hConsole, 9);
		std::cout << "[Debug]" << ctx << '\n';
	}

	inline void Custom(std::string ctx, int color)
	{
		SetConsoleTextAttribute(hConsole, color);
		std::cout << ctx << '\n';
	}

	inline void PreviousLine()
	{
		std::cout << "\033[1A\033[0G                                                                                \033[0G";
	}
}