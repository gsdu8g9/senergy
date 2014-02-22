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

#ifndef SY_RESOURCE_RECORD_H
#define SY_RESOURCE_RECORD_H

#include <string>
#include <memory>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_classes.h>
#include <senergy/dns/utils.h>
#include <senergy/bytebuffer.h>
#include <senergy/convert.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Represents the first part of a resource record. A resource record is defined in section  4.1.3 of RFC 1035.
 *		  However, a resource record can be of different types. The last part of a resource record is different depending
 *		  of what type of resource record we're dealing with. This class handles the serializing and deserializing
 *		  of the first part of a resource record, the part that is always the same. Classes that implement the 
 *		  ResourceRecordInterface class take care of the serialization and deserialization of the rest of the type-specific
 *		  part.
 * 
 * \author Swen Kooij (Photonios)
 */
class ResourceRecordBase
{
	// This is so interface can write information to the base, it's like protected inheritance..
	friend class ResourceRecordInterface;

private:
	// Simple typedef for a shared pointer for the ResourceRecordBase class.
 	// Warning: this is redefined at the bottom of this file for public usage.
	typedef std::shared_ptr<ResourceRecordBase> ResourceRecordBasePtr;

public:
	/*!
	 * \brief Initializes a new instance of the ResourceRecordBase class.
 	 */
	ResourceRecordBase();

	/*!
	 * \brief Creates a new instance of the ResourceRecordBase class as a shared
	 *		  pointer.
	 *
	 * \returns A shared pointer to the newly initiated instance of the ResourceRecordBase class.
	 */
	static ResourceRecordBasePtr Create();

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
	bool Deserialize(ByteBuffer &buffer);

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
 	bool Serialize(ByteBuffer &buffer);

	/*!
	 * \brief Gets the hostname that was configued in this answer.
	 *
	 * \returns The hostname configured in this answer.
	 */
	std::string GetHostname();

	/*!
	 * \brief Sets the hostname for this answer.
	 *
	 * \param hostname The hostname to set.
	 */
	void SetHostname(const std::string hostname);

	/*!
	 * \brief Gets the resource record type, the type of resource this record
	 *		  contains.
	 *
	 * \returns A value from the ResourceRecordType enumuration, which indicates
	 *			what kind of resource this record contains.
	 */
	ResourceRecordType GetType();
	
	/*!
	 * \brief Gets the resource record type of this record, as a string.
	 *
	 * \returns The type of this resource record as a string, which is basiclly
	 *			the name of the configued ResourceRecordType enumuration value.
	 */
	std::string GetTypeString();

	/*!
	 * \brief Sets the resource record type, the type of resource this record contains.
	 *
	 * \param type A value from the ResourceRecordType enumuration, which indicates
	 *			   what kind of resource this record contains.
	 */
	void SetType(ResourceRecordType type);

	/*!
	 * \brief Gets the resource record class that was configured for this
	 *		  record.
	 *
	 * \returns A value from the ResourceRecordClass enumuration, which indicates
	 *			what class the resource is of.
	 */
	ResourceRecordClass GetClass();

	/*!
	 * \brief Sets the resource record class, the class of resource this
	 *		  record contains.	
	 *
	 * \param clas A value from the ResourceRecordClass enumuration, which
	 *			   indicates what class the resource is of.
	 */
	void SetClass(ResourceRecordClass clas);

	/*!
	 * \brief Determines whether the resource in this record should be cached.
	 *
	 * \returns True when this record needs to be cached, and false when
	 *			it should not be cached.
	 */
	bool NeedsCaching();

	/*!
	 * \brief Gets the maximum amount of seconds the resource in this record
	 *		  should be cached.
	 *
	 * \returns The maximum amount of seconds the resource in this record
	 *			should be cached. If zero is returned, the resource should
	 *			be cached at all.
	 */
	int GetMaxCachingTime();

	/*!
	 * \brief Gets the size of the resource this record contains.
	 *
	 * \returns The size of the resource in this record (amount of bytes).
	 */
	int GetResourceSize();

	/*!
	 * \brief Dumps all fields to the standard output, with
	 *		  their values. In the following format:
	 *
	 * 		  [field name]: [field_value]\n
	 */
	void Dump();

	/*!
	 * \brief Gets the minimal size of a resource record, the size that is required to contain all fiels
	 *		  except the resource data.	 
 	 *
	 * \returns The amount of bytes that the minimal size of a resource record is.
	 */
	static int GetMinimalSize();

private:
	// The domain name that was returned, this is either a DNS label (3www6google3com) or a pointer
	// If the first two bits are 1's then, it's a pointer
	std::string 			m_hostname;

	// The resource record type
	ResourceRecordType 		m_type;

	// The resource record class, almost always the same
	ResourceRecordClass		m_class;

	// The time in seconds that the record may be cached
	unsigned int			m_ttl;

	// The length of the remaining data (actual resource data)
	unsigned short			m_rd_length;
};

// Simple typedef for a shared pointer for the ResourceRecordBase class.
typedef std::shared_ptr<ResourceRecordBase> ResourceRecordBasePtr;

} // namespace Dns
} // namespace Senergy

#endif // SY_RESOURCE_RECORD_H
