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

template <class TKey, class TValue>
struct FastMapItem
{
	TKey first;
	TValue second;
};

template <class TKey, class TValue>
class FastMap : public std::vector<FastMapItem<TKey, TValue>>
{
private:
	typedef std::vector<FastMapItem<TKey, TValue>> FastMapBase;

public:
	TValue & at(TKey value)
	{
		return *this[value];
	}

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
