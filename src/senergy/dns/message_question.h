
#ifndef SY_DNS_MESSAGE_QUESTION_H
#define SY_DNS_MESSAGE_QUESTION_H

#include <senergy/bytebuffer.h>
#include <cstdio>
#include <cctype>

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
 * \brief Describes the fields of a question message as defined in section 4.1.2 of RFC-1035. 
 *	 	  This data structure is used as the "Fields" member/property of the MessageQuestion class,
 *		  and serves as the container of the actual data.
 *
 * \note The size of this structure is variable, because of the host name, but it is at least 2 bytes.
 *
 * \author Swen Kooij (Photonios)
 */
struct MessageQuestionFields
{
	/*!
  	 * \brief  A domain name represented as a sequence of labels, where
     *         each label consists of a length octet followed by that
     *         number of octets.  The domain name terminates with the
     *         zero length octet for the null label of the root.  Note
     *         that this field may be an odd number of octets; no
     *         padding is used.
	 */
	unsigned char *Hostname;

	/*!
 	 * \brief A two octet code which specifies the type of the query.
     *        The values for this field include all codes valid for a
     *        TYPE field, together with some more general codes which
     *        can match more than one type of RR.
	 */
	unsigned short Type;
	
	/*!
	 * \brief A two octet code that specifies the class of the query.
     *        For example, the QCLASS field is IN for the Internet.
	 */
	unsigned short Class;
};

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

public:
	/*!
 	 * \brief The fields that are part of a DNS question message. See MessageQuestionFields
	 *		  for a complete list. This contains the actual data
	 *		  that is transmitted and received.
	 */
	MessageQuestionFields Fields;

public:
	// Will encode the hostname currently set from 'www.google.com' to '3www6.google.com3'
	std::string __encode_hostname(const std::string &hostname);

	// Will decode the hostname currently set from '3www6.google.com3' to 'www.google.com'
	std::string __decode_hostname(const std::string &hostname);

	// Updates the 'Hostname' field within the 'Fields' member with m_hostname.
	void __update_host_to_fields(const std::string &hostname);
	
	// Updates m_hostname with the 'Hostname' field from the 'Fields' member.
	void __update_host_from_fields();

private:
	// Holds the host name that is currently set.
	std::string 	m_hostname;
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_MESSAGE_QUESTION_H
