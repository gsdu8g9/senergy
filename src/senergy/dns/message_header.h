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

#ifndef SY_DNS_MESSAGE_HEADER_H
#define SY_DNS_MESSAGE_HEADER_H

#include <senergy/bytebuffer.h>
#include <cstdio>

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
 * \brief Defines the fields within a DNS packet header, as described in section 4.1 of RFC-1035.
 *	 	  This data structure is used as the "Fields" member/property of the MessageHeader class,
 *		  and serves as the container of the actual data.
 *
 * \note This size of this structure is 12 bytes. 
 * 
 * \see http://msdn.microsoft.com/en-us/library/windows/desktop/ms682059(v=vs.85).aspx
 * \see http://www.ietf.org/rfc/rfc1035.txt
 *
 * \author Swen Kooij (Photonios)
 */
struct MessageHeaderFields
{
	/*!
	 * \brief A 16 bit identifier assigned by the program that
	 *        generates any kind of query.  This identifier is copied
	 *        the corresponding reply and can be used by the requester
	 *        to match up replies to outstanding queries.
	 */
	unsigned short Id;

	/*!
 	 * \brief Recursion Desired - this bit may be set in a query and
     * 		  is copied into the response.  If RD is set, it directs
     *		  the name server to pursue the query recursively.
     *		  Recursive query support is optional.
 	 */
	unsigned char RecursionDesired :1;

	/*!
 	 * \brief TrunCation - specifies that this message was truncated
     *        due to length greater than that permitted on the
     *        transmission channel.
	 */
	unsigned char Truncation :1;     

	/*!
 	 * \brief Authoritative Answer - this bit is valid in responses,
     *		  and specifies that the responding name server is an
     *		  authority for the domain name in question section.
 	 *
	 * \note The contents of the answer section may have multiple owner
	 *		 names because of aliases. The AA bit corresponds to the name
	 *		 which atches the query name, or the first owner name in the
	 *		 answer section.
	 */
	unsigned char Authoritative :1;     

	/*!
 	 * \brief A four bit field that specifies kind of query in this
     *        message.  This value is set by the originator of a query
     *        and copied into the response.  The values are:
     *
     *        0               a standard query (QUERY)
     *
     *        1               an inverse query (IQUERY)
     *
     *        2               a server status request (STATUS)
     *
     *        3-15            reserved for future use
	 */
	unsigned char Opcode :4; 

	/*!
 	 * \brief A one bit field that specifies whether this message is a
     *        query (0), or a response (1).
 	 */
	unsigned char IsResponse :1; 

	/*!
 	 * \brief Response code - this 4 bit field is set as part of
     *        responses.  The values have the following
     *        interpretation:
	 *
     *        0               No error condition	
	 *
     *        1               Format error - The name server was
     *                        unable to interpret the query.
	 *
     *        2               Server failure - The name server was
     *                        unable to process this query due to a
     *                        problem with the name server.
 	 *
     *        3               Name Error - Meaningful only for
     *                        responses from an authoritative name
     *                        server, this code signifies that the
     *                        domain name referenced in the query does
     *                        not exist.
	 *
     *        4               Not Implemented - The name server does
     *                        not support the requested kind of query.
	 *
     *        5               Refused - The name server refuses to
     *                        perform the specified operation for
     *                        policy reasons.  For example, a name
     *                        server may not wish to provide the
     *                        information to the particular requester,
     *                        or a name server may not wish to perform
     *                        a particular operation (e.g., zone transfer) 
	 *						  for particular data.
	 *
     *        6-15            Reserved for future use. 
  	 */
	unsigned char ResponseCode :4; 

	/*!
 	 *\ brief A value that specifies whether checking is supported by the DNS resolver.
	 *
	 *		  0				  Checking is enabled on the DNS resolver.
	 *		 
	 *		  1				  Checking is enabled on the DNS resolver.
	 */
	unsigned char CheckingDisabled :1;    

	/*!
 	 * \brief A value that specifies whether the DNS data following the DNS packet header is 
	 *		  authenticated by the DNS server.
	 *
	 *		  0				  The DNS data is not authenticated.
	 *		 
	 *		  1				  The DNS data is authenticated.
	 */
	unsigned char AuthenticatedData :1;    

