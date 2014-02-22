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

#include <senergy/dns/message_question.h>

namespace Senergy
{
namespace Dns
{

MessageQuestion::MessageQuestion() :
	m_hostname 	(""),
	m_type	  	((unsigned short)ResourceRecordType::A),
	m_class		((unsigned short)ResourceRecordClass::Internet)
{
}

MessageQuestion::MessageQuestion(const std::string &hostname, ResourceRecordType type, ResourceRecordClass clas) :
	m_hostname 	(hostname),
	m_type		((unsigned short)type),
	m_class		((unsigned short)clas)
{
}

MessageQuestionPtr MessageQuestion::Create(const std::string &hostname, ResourceRecordType type, ResourceRecordClass clas)
{
	return MessageQuestionPtr(new MessageQuestion(hostname, type, clas));
}

std::string MessageQuestion::GetHostname()
{
	return m_hostname;
}

void MessageQuestion::SetHostname(const std::string &hostname)
{
	m_hostname = hostname;
}

int MessageQuestion::GetSize()
{
	std::string encoded_hostname = Utils::EncodeHostname(m_hostname);
	return 2 + (int)encoded_hostname.size() + 1;
}

bool MessageQuestion::Deserialize(ByteBuffer &buffer)
{
	if(buffer.GetRemainingSize() < 3)
		return false;
	
	m_hostname = Utils::ReadHostnameFromBuffer(buffer);
	
	if(buffer.GetRemainingSize() < 2)
		return false;

	m_type = buffer.ReadUnsignedShort();
	m_class = buffer.ReadUnsignedShort();

	m_type = Utils::NetworkToHostByteOrder(m_type);
	m_class = Utils::NetworkToHostByteOrder(m_class);
	return true;	
}

bool MessageQuestion::Serialize(ByteBuffer &buffer)
{
	if(m_hostname.empty())
		return false;
	
	std::string encoded_hostname = Utils::EncodeHostname(m_hostname);

	buffer.Write(encoded_hostname);
	buffer.Write(Utils::HostToNetworkByteOrder(m_type));
	buffer.Write(Utils::HostToNetworkByteOrder(m_class));
	
	return true;
}

void MessageQuestion::Dump()
{
	printf("Hostname: %s\n", m_hostname.c_str());
	printf("Type: %hu\n", m_type);
	printf("Class: %hu\n", m_class);
}

ResourceRecordType MessageQuestion::GetType()
{
	return (ResourceRecordType) m_type;
}

void MessageQuestion::SetType(ResourceRecordType type)
{
	m_type = (unsigned short) type;
}

ResourceRecordClass MessageQuestion::GetClass()
{
	return (ResourceRecordClass) m_class;
}

void MessageQuestion::SetClass(ResourceRecordClass clas)
{
	m_class = (unsigned short) clas;
}

} // namespace Dns
} // namespace Senergy
