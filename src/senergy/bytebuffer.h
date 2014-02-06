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
 
#ifndef SY_BYTE_BUFFER
#define SY_BYTE_BUFFER

#include <string>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <senergy/print.h>

namespace Senergy
{

/*!
 * \brief A dynamiclly sized buffer for binary data. Resizes the underlying buffer when new data is written.
 *	 	  Makes it easier to write to buffers that already contain data.
 * 
 * \author Swen Kooij (Photonios)
 */
class ByteBuffer
{

// HUGE VIOLATION OF DESIGN -> But it's faster because the socket 
//							   can directly access the underlying buffer,
// 							   thus preventing memory allocations and copies.
friend class Socket;

public:
	/*! 
	 * \brief Initializes a new instance of the ByteBuffer class. The intial buffer size is 0 bytes.
	 */
	ByteBuffer();
	
	/*!
	 * \brief Initializes a new instance of the ByteBuffer class with the specified size. After initialization,
	 *		  the buffer is enlarged to the specified size.
	 */
	ByteBuffer(unsigned int size);

	/*!
	 * \brief The ByteBuffer's destructor. Free's the underlying buffer, and cleans up used resources.
	 */
	~ByteBuffer();
	
	/*!
 	 * \brief Checks if the buffer is empty and returns true when the buffer is empty
	 *		  and false when the buffer is not empty.
	 *
	 * \returns A boolean indicating whether the buffer is empty. True is returned when
	 *			the buffer is empty and false when it is not.
	 */
	bool IsEmpty();
	
	/*!
 	 * \brief Gets the size of the buffer. This is not the same as the data size.
	 *
	 * \returns The size of the buffer, in bytes.
	 */	
	int  Size();

	/*!
  	 * \brief Gets the amount of bytes that can be read until the end of the buffer
	 *		  is reached.
	 *
	 * \returns The amount of bytes that can be read until the end of the buffer is reached.
	 */
	int  GetRemainingSize();

	/*!
 	 * \brief Gets the current position within the byte buffer. The position
	 *		  is the offset within the buffer that writing/reading starts at.
	 *
	 * \returns The position within the byte buffer.
	 */
	int GetPosition();

	/*!
	 * \brief Sets the current position within the byte buffer. The position
	 *		  is the offset within the buffer that writing/reading starts at.
	 *
	 * \param position The offset to set the current position to. The new offset
	 *				   must be 0 and not exceed the size of the buffer.
	 *
 	 * \returns A boolean indicating whether setting the position to the 
	 *			requested offset succeseeded. True is returned when the operation
	 *			succeseeded and false is returned when the operation failed.
	 */
	bool SetPosition(int position);

	/*!
	 * \brief Increases the position by the specified amount of bytes.
	 *
	 * \param amount The amount of bytes to increase the position with,
	 *				 by default this is 1.
	 *
 	 * \returns A boolean indicating whether setting the position to the 
	 *			requested offset succeseeded. True is returned when the operation
	 *			succeseeded and false is returned when the operation failed.
	 */
	bool IncreasePosition(int amount = 1);

	/*!
	 * \brief Decreases the position by the specified amount of bytes.
	 *
	 * \param amount The amount of bytes to decrease the position with,
	 *				 by default this is 1.
	 *
 	 * \returns A boolean indicating whether setting the position to the 
	 *			requested offset succeseeded. True is returned when the operation
	 *			succeseeded and false is returned when the operation failed.
	 */
	bool DecreasePosition(int amount = 1);

	/*!
	 * \brief Sets the current position within the byte buffer. The position
	 *		  is the offset within the buffer that writing/reading starts at.
	 *
	 * \param position The offset to set the current position to. The new offset
	 *				   must be 0 and not exceed the size of the buffer.
	 *
 	 * \returns A boolean indicating whether setting the position to the 
	 *			requested offset succeseeded. True is returned when the operation
	 *			succeseeded and false is returned when the operation failed.
	 */
	bool SetPosition(unsigned int position);
	
	/*!
 	 * \brief Assures that the buffer is of the specified size and enlarges the buffer
	 *		  when the current size of the buffer is below the specified, desired size.
	 *
	 * \param size The desired size of the buffer.
	 */
	void Reserve(unsigned int size);

	/*!
 	 * \brief Assures that the buffer is of the specified size and enlarges the buffer
	 *		  when the current size of the buffer is below the specified, desired size.
	 *
	 * \param size The desired size of the buffer.
	 */
	void Reserve(int size);
	
