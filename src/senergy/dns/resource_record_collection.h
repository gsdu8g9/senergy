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

#ifndef SY_RESOURCE_RECORD_COLLECTION_H
#define SY_RESOURCE_RECORD_COLLECTION_H

#include <vector>
#include <string>
#include <senergy/bytebuffer.h>
#include <senergy/fastmap.h>
#include <senergy/vectorx.h>
#include <senergy/dns/message_header.h>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_classes.h>
#include <senergy/dns/resource_record_base.h>
#include <senergy/dns/resource_record_interface.h>
#include <senergy/dns/resource_record_mapper.h>
#include <senergy/dns/record_ipv4_address.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief A collection of resource record. We have many types of resource record. Senergy DNS
 *		  has a flexbile desing to simplify the implementation of additional records. This container
 *		  is part of that design. It has the ability to contain all kinds of resource records. It also
 *		  helps in serialization and deserialization.
 *
 * \author Swen Kooij (Photonios)
 */
class ResourceRecordCollection
{
private:
	// A simple typedef for a mapping between a resource record type and a vector of resource records.
	typedef FastMap<ResourceRecordType, VectorX<ResourceRecordInterfacePtr>> ResourceRecordMapCollection;

public:
	/*!
	 * \brief Initializes a new instance of the ResourceRecordCollection class.
	 */
	ResourceRecordCollection();

	/*!
	 * \brief Clears the collection of any existing records.
	 */
	void Clear();

	/*!
	 * \brief Deserializes all resource records from the specified buffer, according
	 *		  to the information in the specified DNS message header.
	 *
	 * \note This clears this collection of all existing records.
	 *
	 * \param header The DNS message header to read the information on the amount
	 *				 of resource records from.
	 * \param buffer The buffer to read/deserialize the records from.
 	 *
     * \returns A boolean indicating whether the deserialization was succesful.
	 */
	bool Deserialize(MessageHeader &header, ByteBuffer &buffer);

	/*!
	 * \brief Dumps the contents of this collection to the console.
	 */
	void Dump();

private:
	// Registers all mappings between values from the ResourceRecordType enumuration and the implementation classes...
	void __register_mappings();

private:
	// Helps mapping values from the ResourceRecordType enumuration to the right class for serialization
 	// and deserialization
	ResourceRecordMapper 		m_mapper;

	// Holds all the records
 	ResourceRecordMapCollection m_records;
};

} // namespace Dns
} // namespace Senergy

#endif // SY_RESOURCE_RECORD_COLLECTION_H
