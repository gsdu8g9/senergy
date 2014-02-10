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

#include <senergy/dns/utils.h>

namespace Senergy
{
namespace Dns
{

std::string Utils::EncodeHostname(const std::string &hostname)
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

std::string Utils::DecodeHostname(const std::string &hostname)
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
			int index = i + 1;
			if(index > hostname_len - 1)
				return new_hostname;

			new_hostname += hostname[i + 1];
			i++;
		}

		if(i != (hostname_len - 1)) // skip last
			new_hostname += ".";
	}

	return new_hostname;
}

unsigned short Utils::HostToNetworkByteOrder(unsigned short value)
{
	return htons(value);
}

unsigned short Utils::NetworkToHostByteOrder(unsigned short value)
{
	return ntohs(value);
}

unsigned char Utils::HostToNetworkByteOrder(unsigned char value)
{
	return htons(value);
}

unsigned char Utils::NetworkToHostByteOrder(unsigned char value)
{
	return ntohs(value);
}

unsigned int Utils::HostToNetworkByteOrder(unsigned int value)
{
	return htons(value);
}

unsigned int Utils::NetworkToHostByteOrder(unsigned int value)
{
	return ntohs(value);
}

std::string Utils::ReadHostnameFromBuffer(ByteBuffer &buffer)
{
	if(buffer.GetRemainingSize() < 1)
		return "";
		
	unsigned char first_byte = buffer.ReadUnsignedChar();
	if(first_byte >= 192) // 192 = 11 = pointer
	{
		int offset = (int) buffer.ReadUnsignedChar();

		int current_buffer_position = buffer.GetPosition();
		buffer.SetPosition(offset);
		
		std::string hostname = buffer.ReadString(256);
		hostname = DecodeHostname(hostname);

		buffer.SetPosition(current_buffer_position);
		return hostname;
	}
	else
	{
		buffer.DecreasePosition();

		std::string hostname = buffer.ReadString(256);
		hostname = DecodeHostname(hostname);

		return hostname;
	}

	return "";
}

} // namespace Dns
} // namespace Senergy
