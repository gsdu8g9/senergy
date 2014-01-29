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
#include <senergy/convert.h>

namespace Senergy
{
namespace Dns
{

MessageQuestion::MessageQuestion()
{
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
	std::string encoded_hostname = __encode_hostname(m_hostname);
	return 2 + (int)encoded_hostname.size() + 1;
}

bool MessageQuestion::Deserialize(ByteBuffer &buffer)
{
	if(buffer.GetRemainingSize() < 3)
		return false;

	m_hostname = "";
	while(buffer.GetRemainingSize() > 0 && m_hostname.size() <= 256)
	{
		char current_character = buffer.ReadChar();
		if(current_character == 0)
			break;

		m_hostname += current_character;
	}

	m_hostname = __decode_hostname(m_hostname);
	
	if(buffer.GetRemainingSize() < 2)
		return false;

	m_type = buffer.ReadUnsignedShort();
	m_class = buffer.ReadUnsignedShort();
	return true;	
}

bool MessageQuestion::Serialize(ByteBuffer &buffer)
{
	if(m_hostname.empty())
		return false;
	
	std::string encoded_hostname = __encode_hostname(m_hostname);

	int encoded_hostname_len = (int) encoded_hostname.size();

	buffer.Write((char *)encoded_hostname.c_str(), encoded_hostname_len + 1); // accounting for \0
	buffer.Write(m_type);
	buffer.Write(m_class);

	return true;
}

void MessageQuestion::Dump()
{
	printf("Hostname: %s\n", m_hostname.c_str());
	printf("Type: %hu\n", m_type);
	printf("Class: %hu\n", m_class);
}

std::string MessageQuestion::__encode_hostname(const std::string &hostname)
{
	if(hostname.empty())
		return "";

	/* 
		www.google.come -> 3www6google3com
		where 3, 6, 3 are NOT ASCII but just decimals
	 */

	size_t hostname_len = hostname.size();

	std::string new_hostname = " ";
	new_hostname += hostname;

	int previous_dot_pos = 0;
	int segment_count = 0;

	for(size_t i = 1; i < hostname_len + 1; ++i)
	{
		if(i == hostname_len) // last char
			new_hostname[previous_dot_pos] = ++segment_count;

		if(new_hostname[i] == '.')
		{
			new_hostname[previous_dot_pos] = segment_count;
			previous_dot_pos = (int)i;
			segment_count = 0;
			continue;
		}

		new_hostname[i] = tolower(new_hostname[i]);
		segment_count++;
	}

	return new_hostname;
}

std::string MessageQuestion::__decode_hostname(const std::string &hostname)
{
	if(hostname.empty())
		return "";

	/*
	  	3www6google3com -> www.google.com
		where 3, 6, 3 are NOT ASCII, but just decimals
	 */
	
	int hostname_len = (int) hostname.size();
	std::string new_hostname = "";

	for(int i = 0; i < hostname_len; ++i)
	{
		int segment_length = hostname[i];

		for(int y = 0; y < segment_length; ++y)
		{
			new_hostname += hostname[i + 1];
			i++;
		}

		if(i != (hostname_len - 1)) // skip last
			new_hostname += ".";
	}

	return new_hostname;
}

void MessageQuestion::__update_host_to_fields(const std::string &hostname)
{	
	/*char *raw_hostname = (char*) hostname.c_str();
	int hostname_len = (int)hostname.size();

	this->Fields.Hostname = (unsigned char*) malloc(hostname_len + 1);

	memcpy(this->Fields.Hostname, raw_hostname, hostname_len);
	this->Fields.Hostname[hostname_len] = '\0';&*/
}

} // namespace Dns
} // namespace Senergy
