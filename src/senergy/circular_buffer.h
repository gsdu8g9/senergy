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

#ifndef SY_CIRCULAR_BUFFER_H
#define SY_CIRCULAR_BUFFER_H

#include <vector>

namespace Senergy
{

/*!
 * \brief Simple circular buffer which uses a vector, simple circular buffer which
 *		  should not be used in situations that require efficiency and power.
 *
 * \typeparam T The type of data the circular buffer should hold.
 *
 * \note The documentation does not explain how a circular buffer works. Please use
 *		 Google for that.
 *
 * \author Swen Kooij (Photonios)
 */
template<class T>
class CircularBuffer : public std::vector<T>
{
public:
	/*!
  	 * \brief Initializes a new instance of the CircularBuffer class with
	 *		  the specified size.
 	 */
	CircularBuffer(unsigned int size) :
		m_size		(size),
		m_offset	(0)
	{
		BaseClass::reserve(size);
	}

	/*!
	 * \brief Overrides the vector's push_back function, but makes
	 *		  sure no new entries are inserted.
	 *		
 	 * \param value The value to insert into the circular buffer.
	 */
	void push_back(T value)
	{
		this[(int)m_offset] = value;
		
		if(m_offset >= m_size)
			m_offset = 0;
		else
			m_offset++;
	}

private:
	// Simple typedef to access the base class.
	typedef std::vector<T> BaseClass;

private:
	// Holds the size of the buffer
	unsigned int m_size;
	
	// Holds the offset at which the next item will be inserted
	unsigned int m_offset;
};

} // namespace Senergy

#endif // SY_CIRCULAR_BUFFER_H
