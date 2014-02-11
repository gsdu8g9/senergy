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

#ifndef SY_CONSOLE_H
#define SY_CONSOLE_H

#include <string>
#include <iostream>

namespace Senergy
{

/*!
 * \brief Contains replacements for 'printf' that use C++11 features, such as variadic templates.
 *		  The printf replacement in this class is more C++ like, and for example supports standard
 *		  strings, as oppossed to printf, which only supports C99 data types.
 *
 * \author Swen Kooij (Photonios)
 */
class Console
{
public:
	/*!
	 * \brief Overload to handle prints without any format identifiers, simply
	 *		  prints the specified string.
	 *
	 * \param fmt The string to print to the standard output stream.
	 */
	static void Print(const std::string &fmt)
	{
		__print(fmt);
	}

	
	/*!
	 * \brief Does the actual printing of a whole format string with a variable number of
	 *		  elements/format identifiers.
	 *
	 * \note This uses variadic templates, and uses recursion to iterate over all specified
	 *		 elements.
	 *
	 * \typeparam T The type of the first element.
	 * \typeparam R The type of the current element (recursion).
	 *
	 * \param fmt 		The format string.
	 * \param element	The first element to print, should correspong with the first format
	 *					identifier.
	 * \param rest		Variadic templates, the rest of the elements to print.
	 *
 	 */
	template<class... R>
	static void Print(const std::string &fmt, const R&... rest)
	{
		 std::string rem = __print(fmt, rest...);
		 if (rem != "")
		     __print(rem);
	}

private:
	/*!
	 * \brief This overloads our variadic version, but handles calls without
	 *		  extra parameters, just prints the specified string.
	 *
	 * \param fmt The string to to be printed to the standard output stream.
	 * 
 	 * \returns An empty string, can't return void here because this is an
	 *			overload.
	 */
	static const std::string __print(const std::string &fmt)
	{
		std::cout << fmt;
			return "";
	}

	/*!
 	 * \brief Prints the specified format string, where the format identifier is replaced
	 *		  with the specified element of type T.
	 *
	 * \typeparam T The type of the element/variable to print.
	 *
	 * \note This function only takes one element, this is because variadic templates require
	 *		 recursion to iterate over all elements (See overloads).
	 *
	 * \param fmt		The format string to print.
	 * \param element	The element to replace the format identifier with.
	 *
	 * \returns An empty string, can't return void here, because this is an overload.
	 */
	template<class T>
	static const std::string __print(const std::string &fmt, const T &element)
	{
		size_t fmt_len = fmt.size();

		for(size_t i = 0; i < fmt_len; ++i)
		{
			if(fmt[i] != '%')
			{
				printf("%c", fmt[i]);
				continue;
			}

			int y = 1;
			for(; y < fmt_len; ++y)
			{
				if(fmt[i] == ' ' || fmt[i] == '%')
					break;
			}

			if(y < 0)
			{
				std::cout << fmt[i];
				continue;
			}

			i += y + 1;
			std::cout << element;
		
			return fmt.substr(i);
		}
	}

	/*!
	 * \brief Does the actual printing of a whole format string with a variable number of
	 *		  elements/format identifiers.
	 *
	 * \note This uses variadic templates, and uses recursion to iterate over all specified
	 *		 elements.
	 *
	 * \typeparam T The type of the first element.
	 * \typeparam R The type of the current element (recursion).
	 *
	 * \param fmt 		The format string.
	 * \param element	The first element to print, should correspong with the first format
	 *					identifier.
	 * \param rest		Variadic templates, the rest of the elements to print.
	 *
	 * \returns This function is called recursively, and returns an empty string when
	 *			the recursion was stopped, and the whole string was printed.
 	 */
	template<class T, class... R>
	static const std::string __print(const std::string &fmt, const T &element, const R&... rest)
	{
		std::string formatted = __print(fmt, element);
		if(formatted != "")
			return __print(formatted, rest...);

		return "";
	}
};

} // namespace Senergy

#endif // SY_CONSOLE_H
