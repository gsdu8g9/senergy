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

#ifndef SY_PRINT_H
#define SY_PRINT_H

#include <cstdio>

namespace Senergy
{

/*!
 * \brief Contains simple utilities that facilitate printing various data types
 *		  or data structures to the screen.
 *
 * \author Swen Kooij (Photonios)
 */
class Print
{
public:
	/*!
 	 * \brief Prints the specified char array of the specified string, byte by byte
	 *		  where each byte is shown in it's hexadecimal representation. Followed
	 *		  by a new-line character (\n).
	 *
	 * \param data The data to print hexadecimal.
	 * \param size The size of the data to print.
	 */
	static void Hexadecimal(char *data, int size);
	
	/*!
 	 * \brief Prints the specified integer value to the screen, followed by a new-line
	 *		  character.
	 *
	 * \param value The integer value to print to the screen.
	 */
	static void Integer(int value);
};

} // namespace Senergy

#endif // SY_PRINT_H
