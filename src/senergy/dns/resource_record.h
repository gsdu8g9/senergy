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

#ifndef SYS_DNS_RESOURCE_RECORD_H
#define SYS_DNS_RESOURCE_RECORD_H

#include <string>
#include <memory>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_classes.h>
#include <senergy/vectorx.h>
#include <senergy/dns/utils.h>
#include <senergy/bytebuffer.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Defines a DNS Resource Record, as defined in RFC 1035, section 4.1.3. A DNS Recource record
 *		  can appear both in the answer, authority and additional section of a DNS packet/message.
 *		  
 *		  All fields in a resource record are the same, regardless of whether it is an answer, authority
 *		  or additional record. The only difference is the format of the last
 *		  field, the resource data field. The format of this field depends on the resource record type.
 *
 * 		  This class does NOT implement the resource data field, and does not serialize/deserilize it.
 *		  Instead, new classes should be created per resource record type, which do implement
 *		  the resource data field, and inherit from this class.
 *
 * \author Swen Kooij (Photonios)
 */
class ResourceRecord
{
protected:
	// A simple typedef for a shared pointer to a ResourceRecord instance.
	// Warning: this is re-declared at the bottom of this file.
	typedef std::shared_ptr<ResourceRecord> ResourceRecordPtr;

public:
	/*!
	 * \brief Initializes a new instance of the ResourceRecord class.
	 */
	ResourceRecord();
	
	/*!
	 * \brief Creates a new instance of the ResourceRecord class as a shared
	 *		  pointer.
	 *
	 * \returns A shared pointer to the newly initiated instance of the ResourceRecord class.
	 */
	static ResourceRecordPtr Create();

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
	virtual void Dump();

protected:
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

/*!
 * \brief A shared pointer to an instance of the ResourceRecord class.
 */
typedef std::shared_ptr<ResourceRecord> ResourceRecordPtr;

/*!
 * \brief A vector of shared pointers to ResourceRecord class instances
 */
typedef VectorX<ResourceRecordPtr> ResourceRecordPtrVector;

} // namespace Dns
} // namespace Senergy

#endif // SYS_DNS_RESOURCE_RECORD_H
