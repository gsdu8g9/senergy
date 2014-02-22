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
 
#include <senergy/dns/record_nameserver.h>

namespace Senergy
{
namespace Dns
{

NameServerRecord::NameServerRecord(ResourceRecordBasePtr base) :
	ResourceRecordInterface	(base),
	m_address				()
{

}

bool NameServerRecord::Deserialize(ByteBuffer &buffer)
{
	m_address = Utils::ReadHostnameFromBuffer(buffer);
	
	if(m_address.empty())
		return false;
		
	return true;
}

bool NameServerRecord::Serialize(ByteBuffer &buffer)
{
	if(m_address.empty())
		return false;
		
	std::string encoded_address = Utils::EncodeHostname(m_address);
	buffer.Write(encoded_address);
}

ResourceRecordInterfacePtr NameServerRecord::Create(ResourceRecordBasePtr base)
{
	return ResourceRecordInterface::CreateCast<NameServerRecord>(base);
}

ResourceRecordType NameServerRecord::GetType()
{
	return ResourceRecordType::NS;
}

void NameServerRecord::SetAddress(const std::string &address)
{
	m_address = address;
}

std::string NameServerRecord::GetAddress()
{
	return m_address;
}

} // namespace Dns
} // namespace Senergy