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
 
#include <senergy/bytebuffer.h>

namespace Senergy
{

ByteBuffer::ByteBuffer() :
	m_data				(NULL),
	m_current_size		(0),
	m_position		 	(0)
{
	__set_size(0);	
}

ByteBuffer::ByteBuffer(unsigned int size) : 
	m_data				(NULL),
	m_current_size		(0),
	m_position		    (0)
{
	__set_size(size);
}

ByteBuffer::~ByteBuffer()
{
	if(m_data != NULL)
	{
		free(m_data);
		m_data = NULL;
		m_current_size = 0;
	}
}

bool ByteBuffer::IsEmpty()
{
	return (m_current_size > 0);
}

int ByteBuffer::Size()
{
	return (int)m_current_size;
}

int ByteBuffer::GetPosition()
{
	return (int)m_position;
}

int ByteBuffer::GetRemainingSize()
{
	return Size() - GetPosition();
}

bool ByteBuffer::SetPosition(int position)
{
	if(position < 0 || position > (int) m_current_size)
		return false;

	m_position = position;
	return true;
}

bool ByteBuffer::SetPosition(unsigned int position)
{
	return SetPosition((int)position);
}

bool ByteBuffer::IncreasePosition(int amount /* = 1 */)
{
	return SetPosition((int)GetPosition() + amount);
}

bool ByteBuffer::DecreasePosition(int amount /* = 1 */)
{
	return SetPosition((int)GetPosition() - amount);
}

void ByteBuffer::Reserve(unsigned int size)
{
	if(m_data == NULL)
		__set_size(0);

	if(m_current_size >= size || size <= 0)
		return;

	__set_size(size);
}

void ByteBuffer::Reserve(int size)
{
	if(size <= 0)
		return;
		
	Reserve((unsigned int)size);
}

void ByteBuffer::Write(char *data, unsigned int size)
{
	Write((void*)data, size);
}

void ByteBuffer::Write(char *data, int size)
{
	Write((void*)data, size);
}

void ByteBuffer::Write(void *data, unsigned int size)
{
	if(data == NULL || size <= 0)
		return;

	unsigned int offset = m_position;
	
	unsigned int new_size = m_current_size + size;
	Reserve(new_size);
	
	memcpy(m_data + offset, data, size);
	m_position += size;
}

void ByteBuffer::Write(void *data, int size)
{
	if(size <= 0)
		return;
		
	Write(data, (unsigned int)size);
}

void ByteBuffer::Write(const std::string &data, StringOptions options /* = StringOptions::ExcludeNullTerminator */)
{
	switch(options)
	{
		case StringOptions::ExcludeNullTerminator:
			Write((char *)data.c_str(), (unsigned int)data.size());
			break;
		
		default:
			Write((char *)data.c_str(), (unsigned int)data.size() + 1);
			break;
	}
}

void ByteBuffer::Write(int value)
{
	__write_native_type<int>(value);
}

void ByteBuffer::Write(unsigned int value)
{
	__write_native_type<unsigned int>(value);
}

void ByteBuffer::Write(char value)
{
	__write_native_type<char>(value);
}

void ByteBuffer::Write(unsigned char value)
{
	__write_native_type<unsigned char>(value);
}

void ByteBuffer::Write(short value)
{
	__write_native_type<short>(value);
}

void ByteBuffer::Write(unsigned short value)
{
	__write_native_type<unsigned short>(value);
}

void ByteBuffer::WriteNop()
{
	__write_native_type<char>(0);
}

bool ByteBuffer::Read(char *buffer, int size)
{
	if(buffer == NULL || size <= 0)
		return false;

	int buffer_end_offset = m_position + size;
	if(buffer_end_offset > (int) m_current_size)
		return false;

	memcpy(buffer, m_data + m_position, size);
	m_position += size;

	return true; 
}

bool ByteBuffer::Read(char *buffer, unsigned int size)
{
	return Read(buffer, (int)size);
}

int ByteBuffer::ReadInt()
{
	return __read_native_type<int>();
}

unsigned int ByteBuffer::ReadUnsignedInt()
{
	return __read_native_type<unsigned int>();
}

char ByteBuffer::ReadChar()
{
	return __read_native_type<char>();
}

unsigned char ByteBuffer::ReadUnsignedChar()
{
	return __read_native_type<unsigned char>();
}

short ByteBuffer::ReadShort()
{
	return __read_native_type<short>();
}

unsigned short ByteBuffer::ReadUnsignedShort()
{
	return __read_native_type<unsigned short>();
}

std::string ByteBuffer::ReadString(unsigned int max_length /* = 0 */)
{
	std::string result_string = "";	

	while(GetRemainingSize() > 0)
	{
		if(result_string.size() >= max_length)
			break;

		char current_character = ReadChar();
		if(current_character == 0)
			break;

		result_string += current_character;
	}

	return result_string;
}

std::string ByteBuffer::ReadAll()
{
	if(m_current_size <= 0)
		return "";
		
	return std::string(m_data, m_current_size);
}

void ByteBuffer::__set_size(unsigned int new_size)
{	
	if(m_current_size >= new_size)
		return;

	unsigned int size_increment = new_size - m_current_size;

	m_data = (char*) realloc(m_data, sizeof(char) * new_size);
	memset(m_data + m_current_size, 0, size_increment);

	m_current_size = new_size;
}

void ByteBuffer::DumpHexadecimal()
{
	int current_position = GetPosition();
	int current_remaining_bytes = GetRemainingSize();

	if(current_remaining_bytes <= 0)
		return;

	int line_count = 0;

	for(int i = 0; i < current_remaining_bytes; ++i)
	{
		printf("%02X ", ReadChar());
		line_count++;

		if(line_count >= 35)
		{
			printf("\n");
			line_count = 0;
		}
	} 
	
	printf("\n");
	SetPosition(current_position);
}

void ByteBuffer::DumpHexadecimal(int start, int amount)
{
	int current_position = GetPosition();
	SetPosition(start);
	
	int current_remaining_bytes = GetRemainingSize();
	
	if(current_remaining_bytes > amount)
		current_remaining_bytes = amount;

	if(current_remaining_bytes <= 0)
		return;

	int line_count = 0;
 
	for(int i = 0; i < current_remaining_bytes; ++i)
	{
		printf("%02X ", ReadChar());
		line_count++;

		if(line_count >= 35)
		{
			printf("\n");
			line_count = 0;
		}
	} 
	
	printf("\n");
	SetPosition(current_position);
}

bool ByteBuffer::CopyTo(ByteBuffer &buffer, int amount)
{
	if(amount > GetRemainingSize())
		return false;

	buffer.Reserve(amount);	
	memcpy(buffer.m_data + buffer.GetPosition(), m_data + GetPosition(), amount);

	IncreasePosition(amount); 
	return true;
}

bool ByteBuffer::CopyTo(ByteBufferPtr buffer, int amount)
{
	if(amount > GetRemainingSize())
		return false;

	buffer->Reserve(amount);	
	memcpy(buffer->m_data + buffer->GetPosition(), m_data + GetPosition(), amount); 

	IncreasePosition(amount);
	return true;
}

bool ByteBuffer::CopyAllTo(ByteBuffer &buffer)
{
	int current_pos = GetPosition();

	CopyTo(buffer, GetRemainingSize());
	SetPosition(current_pos);
	return true;
}

bool ByteBuffer::CopyAllTo(ByteBufferPtr buffer)
{
	int current_pos = GetPosition();

	CopyTo(buffer, GetRemainingSize());
	SetPosition(current_pos);
	return true;
}

bool ByteBuffer::HasReachedEnd()
{
	if(GetRemainingSize() <= 0)
		return true;
		
	return false;
}

void ByteBuffer::Clear()
{
	if(m_data != NULL)
		free(m_data);

	m_data = NULL;
	m_current_size = 0;
	m_position = 0;
}

char * ByteBuffer::GetRawData()
{
	return m_data;
}

} // namespace Senergy