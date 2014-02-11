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

#include <senergy/dns/record_ipv4_address.h>

namespace Senergy
{
namespace Dns
{

bool IPV4Record::Serialize(ByteBuffer &buffer)
{
	unsigned int serialized_address = Socket::IPV4AddressToBinary(m_address);
	if(serialized_address == 0xffffffff)
		return false;

	buffer.Write(serialized_address);
	return true;
}

bool IPV4Record::Deserialize(ByteBuffer &buffer)
{
	if(buffer.GetRemainingSize() < (int)sizeof(unsigned int))
		return false;

	if(GetBase().GetResourceSize() < (int)sizeof(unsigned int))
		return false;

	unsigned int binary = buffer.ReadUnsignedInt();
	m_address = Socket::IPV4AddressFromBinary(binary);

	if(m_address.empty())
		return false;

	return true;
}

ResourceRecordInterfacePtr IPV4Record::Create(ResourceRecordBase &base)
{
	return std::dynamic_pointer_cast<ResourceRecordInterface>(std::shared_ptr<IPV4Record>(new IPV4Record(base)));
}

ResourceRecordType IPV4Record::GetType()
{
	ResourceRecordType::A;
}

void IPV4Record::SetAddress(const std::string &address)
{
	m_address = address;
}

std::string IPV4Record::GetAddress()
{
	return m_address;
}

} // namespace Dns
} // namespace Senergy
