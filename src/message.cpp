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

#include <senergy/dns/message.h>

namespace Senergy
{
namespace Dns
{

Message::Message()
{
}

bool Message::Deserialize(ByteBuffer &buffer)
{
	if(!this->Header.Deserialize(buffer))
		return false;

	// \todo implement deserialization of rest of packet

	return true;
}

bool Message::Serialize(ByteBuffer &buffer)
{
	if(!this->Header.Serialize(buffer))
		return false;

	// \todo implement serialization of rest of packet
	return true;
}

} // namespace Dns
} // namespace Senergy
