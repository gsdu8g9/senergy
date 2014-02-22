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
 
#ifndef SY_ENUM_MAPPER_H
#define SY_ENUM_MAPPER_H

#include <string>
#include <senergy/fastmap.h>

namespace Senergy
{

/*! 
 * \brief Simple wrapper for a hash map that maps enum values to their textual value (name).
 *
 * \author Swen Kooij
 */
template<typename T>
class EnumMapper : public FastMap<T, std::string>
{
public:
	/*!
	 * \brief Maps the specified enumuration value to the specified textual representation.
	 *
	 * \param enum_value	  A value from the enumuration to map to the specified textual representation.
	 * \param enum_value_name The textual representation of the specified enum value.
	 */
	void Map(T enum_value, const std::string &enum_value_name)
	{
		(*this)[enum_value] = enum_value_name;
	}
	
	/*!
	 * \brief Finds the textual representation for the specified enumuration value.
	 *
	 * \param enum_value A value from the enumuration to find the textual representation for.
	 *
	 * \returns The textual representation of the specified enumuration value. An empty string is
	 *			returned when no mapping exists for the specified enumuration value.
	 */
	std::string GetMapping(T enum_value)
	{
		return (*this)[enum_value];
	}
};

} // namespace Senergy

#endif // SY_ENUM_MAPPER_H