	/*!
	 * \brief Reserved for future use.  Must be zero in all queries
     *        and responses.
	 * 
	 * \note Specification (RFC 1035) says that this field must be zero
	 *		 at all times, however, bytes get reversed, so 1 becomes zero.
	 */
	unsigned char Reserved :1; 

	/*!
 	 * \brief Recursion Available - this be is set or cleared in a
     *        response, and denotes whether recursive query support is
     *        available in the name server.
	 */
	unsigned char RecursionAvailable :1; 

	/*!
 	 * \brief  An unsigned 16 bit integer specifying the number of
     *         entries in the question section.    
	 */
	unsigned short QuestionCount;

	/*!
	 * \brief The number of resource records (RRs) contained in the 
	 *	 	  answer section of the DNS message.
	 */
	unsigned short AnswerCount; 

	/*!
 	 * \brief The number of DNS name server RRs contained in the authority 
	 *		  section of the DNS message. This value is the number of DNS 
	 *	 	  name servers the message has traversed in its search for resolution.
	 */
	unsigned short NameServerCount; 

	/*!
	 * \brief Reserved. Do not use.
	 */
	unsigned short AdditionalCount;
};

/*!
 * \brief Defines the header of a DNS packet, as described in section 4.1 of RFC-1035. All DNS messages
 *		  start with this header.
 *
 * \note The actual data will be within a MessageHeaderFields data structure.
 *
 * \see http://msdn.microsoft.com/en-us/library/windows/desktop/ms682059(v=vs.85).aspx
 * \see http://www.ietf.org/rfc/rfc1035.txt
 *
 * \author Swen Kooij (Photonios)
 */
class MessageHeader
{
public:
	/*!
 	 * \brief Initializes a new instance of the MessageHeader class, with the default
	 *	 	  values.
	 */
	MessageHeader();
	
	/*!
 	 * \brief Deserializes a DNS packet header from the specified buffer into this
	 *		  instance.
	 *
	 * \note The DNS message header is 12 bytes, the specified buffer must at least
	 *		 have 12 bytes left to read.
	 *
	 * \note Using this will advance the position of the specified ByteBuffer with
	 *		 12 bytes.
	 *
	 * \param buffer A reference to an instance of the ByteBuffer class,
	 *		  	 	 the buffer to read from.
	 *
	 * \returns A boolean indicating whether deserialization was succesfull. True is
	 *			returned when it was a success and false is returned when it failed.
	 */
	bool Deserialize(ByteBuffer &buffer);

	/*!
 	 * \brief Gets the size of a DNS packet header. This is almost constant
	 *		  as long as the MessageHeaderFields structure doesn't change.
	 *
	 * \returns The size of a MessageHeaderFields structure, the size
	 *			of a DNS packet header.
	 */
	int GetSize();
	
	/*!
 	 * \brief Serializes this instance into the specified buffer, ready
	 *		  for transmission.
	 *
	 * \note Using this will advance the position of the specified ByteBuffer with
	 *		 12 bytes.
	 *
	 * \param buffer A reference to the ByteBuffer to write the serialized
	 *		 		 DNS packet header into.
	 *
	 * \returns A boolean indicating whether serialization was sucessful.
	 *			True is returned when seralization suceseeded and false
	 *			is returned when it failed.
	 */
	bool Serialize(ByteBuffer &buffer);

	/*!
 	 * \brief Dumps all fields and their values to the standard output in the following
	 *		  format:
	 *	 
	 *		  [field name]: [field_value]\n
	 */
	void Dump();

public:
	/*!
 	 * \brief The fields that are part of a DNS packet header. See MessageHeaderFields
	 *		  for a complete list. This contains the actual data
	 *		  that is transmitted and received.
	 */
	MessageHeaderFields Fields;

private:
	// Converts all fields from host to network byte order
	void __host_to_network_byte_order();

	// Converts all fields from network to host byte order
	void __network_to_host_byte_order();

	// Prepares all fields for serialization by setting the correct values
	void __prepare_serialization();
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_MESSAGE_HEADER_H
