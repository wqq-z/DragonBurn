#pragma once
#include <Windows.h>
#include <iostream>
#include <string>


class Logger 
{
public:
	Logger(HANDLE);

	void Info(const std::string&) const;
	void Warning(const std::string&, bool = false) const;
	void Error(const std::string&, bool = true) const;
	void Fine(const std::string&) const;
	void Debug(const std::string&) const;

	void Custom(const std::string&, int) const;
	void PreviousLine() const;

private:
	HANDLE hConsole;
};