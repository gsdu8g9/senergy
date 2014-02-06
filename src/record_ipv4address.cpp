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

#include <senergy/dns/record_ipv4address.h>

namespace Senergy
{
namespace Dns
{
namespace Records
{

IPV4Address::IPV4Address()
{
}

bool IPV4Address::Deserialize(ByteBuffer &buffer)
{
	if(buffer.GetRemainingSize() < BaseClass::m_rd_length)
	{
		printf("JJJJJ: %i - %i\n", (int)buffer.GetRemainingSize(), (int) BaseClass::m_rd_length);
		return false;
	}

	return true;
}

bool IPV4Address::Serialize(ByteBuffer &buffer)
{
 	// \todo implement serialization of address here

	return true;
}

void IPV4Address::Dump()
{
	BaseClass::Dump();
	printf("IP: -\n");
}

} // namespace Records
} // namespace Dns
} // namespace Senergy
