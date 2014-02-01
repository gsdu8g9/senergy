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

#ifndef SY_VECTOR_X_H
#define SY_VECTOR_X_H

#include <vector>

namespace Senergy
{

/*!
 * \brief An improvemend upon the standard vector (std::vector), but it's interface is more like
 *		  the rest of Senergy (naming). All normal functionality is still available, and switching
 *		  between VectorX and std::vector should be painless.
 *
 * \typeparam T The type that the vector will contain.
 *
 * \author Swen Kooij (Photonios)
 */
template<class T>
class VectorX : public std::vector<T>
{
public:
	/*!
	 * \brief Initializes a new, empty vector.
	 */
	VectorX()
	{
	}

	/*!
 	 * \brief Adds the specified item to the vector.
	 *
	 * \param value The object/value to add to the vector.
 	 */
	void Add(T value)
	{
		BaseClass::push_back(value);
	}

private:	
	/*!
 	 * \brief Simple typedef to access the base class.
	 */
	typedef std::vector<T> BaseClass;
};

} // namespace Senergy

#endif // SY_VECTOR_X_H