	/*!
 	 * \brief Writes the specified data of the specified size to the buffer. The buffer
	 *		  is automaticlly resized when the specified data does not fit into the current
	 *		  buffer.
	 *
	 * \note Increases the position by the specified size.
	 *
	 * \param data The data to write to the buffer. If the specified data is NULL,
	 *			   no data will be written.
	 * \param size The size of the data to write.
	 */
	void Write(char *data, unsigned int size);

	/*!
 	 * \brief Writes the specified data of the specified size to the buffer. The buffer
	 *		  is automaticlly resized when the specified data does not fit into the current
	 *		  buffer.
	 *
	 * \note Increases the position by the specified size.
	 *
	 * \param data The data to write to the buffer. If the specified data is NULL,
	 *			   no data will be written.
	 * \param size The size of the data to write.
	 */
	void Write(void *data, unsigned int size);

	/*!
 	 * \brief Writes the specified data of the specified size to the buffer. The buffer
	 *		  is automaticlly resized when the specified data does not fit into the current
	 *		  buffer.
	 *
	 * \note Increases the position by the specified size.
	 *
	 * \param data The data to write to the buffer. If the specified data is NULL,
	 *			   no data will be written.
	 * \param size The size of the data to write.
	 */
	void Write(char *data, int size);

	/*!
 	 * \brief Writes the specified data of the specified size to the buffer. The buffer
	 *		  is automaticlly resized when the specified data does not fit into the current
	 *		  buffer.
	 *
	 * \note Increases the position by the specified size.
	 *
	 * \param data The data to write to the buffer. If the specified data is NULL,
	 *			   no data will be written.
	 * \param size The size of the data to write.
	 */
	void Write(void *data, int size);

	/*!
	 * \brief Writes the specified string to the buffer. The buffer is automaticlly resized when
	 *		  the specified string does not fit into the buffer.
	 *
	 * \note Increases the position by the size of the specified string.
	 * \note Accounts for the string termination character (\0).
	 *
	 * \param data The string to write to the buffer.
	 */
	void Write(const std::string &data);

	/*!
	 * \brief Writes the specified value to the buffer. The buffer is automaticlly resized when
	 *		  the specified value does not fit into the buffer.
	 *
	 * \note Increases the position by the size of the specified value.
	 *
	 * \param value The value to write to the buffer.
	 */
	void Write(int value);

	/*!
	 * \brief Writes the specified value to the buffer. The buffer is automaticlly resized when
	 *		  the specified value does not fit into the buffer.
	 *
	 * \note Increases the position by the size of the specified value.
	 *
	 * \param value The value to write to the buffer.
	 */
	void Write(unsigned int value);

	/*!
	 * \brief Writes the specified value to the buffer. The buffer is automaticlly resized when
	 *		  the specified value does not fit into the buffer.
	 *
	 * \note Increases the position by the size of the specified value.
	 *
	 * \param value The value to write to the buffer.
	 */
	void Write(char value);

	/*!
	 * \brief Writes the specified value to the buffer. The buffer is automaticlly resized when
	 *		  the specified value does not fit into the buffer.
	 *
	 * \note Increases the position by the size of the specified value.
	 *
	 * \param value The value to write to the buffer.
	 */
	void Write(unsigned char value);

	/*!
	 * \brief Writes the specified value to the buffer. The buffer is automaticlly resized when
	 *		  the specified value does not fit into the buffer.
	 *
	 * \note Increases the position by the size of the specified value.
	 *
	 * \param value The value to write to the buffer.
	 */
	void Write(short value);

	/*!
	 * \brief Writes the specified value to the buffer. The buffer is automaticlly resized when
	 *		  the specified value does not fit into the buffer.
	 *
	 * \note Increases the position by the size of the specified value.
	 *
	 * \param value The value to write to the buffer.
	 */
	void Write(unsigned short value);

	/*!
 	 * \brief Reads the specified amount of bytes from the buffer and copies
	 *		  it into the specified buffer.
	 *
	 * \param buffer The buffer to write to.
	 * \param size   The amount of bytes to read from the buffer.
	 *
	 * \returns A boolean indicating whether reading succeseeded. True is returned
	 *	 		when reading succeseeded and false when reading failed.
	 */
	bool Read(char *buffer, int size);

	/*!
 	 * \brief Reads the specified amount of bytes from the buffer and copies
	 *		  it into the specified buffer.
	 *
	 * \param buffer The buffer to write to.
	 * \param size   The amount of bytes to read from the buffer.
	 *
	 * \returns A boolean indicating whether reading succeseeded. True is returned
	 *	 		when reading succeseeded and false when reading failed.
	 */
	bool Read(char *buffer, unsigned int size); 

