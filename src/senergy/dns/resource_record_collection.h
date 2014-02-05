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
	 * \param header The header to write to how many resource records
	 *				 we serialized.
	 *
	 * \returns A boolean indicating whether this operation was a success.
	 */
	bool Serialize(MessageHeader &header, ByteBuffer &buffer);

	/*!
	 * \brief Deserializes the content of the specified buffer into this collection.
	 *
	 * \param buffer The buffer to read from.
	 * \param header The header to use as the information source during deserialization.
	 *				 The header contains information on how many resource records
	 *				 have been returned.
	 *
	 * \returns A boolean indicating whether this operation was a success.
	 */
	bool Deserialize(MessageHeader &header, ByteBuffer &buffer);

public:
	/*!
	 * \brief All 'A' records in this collection. See the IPV4Address class for more information..
	 */
	Records::IPV4AddressPtrVector ARecords;

private:
	// Clears all internal collections
	void __clear_collections();
}; 

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_RESOURCE_RECORD_COLLECTION_H

