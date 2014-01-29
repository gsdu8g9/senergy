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

#ifndef SY_DNS_MESSAGE_QUESTION_H
#define SY_DNS_MESSAGE_QUESTION_H

#include <senergy/bytebuffer.h>
#include <senergy/convert.h>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_classes.h>
#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <memory>

#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <arpa/inet.h>
#endif

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Represents a DNS question, as defined in section 4.1.2 of RFC-1035. A DNS question is usually transmitted
 *		  by a DNS client, asking to lookup the IP address of a host name.
 *
 * \author Swen Kooij (Photonios)
 */
class MessageQuestion
{
public:
	/*!
	 * \brief Initializes a new instance of the MessageQuestion class with default values.
	 */
	MessageQuestion();

	/*!
	 * \brief Gets the host name from the fields.
	 *
	 * \returns The host name that is being requested (resolved).
	 */
	std::string GetHostname();

	/*!
	 * \brief Sets the host name that needs to be requested (resolved).
	 *	
	 * \param hostname The host name that needs to be requested
	 *				   (resolved).
	 */
	void SetHostname(const std::string &hostname);

	/*!
	 * \brief Gets the current size of this message, this is variable, depending
	 *		  on the length of the host name.
	 *
	 * \returns The current size of this message.
	 */
	int GetSize();

	/*!
	 * \brief Deserializes a single DNS question message from the specified buffer into this instance.
	 *
	 * \note The question message is of variable size, due to the hostname. We must at least be
	 *		 able to read 3 bytes from the specified buffer, otherwise the operation will fail.
	 *
	 * \note This will advance the position of the buffer with the size of the message.
	 *
	 * \param buffer The buffer to read from.
	 *
	 * \returns A boolean indicating whether deserilization was successful. True is returned
	 *			when it was a success and false is returned when it failed.
	 */
	bool Deserialize(ByteBuffer &buffer);
	
	/*!
	 * \brief Serializes this instance into the specified buffer as a DNS question message.
	 *
	 * \note This will advance the position of the buffer with the size of the message.
	 *
	 * \note Serilization will fail when no hostname is set.
	 *
	 * \param buffer The buffer to write the serialized message to.
	 * 
	 * \returns A boolean indicating whether serilization was successful. True is returned
	 *			when it was a success and false is returned when it failed.
	 */
	bool Serialize(ByteBuffer &buffer);

	/*!
	 * \brief Dumps all fields to the standard output, with
	 *		  their values. In the following format:
	 *
	 * 		  [field name]: [field_value]\n
	 */
	void Dump();

	/*!
	 * \brief Gets the type of question this is, what actually is meant, is the type
	 *		  or resource record that is expected when asking this question.
	 *
	 * \returns A value from the ResourceRecordType enumuration.
	 */
	ResourceRecordType GetType();

	/*!
	 * \brief Sets the type of question this is, what actually is meant is the type
	 *		  of resource record that is expected when asking this question.
	 *
	 * \param type A value from the ResourceRecordType enumuration, the type to set.
	 */
	void SetType(ResourceRecordType type);

	/*!
	 * \brief Gets the class of this question, the class denotes the format of the question.
	 *		  We only support IN (Internet) classes (1).
	 *
	 * \returns A value from the ResourceRecordClass enumuration.
	 */
	ResourceRecordClass GetClass();

	/*!
	 * \brief Set the class of this question, the class denotes the format of the question.
	 *		  We only support IN (Internet) classes (1).
	 *
	 * \param clas A value from the ResourceRecordClass enumuration.
	 */
	void SetClass(ResourceRecordClass clas);

private:
	// Will encode the hostname currently set from 'www.google.com' to '3www6.google.com3'
	std::string __encode_hostname(const std::string &hostname);

	// Will decode the hostname currently set from '3www6.google.com3' to 'www.google.com'
	std::string __decode_hostname(const std::string &hostname);

	// Converts the specified value from host to network byte order
	unsigned short __host_to_network_byte_order(unsigned short value);

	// Converts the specified value from network to host byte order
	unsigned short __network_to_host_byte_order(unsigned short value);

private:
	// Holds the host name that is currently set.
	std::string 	m_hostname;

	// Holds the type for this question
	unsigned short 	m_type;
	
	// Holds the question class
	unsigned short 	m_class;
};

/*!
 * \brief Simple typedef for a shared pointer to a MessageQuestion.
 */
typedef std::shared_ptr<MessageQuestion> MessageQuestionPtr;

/*!
 * \brief Simple typedef for a vector of MessageQuestion smart pointers.
 */
typedef std::vector<MessageQuestionPtr> MessageQuestionPtrVector;

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_MESSAGE_QUESTION_H
