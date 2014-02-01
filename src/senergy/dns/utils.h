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
	 * \brief Determines whether the specified hostname/domain name is a pointer
	 *		  to an earlier occurence of the same domain name.
	 *
	 * 		  If it's a pointer, the first two bytes will be 0x01.
	 *
	 * \see Section 4.1.4 of RFC-1025 (Message compression).
 	 *
	 * \param hostname The hostname/domain name to check if it's a pointer.
	 *
	 * \returns A boolean indicating whether the specified hostname/domain name
	 *			is a pointer. True is returned when it is a pointer and false
	 *			is returned when it is not.	
	 */
	static bool IsDomainPointer(const std::string &hostname);
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_UTILS_H
