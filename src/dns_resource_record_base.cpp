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

#include <senergy/dns/resource_record_base.h>

namespace Senergy
{
namespace Dns
{

ResourceRecordBase::ResourceRecordBase() :
	m_hostname	(""),
	m_type		(ResourceRecordType::A),
	m_class		(ResourceRecordClass::Internet),
	m_ttl		(0),
	m_rd_length	(0)
{
}

ResourceRecordBasePtr ResourceRecordBase::Create()
{
	return ResourceRecordBasePtr(new ResourceRecordBase());
}

bool ResourceRecordBase::Deserialize(ByteBuffer &buffer)
{
	if(buffer.GetRemainingSize() < 4)
		return false;

	m_hostname = Utils::ReadHostnameFromBuffer(buffer);

	if(m_hostname.size() <= 0)
		return false;

	if(buffer.GetRemainingSize() < 4)
		return false;

	m_type 		= (ResourceRecordType) buffer.ReadUnsignedShort();
	m_class 	= (ResourceRecordClass) buffer.ReadUnsignedShort();
	m_ttl 		= buffer.ReadUnsignedInt();
	m_rd_length = buffer.ReadUnsignedShort();

	m_type 		= (ResourceRecordType) Utils::NetworkToHostByteOrder((unsigned short)m_type);
	m_class 	= (ResourceRecordClass) Utils::NetworkToHostByteOrder((unsigned short)m_class);
	m_ttl 		= Utils::NetworkToHostByteOrder(m_ttl);
	m_rd_length = Utils::NetworkToHostByteOrder(m_rd_length);

	return true;
}

bool ResourceRecordBase::Serialize(ByteBuffer &buffer)
{
	if(m_hostname.empty() || m_rd_length <= 0)
		return false;

	std::string encoded_hostname = Utils::EncodeHostname(m_hostname);
	buffer.Write(encoded_hostname);

	buffer.Write(Utils::HostToNetworkByteOrder((unsigned short)m_type));
	buffer.Write(Utils::HostToNetworkByteOrder((unsigned short)m_class));
	buffer.Write(Utils::HostToNetworkByteOrder(m_ttl));
	buffer.Write(Utils::HostToNetworkByteOrder(m_rd_length));
	return true;
}

std::string ResourceRecordBase::GetHostname()
{
	return m_hostname;
}

void ResourceRecordBase::SetHostname(const std::string hostname)
{
	m_hostname = hostname;
}

ResourceRecordType ResourceRecordBase::GetType()
{
	return m_type;
}

void ResourceRecordBase::SetType(ResourceRecordType type)
{
	m_type = type;
}

ResourceRecordClass ResourceRecordBase::GetClass()
{
	return m_class;
}

void ResourceRecordBase::SetClass(ResourceRecordClass clas)
{
	m_class = clas;
}

bool ResourceRecordBase::NeedsCaching()
{
	return (m_ttl > 0);
}

int ResourceRecordBase::GetMaxCachingTime()
{
	return (int)m_ttl;
}

int ResourceRecordBase::GetResourceSize()
{
	return (int)m_rd_length;
}

void ResourceRecordBase::Dump()
{
	printf("Name: %s\n", m_hostname.c_str());
	printf("Type: %hu\n", (unsigned short)m_type);
	printf("Class: %hu\n", (unsigned short)m_class);
	printf("TTL: %u\n", m_ttl);
	printf("RDLength: %hu\n", m_rd_length);
}


} // namespace Dns
} // namespace Senergy