	/*!
	 * \brief Reads all remaining bytes from the buffer.
	 *
	 * \param buffer   The buffer to write the acquired data to, make
	 *				   sure the buffer is at least the size of
	 *				   of the specified maximum size.
	 * \param max_size The maximum amount of bytes to copy into	the specified
	 *				   buffer, the size of the specified buffer.
	 *
	 * \returns A boolean indicating whether writing the remainging 
	 *			bytes to the specified buffer was a success.
	 */
	bool ReadRemaining(char *buffer, int max_size);

	/*!
	 * \brief Reads all remaining bytes from the buffer.
	 *
	 * \param buffer   The buffer to write the acquired data to, make
	 *				   sure the buffer is at least the size of
	 *				   of the specified maximum size.
	 * \param max_size The maximum amount of bytes to copy into	the specified
	 *				   buffer, the size of the specified buffer.
	 *
	 * \returns A boolean indicating whether writing the remainging 
	 *			bytes to the specified buffer was a success.
	 */
	bool ReadRemaining(char *buffer, unsigned int max_size);
	
	/*!
 	 * \brief Reads an integer from the buffer.
	 *
	 * \returns The integer that was read from the buffer. -1 is returned
	 *			when reading failed.
  	 */
	int ReadInt();

	/*!
 	 * \brief Reads an unsigned integer from the buffer.
	 *
	 * \returns The unsigned integer that was read from the buffer. 0 is returned
	 *			when reading failed.
  	 */
	unsigned int ReadUnsignedInt();

	/*!
 	 * \brief Reads a char from the buffer.
	 *
	 * \returns The char that was read from the buffer. -1 is returned
	 *			when reading failed.
  	 */
	char ReadChar();


	/*!
 	 * \brief Reads an unsigned char from the buffer.
	 *
	 * \returns The unsigned char that was read from the buffer. 0 is returned
	 *			when reading failed.
  	 */
	unsigned char ReadUnsignedChar();

	/*!
 	 * \brief Reads a short from the buffer.
	 *
	 * \returns The short that was read from the buffer. -1 is returned
	 *			when reading failed.
  	 */
	short ReadShort();

	/*!
 	 * \brief Reads an unsigned short from the buffer.
	 *
	 * \returns The unsigned short that was read from the buffer. 0 is returned
	 *			when reading failed.
  	 */
	unsigned short ReadUnsignedShort();
	
	/*!
	 * \brief Attempts to read a string for the buffer until a string termination character, or
	 *		  the end of the buffer is encountered.
	 *
	 * \param max_length Specifies the maximum length of the string being returned. Specifying
	 *					 zero disables this functionality.
	 *
	 * \returns The string that was read, if something went wrong, or the end of the buffer was
	 *		    reached, everything that was read so far will be returned. If the buffer
	 *			is empty, or there are no more bytes left to read, an empty string will
	 *			be returned.
 	 */
	std::string ReadString(unsigned int max_length = 0);
	
	/*!
 	 * \brief Reads the contents of the buffer from start to end and returns the contents
	 *		  as a string.
	 *
	 * \note This does not affect the current position.
	 *
	 * \returns The contents of the buffer as a string.
	 */
	std::string ReadAll();

	/*!
  	 * \brief Dump everything from the current position to the standard output, where
	 *		  each byte in the buffer is dumped in it's hexadecimal representation. Each
	 *		  byte will be separated by a space and after 35 bytes, a new line is created.
	 */
	void DumpHexadecimal();
	
private:
	// Sets the size of the buffer, by reallocating memory but checks
	// if the reallocation is needed.
	void __set_size(unsigned int new_size);
	
	// Used to write native data types to the buffer
	template<typename T>
	void __write_native_type(T value)
	{
		unsigned int value_size = sizeof(T);

		char *temp_buffer = (char*) malloc(value_size);
		memcpy(temp_buffer, (char*)&value, value_size);

		Write(temp_buffer, value_size);
		free(temp_buffer);
	}

	// Used to read native data types from the buffer
	template<typename T>
	T __read_native_type()
	{
		int type_size = sizeof(T);
		char *read_buffer = (char *)malloc(type_size);

		T return_value{};

		if(!Read(read_buffer, type_size))
		{
			free(read_buffer);
			return return_value;
		}

		return_value = *(reinterpret_cast<T *>(read_buffer));
		free(read_buffer);

		return return_value;
	}
	
private:
	// The underlying buffer, holds the actual data.
	char *				m_data;

	// The current size of the underlying buffer.
	unsigned int		m_current_size;

	// Denotes the current position within the buffer
	unsigned int		m_position;
};

/*!
 * \brief A simple typedef for a shared pointer to a ByteBuffer instance.
 */
typedef std::shared_ptr<ByteBuffer> ByteBufferPtr;

} // namespace Senergy

#endif // SY_BYTE_BUFFER
