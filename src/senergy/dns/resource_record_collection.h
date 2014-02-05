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

#ifndef SY_DNS_RESOURCE_RECORD_COLLECTION_H
#define SY_DNS_RESOURCE_RECORD_COLLECTION_H

#include <string>
#include <senergy/dns/record_ipv4address.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Simple container for all types of resource records we support. This is to prevent creating
 *		  hundreds of separate containers in the Message class.
 *
 * \author Swen Kooij (Photonios)
 */
class ResourceRecordCollection
{
public:
	/*!
  	 * \brief Initializes a new instance of the ResourceRecordCollection class.
  	 */
	ResourceRecordCollection();

	/*!
	 * \brief Serializes all records in this collection into the specified buffer.
	 *
	 * \param buffer The buffer to write the serialized data to.
	 *
	 * \returns A boolean indicating whether this operation was a success.
	 */
	bool Serialize(ByteBuffer &buffer);

	/*!
	 * \brief Deserializes the content of the specified buffer into this collection.
	 *
	 * \param buffer The buffer to read from.
	 * 
	 *
	 * \returns A boolean indicating whether this operation was a success.
	 */
	bool Deserialize(ByteBuffer &buffer);

public:
	/*!
	 * \brief All 'A' records in this collection. See the IPV4Address class for more information..
	 */
	IPV4AddressPtrVector ARecords;

private:
	// Serializes all 'A' records, in the ARecords vector to the specified buffer.
	void __serialize_a_records(ByteBuffer &buffer);

	// Deserializes all 'A' records from the specified buffer into the 'ARecords' vector.
	void __deserialize_a_records(ByteBuffer &buffer);
}; 

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_RESOURCE_RECORD_COLLECTION_H

