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

#ifndef SY_DNS_ID_FACTORY_H
#define SY_DNS_ID_FACTORY_H

#include <stdlib.h>
#include <mutex>
#include <random>
#include <senergy/circular_buffer.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Static global factory that is used to generate random identifiers
 *		  for DNS messages/packets. This is to ensure, each ID that is generated
 *		  is unique.
 *
 * \note This static class is thread-safe.
 *
 * \author Swen Kooij (Photonios)
 */
class IdFactory
{
public:
	/*!
	 * \brief Defines the maximum number of generated ID's that we keep in our buffer, before
	 *		  we throw them out.
	 */
	static int MaximumBufferSize;

public:
	/*!
	 * \brief Generates a new random identifier to be used as the unique identifier
	 *		  for a DNS message/packet.
	 *
	 * \returns A unique, random identifier for a DNS message/packet.
	 */
	static unsigned short GenerateId();

private:
	// Makes sure that the number wasn't generated already
	static bool __exists(unsigned short id);

private:
	// Simple typedef for our circular buffer
	typedef CircularBuffer<unsigned short> GeneratedIdBuffer;

private:
	// Keeps a list of numbers we generated
	static GeneratedIdBuffer s_generated_numbers;

	// Mutex for generating a random number
	static std::mutex s_generate_id_lock;
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_ID_FACTORY_H
