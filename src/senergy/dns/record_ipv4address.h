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

#ifndef SY_DNS_RECORDS_IPV4ADDRESS_H
#define SY_DNS_RECORDS_IPV4ADDRESS_H

#include <string>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_classes.h>
#include <senergy/dns/message_header.h>
#include <senergy/dns/resource_record.h>
#include <senergy/socket.h>
#include <senergy/vectorx.h>

namespace Senergy
{
namespace Dns
{
namespace Records
{

/*!
 * \brief An address record, contains the answer to a lookup. Contains a IPV4 IP address, the response to
 *		  a question, to lookup a hostname/domain name. This is part of a resource record, and the actual
 *		  data is stored in the last field of a recource record (RDATE). See the ResourceClass and section
 *		  3.4.1 of RFC 1035 for more information.
 *
 * \note This is coupled with the ResourceRecordType::A type.
 *
 * \author Swen Kooij (Photonios)
 */
class IPV4Address
{
private:
	// Simple typedef for a shared pointer to this class, warning
  	// this is re-declared at the bottom of this file (for public access).
	typedef std::shared_ptr<IPV4Address> IPV4AddressPtr;

public:
	/*!
	 * \brief Initializes a new instance of the IPV4Address class with the specified
	 *		  resource record.
	 *
	 * \param resource_record The resource record to use as a base for this instance.
 	 */
	IPV4Address(ResourceRecordPtr resource_record);

	/*!
	 * \brief Initializes a new instance of the IPV4Address class as a shared pointer.
	 *
	 * \param resource_record The resource record to use as a base for this instance.
     */
	static IPV4AddressPtr Create(ResourceRecordPtr resource_record);
	
	/*!
	 * \brief Deserializes the RDATA part of this resource record, and does NOT
	 *		  deserialize the first part of the resource record.
	 *
 	 * \param resource_record 	The resource record to use as the base.
	 * \param buffer 			The buffer to read from.	
 	 *
	 * \returns A boolean indicating whether this operation was a success. If the operation
	 *		    failed, false is returned. When the operation was a success, true is
	 *			returned.
	 */
	bool Deserialize(ByteBuffer &buffer);

	/*!
	 * \brief Serializes the RDATA part of this resource record, and does NOT
	 *		  serialize the first part of the resource record.
	 *
 	 * \param resource_record 	The resource record to use as the base.
	 * \param buffer 			The buffer to write to.
 	 *
	 * \returns A boolean indicating whether this operation was a success. If the operation
	 *		    failed, false is returned. When the operation was a success, true is
	 *			returned.
	 */
	bool Serialize(ByteBuffer &buffer);

	/*!
	 * \brief Dumps all fields to the standard output, with
	 *		  their values. In the following format:
	 *
	 * 		  [field name]: [field_value]\n
	 */
	void Dump();

private:
	// Contains the address that is going to be serialized, or the address that was deserialized.
	std::string m_address;
	
	// The resource record that was specified during construction.
	ResourceRecordPtr m_resource_record;
};

/*!
 * \brief A shared pointer to a IPV4Address instance.
 */
typedef std::shared_ptr<IPV4Address> IPV4AddressPtr;

/*!
 * \brief A vector of shared pointers to IPV4Address instances
 */
typedef VectorX<IPV4AddressPtr> IPV4AddressPtrVector;

} // namespace Records
} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_RECORDS_IPV4ADDRESS_H
