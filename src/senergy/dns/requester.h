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

#ifndef SYS_DNS_REQUESTER_H
#define SYS_DNS_REQUESTER_H

#include <senergy/bytebuffer.h>
#include <senergy/socket.h>
#include <senergy/vectorx.h>
#include <senergy/types.h>
#include <senergy/dns/message.h>
#include <senergy/dns/resource_record_types.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Allows querying remote DNS servers, wraps sending and receiving DNS messages.
 *
 * \author Swen Kooij (Photonios)
 */
class Requester
{
public:
	/*!
	 * \brief Initializes a new instance of the Requester class with the specified
	 * 		  DNS server address.
	 *
	 * \param dns_server The IP address of a DNS server that this class will communicate
	 *				     with when requests are executed.
	 *
	 */
	Requester(const std::string &dns_server);

	/*!
	 * \brief Performs a lookup for the specified domain name, and requests
	 *		  the specified record from the remote DNS server.
	 *
	 * \param record_type A value from the ResourceRecordType enumuration, which
	 *					  indicates what kind of records should be returned.
 	 * \param hostname 	  The domain name to look up the IP address(es) for.
	 *
	 * \returns The message that was received from the remote server.
	 */
	Dns::Message Lookup(ResourceRecordType record_type, const std::string &hostname);

private:
	// Holds the ip of the remote dns server as specified in the constructor
	std::string m_dns_server;
};

} // namespace Dns
} // namespace Senergy

#endif // SYS_DNS_REQUESTER_H
