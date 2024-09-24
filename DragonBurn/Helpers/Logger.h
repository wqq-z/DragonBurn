//
//______                            ______                  
//|  _  \                           | ___ \                 
//| | | |_ __ __ _  __ _  ___  _ __ | |_/ /_   _ _ __ _ __  
//| | | | '__/ _` |/ _` |/ _ \| '_ \| ___ \ | | | '__| '_ \ 
//| |/ /| | | (_| | (_| | (_) | | | | |_/ / |_| | |  | | | |
//|___/ |_|  \__,_|\__, |\___/|_| |_\____/ \__,_|_|  |_| |_|
//                  __/ |                                   
//                 |___/                                    
//https://github.com/ByteCorum/DragonBurn

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