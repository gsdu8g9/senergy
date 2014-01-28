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
};

} // namespace Senergy

#endif // SY_CONVERT_H
