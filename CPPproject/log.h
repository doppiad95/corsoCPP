#pragma once
#include <iostream>
#include <string>

using std::string;
using std::cout;

class Logger
{
public:
	enum LogLevel { ALL, INFO, WARNING, ERROR, NEEDED };
private:
	LogLevel Errorlevel;
	string LogLevelNames[5];

public:
	/**
	* 	@brief Costruttore Default
	*
	**/
	Logger()
	{
		Errorlevel = ALL;
		LogLevelNames[0] = "ALL";
		LogLevelNames[1] = "INFO";
		LogLevelNames[2] = "WARNING";
		LogLevelNames[3] = "ERROR";
		LogLevelNames[4] = "NEEDED";
	}
	/**
	*	@brief Costruttore con livello
	*
	**/
	Logger(const LogLevel level)
	{
		LogLevelNames[0] = "ALL";
		LogLevelNames[1] = "INFO";
		LogLevelNames[2] = "WARNING";
		LogLevelNames[3] = "ERROR";
		LogLevelNames[4] = "NEEDED";
		Errorlevel = level;
		if (Errorlevel <= INFO)
		{
			cout << "[" << LogLevelNames[Errorlevel] << "]: " << "LOGGER set to: " << LogLevelNames[Errorlevel] << std::endl;
		}
	}
	/**
	* 	@brief Distruttore
	*
	**/
	~Logger()
	{
		if (Errorlevel < WARNING)
		{
			cout << "[" << LogLevelNames[Errorlevel] << "]:" << " LOGGER destroyed" << std::endl;
		}
	}
	/**
	* 	@brief Crea riga di log
	*
	**/
	void log(const LogLevel level, const string& message) const
	{
		if (Errorlevel <= level)
		{
			cout << "[" << LogLevelNames[level] << "]: " << message << std::endl;
		}
	}
};