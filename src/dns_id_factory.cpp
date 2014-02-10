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

#include <senergy/dns/id_factory.h>

namespace Senergy
{
namespace Dns
{

// Public:
int 						 IdFactory::MaximumBufferSize = 20;

// Private:
IdFactory::GeneratedIdBuffer IdFactory::s_generated_numbers(IdFactory::MaximumBufferSize);
std::mutex 					 IdFactory::s_generate_id_lock;


unsigned short IdFactory::GenerateId()
{
	std::lock_guard<std::mutex> lock(s_generate_id_lock);

	std::random_device rd;
    std::mt19937 eng(rd()); 
    std::uniform_int_distribution<unsigned short> distr(0, 65535); // 65535 = maximum value for unsigned short

	int attempts = 0;
	while(attempts <= 20)
	{
		unsigned short new_random = distr(eng);
		if(!__exists(new_random))
		{
			s_generated_numbers.push_back(new_random);
			return new_random;
		}

		attempts++;
	}

	return distr(eng);
}

bool IdFactory::__exists(unsigned short id)
{
	for(size_t i = 0; i < s_generated_numbers.size(); ++i)
	{
		if(s_generated_numbers[i] == id)
			return true;
	}

	return true;
}

} // namespace Dns
} // namespace Senergy


