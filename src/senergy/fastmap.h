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

#ifndef SY_FAST_MAP_H
#define SY_FAST_MAP_H

#include <vector>
#include <stddef.h>

namespace Senergy
{

/*!
 * \brief The structure that FastMap stores in it's vector, this emulates
 *		  a std::map iterator.
 *
 * \typeparam TKey   The data type of the key that is stored in the map.
 * \typeparam TValue The data type of the value that is stored in the map.
 *
 * \author Swen Kooij (Photonio)
 */
template <class TKey, class TValue>
struct FastMapItem
{
	TKey first;
	TValue second;
};

/*!
 * \brief The fast map is an alternative to std::map. An std::map is relatively slow with a small number
 * 		  of items. FastMap uses a vector of structures instead, and outperforms std::map with collections
 *		  with fewer items. The beauty of this class is that it can be used as a drop-in replacement
 *		  for std::map, it uses the exact same values, simply replacing the declaration is enough.
 *
 * \typeparam TKey The data type of the key that is stored in the map.
 * \typeparam TValue The data type of the value that is stored in the map. 
 *
 * \author Swen Kooij (Photonios)
 */
template <class TKey, class TValue>
class FastMap : public std::vector<FastMapItem<TKey, TValue>>
{
private:
	// Simple typedef to make accessing the base class easier..
	typedef std::vector<FastMapItem<TKey, TValue>> FastMapBase;

public:
	/*!
	 * \brief Provides access to the base class's at method.
	 *
	 * \param index The index of the item you want to acquire.
 	 *
	 * \returns The fast map item at the specified index.
	 */
	FastMapItem<TKey, TValue> & at(int index)
	{
		return FastMapBase::at(index);
	}

	/*!
 	 * \brief Allows access to the pairs stored inside this map, one specifies the key of the item
 	 *		  to retrieve, and the value is returned as a reference. If the specified key does
	 *		  not exists yet, it will be created, and the specified value will be set.
	 *
	 *		  If the specified key is already set, then the value will be set.
	 *
	 * \param key The key of the item/pair you want to retrieve.
	 *
	 * \returns The value of that is associated with the specified pair.
	 */
	TValue & operator[] (TKey key)
	{
		for(size_t i = 0; i < FastMapBase::size(); i++)
		{
			if(FastMapBase::at(i).first == key)
				return FastMapBase::at(i).second;
		}

		FastMapItem<TKey, TValue> fast_map_item;
		fast_map_item.first = key;
		FastMapBase::push_back(fast_map_item);

		return FastMapBase::at(FastMapBase::size() - 1).first;
	}
};

} // namespace Senergy

#endif // SY_FAST_MAP_H
