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

#ifndef SY_DNS_MESSAGE_H
#define SY_DNS_MESSAGE_H

#include <senergy/dns/message_header.h>
#include <senergy/dns/message_question.h>
#include <senergy/bytebuffer.h>
#include <algorithm>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Represents a DNS packet as described in section 4 of RFC-1035. A DNS packet is the standard
 *		  message format that is transmitted and received by DNS clients and hosts.
 * 
 * \author Swen Kooij (Photonios)
 */
class Message
{
public:
	/*!
	 * \brief Initializes a new instance of the Message class, with default values, without questions,
	 *		  answers, authorities and additionals.
 	 */
	Message();

	/*!
	 * \brief Deserializes a DNS packet header from the specified buffer into
	 *		  this instance.
	 *
	 * \note The DNS packet header is 12 bytes, the specified buffer should
	 *		 have at least 12 bytes left to read. Deserialization will fail
	 *		 when there are less then 12 bytes left to read.
	 *
	 * \note This will overwrite all contents currently in this message.
	 *
	 * \note If the operation suceseeded, the buffer's position will have
	 *		 at least advanced 12 bytes.
	 *
	 * \param buffer The buffer to read from, should contain a DNS packet message.
	 * 
	 * \returns A boolean indicating whether deserialization was succesfull. True is returned
	 *			when it was a success and false is returned when it failed.
	 */
	bool Deserialize(ByteBuffer &buffer);
	
	/*!
 	 * \brief Serializes this DNS message (packet) into the specified ByteBuffer.
	 *
	 * \param buffer The buffer to write the serialized DNS message to.
	 * 
	 * \returns A boolean indicating whether serialization was succesfull. True is returned
	 *			when it was a success and false is returned when it failed.
	 */
	bool Serialize(ByteBuffer &buffer);

	/*!
	 * \brief Resets this message so that all vectors/collections will be cleared,
	 *		  and default values restored.
	 */
	void Reset();

	/*!
	 * \brief Gets the amount of questions this DNS message currently holds.
	 * 
	 * \returns The amount of questions this DNS message currently holds.
	 */	
	int GetQuestionCount();

public:	
	/*!
	 * \brief Holds all the 'question messages' that are part of this DNS message.
	 */
	MessageQuestionPtrVector Questions;
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_MESSAGE_H
