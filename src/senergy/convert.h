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
 
#ifndef SY_CONVERT_H
#define SY_CONVERT_H

#include <string>
#include <cstdio>
#include <cmath> 
#include <ctgmath>

namespace Senergy
{

/*!
 * \brief A simple conversion class, which simplifies conversion between various
 *		  native data types. Based on the idea of the 'Convert' class in the .NET
 *		  framework.
 * 
 * \author Swen Kooij (Photonios)
 */
class Convert
{
public:
	/*!
  	 * \brief Converts the specified integer value to a string.
	 *
	 * \param value The integer value to convert to a string.
	 *
	 * \returns The specified integer value as a string.
 	 */
	static std::string ToString(int value);

	/*!
  	 * \brief Converts the specified unsigned integer value to a string.
	 *
	 * \param value The unsigned integer value to convert to a string.
	 *
	 * \returns The specified unsigned integer value as a string.
 	 */
	static std::string ToString(unsigned int value);
	
	/*!
	 * \brief Converts the specified unsigned short value to a string.
	 *
	 * \param value The unsigned short value to convert to a string.
	 *
	 * \returns The specified unsigned short value as a string.
	 */
	static std::string ToString(unsigned short value);

	/*!
  	 * \brief Converts the specified integer value to a character.
	 *
	 * \param value The integer value to convert to a character.
	 *
	 * \returns The specified integer value as a character.
 	 */
	static char ToChar(int value);
	
private:
	/*!
	 * \brief Converts the specified integer/number type to a string using the specified 'printf identifier'.
	 *
	 * \typeparam T The integer type to convert to a string.
	 * 
	 * \param value 			The integer/numeric value to convert to a string.
	 * \param printf_identfier  The 'printf identifier' to use, for example, for an unsigned integer, '%u' is specified.
	 *
	 * \returns The specified integer/numeric value as a string.
	 */
	template<typename T>
	static std::string __numeric_to_string(T value, const std::string &printf_identifier)
	{
		int digits = floor((double)log10(abs(value))) + 1;
		if(value == 0)
			digits = 1;

		#ifdef _WIN32
			char *raw_result = (char *) malloc(digits);
		#else
			char raw_result[digits];
		#endif
 
		sprintf(raw_result, printf_identifier.c_str(), value); 
		return std::string(raw_result);
	}
};

} // namespace Senergy

#endif // SY_CONVERT_H
