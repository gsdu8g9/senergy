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
	if(position < 0 || position > m_current_size)
		return false;

	m_position = position;	
}

bool ByteBuffer::SetPosition(unsigned int position)
{
	return SetPosition((int)position);
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

void ByteBuffer::Write(const std::string &data)
{
	Write((char *)data.c_str(), (unsigned int)data.size());
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

bool ByteBuffer::Read(char *buffer, int size)
{
	if(buffer == NULL || size <= 0)
		return false;

	int buffer_end_offset = m_position + size;
	if(buffer_end_offset > m_current_size)
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
		
	m_data = (char*) realloc(m_data, sizeof(char) * new_size);
	m_current_size = new_size;
}

} // namespace Senergy

