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
	/// <summary>
	/// Logger constructor
	/// </summary>
	/// <param name="base console handle "></param>
	/// <returns> none </returns>
	Logger(HANDLE);

	/// <summary>
	/// Logger destructor
	/// </summary>
	/// <returns> none </returns>
	~Logger();

	/// <summary>
	/// Example: [i]ctx
	/// </summary>
	/// <param name="context"></param>
	/// <returns> none </returns>
	void Info(const std::string&) const;

	/// <summary>
	/// Example: [!]ctx
	/// </summary>
	/// <param name="context"></param>
	/// <returns> none </returns>
	void Warning(const std::string&, bool = false) const;

	/// <summary>
	/// Example: [X]ctx
	/// </summary>
	/// <param name="context"></param>
	/// <param name="fatal"></param>
	/// <returns> none </returns>
	void Error(const std::string&, bool = true) const;

	/// <summary>
	/// Example: [+]ctx
	/// </summary>
	/// <param name="context"></param>
	/// <returns> none </returns>
	void Fine(const std::string&) const;

	/// <summary>
	/// Works only in debug mode. Example: [Debug]ctx
	/// </summary>
	/// <param name="context"></param>
	/// <returns> none </returns>
	void Debug(const std::string&) const;


	/// <summary>
	/// Outputs colored ctx
	/// </summary>
	/// <param name="context"></param>
	/// <param name="color"></param>
	/// <returns> none </returns>
	void Custom(const std::string&, int) const;

	/// <summary>
	/// Sets cursor to the beginning of previous line and clean line
	/// </summary>
	/// <returns> none </returns>
	void PreviousLine() const;

private:
	HANDLE hConsole;
};