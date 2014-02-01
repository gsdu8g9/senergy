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
 
#include <senergy/convert.h>

namespace Senergy
{

std::string Convert::ToString(int value)
{
	int digits = floor(log10(abs(value))) + 1;
	if(value == 0)
		digits = 1;

	char raw_result[digits];
	sprintf(raw_result, "%d", value); 
	
	return std::string(raw_result);
}

/*!
 * \brief Converts the specified integer value to a string.
 *
 * \param value The integer value to convert to a string.
 *
 * \returns The specified integer value as a string.
 */
std::string Convert::ToString(unsigned int value)
{
	return ToString((int)value);
}

char Convert::ToChar(int value)
{
	return ToString(value)[0];
}

} // namespace Senergy
