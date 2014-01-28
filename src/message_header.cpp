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

#include <senergy/dns/message_header.h>

namespace Senergy
{
namespace Dns
{

MessageHeader::MessageHeader() :
	m_valid	(true)
{
}

bool MessageHeader::IsValid()
{
	return m_valid;
}

int MessageHeader::GetSize()
{
	return sizeof(MessageHeaderFields);
}

MessageHeader MessageHeader::Deserialize(ByteBuffer &buffer) // static
{
	MessageHeader return_header;
	return_header.m_valid = false;

	int header_size = return_header.GetSize();

	if(buffer.GetRemainingSize() < header_size)
		return return_header;

	if(!buffer.Read((char*)&return_header.Fields, header_size))
		return return_header;

	return_header.m_valid = true;
	return return_header;
}

bool MessageHeader::Serialize(ByteBuffer &buffer)
{	
	if(!IsValid())
		return false;

	int header_size = GetSize();
	buffer.Reserve(header_size);

	buffer.Write((char *)&this->Fields, header_size);
	return true;
}

} // namespace Dns
} // namespace Senergy
