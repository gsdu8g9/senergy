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

#ifndef SY_DNS_UTILS_H
#define SY_DNS_UTILS_H

#include <string>
#include <senergy/bytebuffer.h>

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
 * \brief Contains various utilities related to the DNS protocol. This are mostly functions that
 *		  are used throughout the application.
 *
 * \author Swen Kooij (Photonios)
 */
class Utils
{
public:
	/*!
	 * \brief Encodes the specified hostname and returns the result. Encoding
	 *		  a hostname means, replacing all dots, with single bytes, that tell
	 * 		  how many characters one needs to count further to get to the next
	 *		  dot.
	 *	
	 *		  www.google.com -> 3www6google3com
	 *		  
	 *		  The dots that are being replaced with numbers are NOT ASCII. They are just
	 *		  single bytes. So, 3, is really 0x03.
	 *
	 * \param hostname The hostname to encode.
	 *
	 * \returns The encoded hostname. If the specified hostname was empty, an empty
	 *			string is returned. 
	 */
	static std::string EncodeHostname(const std::string &hostname);

	/*!
	 * \brief Decodes the specified hostname and returns the result, reverse the result
	 *		  of encoding a hostname. Encoding a hostname means, replacing all dots, 
	 *		  with single bytes, that tell how many characters one needs to count 
	 *	 	  further to get to the next dot.
	 *	
	 *		  www.google.com -> 3www6google3com
	 *		  
	 *		  The dots that are being replaced with numbers are NOT ASCII. They are just
	 *		  single bytes. So, 3, is really 0x03.
	 *
	 *		  So, this function reverse the above example:
	 *
	 *		  3www6google3com -> www.google.com
	 *
	 * \param hostname The hostname to decode.
	 *
	 * \returns The decoded hostname, if the specified hostname was empty, an empty
	 *			string is returned.
	 */
	static std::string DecodeHostname(const std::string &hostname);

	/*!
	 * \brief Converts the specified unsigned short value from host to
	 *		  network byte order.
	 *
	 * \param value The value to convert from host to network byte order.
	 *
	 * \returns The input value, in network byte order.
	 */
	static unsigned short HostToNetworkByteOrder(unsigned short value);
	
	/*!
	 * \brief Converts the specified unsigned short value from network
	 *		  to host byte order.
	 *
	 * \param value The value to convert from network to host byte order.
	 *
	 * \returns The input value, in host byte order.
	 */
	static unsigned short NetworkToHostByteOrder(unsigned short value);

	/*!
	 * \brief Converts the specified unsigned character value from host to
	 *		  network byte order.
	 *
	 * \param value The value to convert from host to network byte order.
	 *
	 * \returns The input value, in network byte order.
	 */
	static unsigned char HostToNetworkByteOrder(unsigned char value);
	
	/*!
	 * \brief Converts the specified unsigned character value from network
	 *		  to host byte order.
	 *
	 * \param value The value to convert from network to host byte order.
	 *
	 * \returns The input value, in host byte order.
	 */
	static unsigned char NetworkToHostByteOrder(unsigned char value);

	/*!
	 * \brief Converts the specified unsigned integer value from host to
	 *		  network byte order.
	 *
	 * \param value The value to convert from host to network byte order.
	 *
	 * \returns The input value, in network byte order.
	 */
	static unsigned int HostToNetworkByteOrder(unsigned int value);
	
	/*!
	 * \brief Converts the specified unsigned integer value from network
	 *		  to host byte order.
	 *
	 * \param value The value to convert from network to host byte order.
	 *
	 * \returns The input value, in host byte order.
	 */
	static unsigned int NetworkToHostByteOrder(unsigned int value);

	/*!
	 * \brief Reads a domain name from the specified buffer, also known as a 'QNAME'.
	 *
	 * 	 	  A domain name in a DNS message is basiclly a string 
	 *		  (but, see Utils::EncodeHostname and Utils::DecodeHostname),
	 *		  however, in a answer (resource record) the domain name
	 *		  could also be a 'pointer'. A pointer in a DNS message means
	 *		  a offset in the buffer where the domain name can be read.
	 *		  This is also known as 'message compression', this is defined
	 *		  in section 4.1.4 of RFC 1035. 
	 *		
	 *		  This function detects whether it is a pointer or just a domain name,
	 *		  and reads both and returns the domain name.
	 *
	 * \see Section 4.1.4 of RFC-1025 (Message compression).
	 *
	 * \param buffer The buffer to read the domain name from.
	 * \param decode An optional parameters that indicates whether the returned string should
	 *				 be decoded using the Utils::DecodeHostname function or not. If set to
	 *				 true the returned hostname will be decoded, if set to false it will
	 *				 not be decoded. We use this parameter when reading a domain name pointer.
	 *
	 * \returns The domain name that was read from the buffer, or an empty
	 *			string if something went wrong.
	 */
	static std::string ReadHostnameFromBuffer(ByteBuffer &buffer, bool decode = true);
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_UTILS_H
