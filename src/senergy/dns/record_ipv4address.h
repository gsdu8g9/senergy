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
class IPV4Address : ResourceRecord
{
private:
	// Simple typedef for a shared pointer to this class, warning
  	// this is re-declared at the bottom of this file (for public access).
	typedef std::shared_ptr<IPV4Address> IPV4AddressPtr;

public:
	/*!
	 * \brief Initializes a new instance of the IPV4Address class.
 	 */
	IPV4Address();

	/*!
	 * \brief Initializes a new instance of the IPV4Address class as a shared pointer.
     */
	static IPV4AddressPtr Create();

	/*!
	 * \brief Deserializes a resource record from the specified buffer into
	 *		  this instance.
	 *
	 * 		  The specified buffer must have at least 4 bytes left to read.
	 *		  However, the size of a resource record is variable, because
	 *		  of the name field.
	 *
	 *		  When we can not read the entire resource record from the specified
	 *		  buffer, false is returned.
	 *
	 * \note This will advance the buffer's position with the size of the record.
	 *
	 * \param buffer The buffer to read the resource record from.
	 *
	 * \returns A boolean indicating whether deserialization was succesful. True
	 *			is returned when deseriliazation was succesful and false when
	 *			it was not.
	 */
	virtual bool Deserialize(ByteBuffer &buffer);

	/*!
	 * \brief Serializes this instance into the specified buffer.
	 *
	 * 		  The size of a resource record is variable, because of
	 *		  the name field.
	 *
	 *	 	  If we cannot, for whatever reason, serialize this record,
	 *		  false is returned.
	 *
	 * \note This will advance the buffer's position with the size of the record.
	 *
	 * \param buffer The buffer to write the serialized record to.
	 * 
	 * \returns A boolean indicating whether serialization was successful. True is
	 *			returned when serialization was successful, and false is returned
	 *			when it was not.
	 */
	virtual bool Serialize(ByteBuffer &buffer);

private:
	// Simple typedef to make the code more readble and clear..
	typedef ResourceRecord BaseClass;

private:
	// Contains the address that is going to be serialized, or the address that was deserialized.
	std::string m_address;
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
