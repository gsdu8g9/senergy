/*******************************************************************************
 *
 *	 This file is part of Senergy.
 *
 *   Senergy is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Senergy is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Senergy. If not, see <http://www.gnu.org/licenses/>.
 *
 *   Swen Kooij (Photonios) <swenkooij@gmail.com> <photonios@outlook.com>
 *
 *******************************************************************************/

#ifndef SY_LOGGER_H
#define SY_LOGGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <senergy/print.h>
#include <senergy/console.h>

namespace Senergy
{

/*!
 * \brief An enumuration of all possible log levels, log levels will result
 *		  in prefixes in log entries.
 */
enum class LogLevel
{
	Info,
	Error,
	Warning,
	Debug
};

/*!
 * \brief Simple logger with support for variadic arguments and various log levels.
 *
 * \author Swen Kooij (Photonios)
 */
class Logger
{
public:
	/*!
	 * \brief Writes a info log message with the specified log message and the current date and
	 *		  and time.
	 *
	 * \typeparm R Any type, it's variadic :D
	 * 
	 * \param message	The message to log.
	 * \param rest		All arguments, can be of any type, but should have a format identifier in
	 *				  	the 'message' argument.
	 *
	 */
	template<class... R>
	static void Info(const std::string &message, const R&... rest)
	{
		Log(LogLevel::Info, message, rest...);
	}

	/*!
	 * \brief Writes a error log message with the specified log message and the current date and
	 *		  and time.
	 *
	 * \typeparm R Any type, it's variadic :D
	 * 
	 * \param message	The message to log.
	 * \param rest		All arguments, can be of any type, but should have a format identifier in
	 *				  	the 'message' argument.
	 *
	 */
	template<class... R>
	static void Error(const std::string &message, const R&... rest)
	{
		Log(LogLevel::Error, message, rest...);
	}

	/*!
	 * \brief Writes a warning log message with the specified log message and the current date and
	 *		  and time.
	 *
	 * \typeparm R Any type, it's variadic :D
	 * 
	 * \param message	The message to log.
	 * \param rest		All arguments, can be of any type, but should have a format identifier in
	 *				  	the 'message' argument.
	 *
	 */
	template<class... R>
	static void Warning(const std::string &message, const R&... rest)
	{
		Log(LogLevel::Warning, message, rest...);
	}

	/*!
	 * \brief Writes a debug log message with the specified log message and the current date and
	 *		  and time.
	 *
	 * \typeparm R Any type, it's variadic :D
	 * 
	 * \param message	The message to log.
	 * \param rest		All arguments, can be of any type, but should have a format identifier in
	 *				  	the 'message' argument.
	 *
	 */
	template<class... R>
	static void Debug(const std::string &message, const R&... rest)
	{
		Log(LogLevel::Debug, message, rest...);
	}

	/*!
	 * \brief Writes a log message with the specified log message and the current date and
	 *		  and time.
	 *
	 * \typeparm R Any type, it's variadic :D
	 * 
	 * \param level  	The level this log message needs to be stored under.
	 * \param message	The message to log.
	 * \param rest		All arguments, can be of any type, but should have a format identifier in
	 *				  	the 'message' argument.
	 *
	 */
	template<class... R>
	static void Log(LogLevel level, const std::string &message, const R&... rest)
	{
		std::string level_str = "";
		switch(level)
		{
			case LogLevel::Info:
				level_str += "INF";
				break;

			case LogLevel::Error:
				level_str += "ERR";
				break;

			case LogLevel::Warning:
				level_str += "WRN";
				break;

			case LogLevel::Debug:
				level_str += "DBG";
				break;

			default:
				level_str += "INF";
		}
		
		std::string date_time_str = __get_time_string();
		
		Console::Print("[%s][%s] ", level_str, date_time_str);
		Console::Print(message + "\n", rest...);
	}

private:
	// Gets the current date/time as a string to be used in the log..
	static std::string __get_time_string()
	{
		auto time_point = std::chrono::system_clock::now();
    	std::time_t ttp = std::chrono::system_clock::to_time_t(time_point);
	
		std::string format_string = "%H:%M:%S";

		struct tm *timeinfo;
		timeinfo = localtime(&ttp);

		std::string buffer;
		buffer.resize(format_string.size());
		int len = strftime(&buffer[0], buffer.size(), format_string.c_str(), timeinfo);

		while (len == 0) 
		{
		    buffer.resize(buffer.size()*2);
		    len = strftime(&buffer[0], buffer.size(), format_string.c_str(), timeinfo);
		} 
		
		return buffer;
	}
};

} // namespace Senergy

#endif // SY_LOGGER_H
