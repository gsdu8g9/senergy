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

#ifndef SY_RECORD_IPV4_ADDRESS_H
#define SY_RECORD_IPV4_ADDRESS_H

#include <memory>
#include <senergy/bytebuffer.h>
#include <senergy/socket.h>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_interface.h>
#include <senergy/dns/resource_record_base.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Represents a DNS 'A' record, which is a resource record that contains an IPV4 address. It is the reply to
 *		  a DNS 'A' question.
 * 
 * \author Swen Kooij (Photonios)
 */
class IPV4Record : public ResourceRecordInterface
{
	// Constructor inheritance..
	using ResourceRecordInterface::ResourceRecordInterface;

public:
	/*!
	 * \brief Initializes a new instance of the IPV4Record class with the specified resource record base.
	 *
	 * \param base The base resource record instance to use for the IPV4 record.
	 */
	IPV4Record(ResourceRecordBasePtr base);

	/*!
	 * \brief Serializes this record into the specified buffer. This does not handle the serialization
	 *		  of the first (base) part of the resource record. Call SerializeBase for that.
	 *
	 * \param buffer The buffer to serialize to.
	 *
	 * \returns A boolean indicating whether the serialization was successful. 
	 */
	bool Serialize(ByteBuffer &buffer);

	/*!
	 * \brief Deserializes the record from the specified buffer. This does not handle deserialization
	 *	 	  of the first (base) part of the resource record. Call DeserializeBase for that.
	 *
	 * \param buffer The buffer to deserialize from.
	 */
	bool Deserialize(ByteBuffer &buffer);

	/*!
	 * \brief Creates a new instance of this class, and returns it as a shared pointer
	 *		  to an instance of the ResourceRecordInterface class. 
	 *		
	 *		  The derived class should create an instance of itself and return
	 *		  the polymorphic form (as it's base).
	 *
	 * \param base The ResourceRecordBase class to pass to the constructor.
	 *
	 * \returns A shared pointer to an instance of the ResourceRecordInterface class,
	 *			which is just the polymorphic form of the derived class.
	 */
	ResourceRecordInterfacePtr Create(ResourceRecordBasePtr base);

	/*!
	 * \brief Gets the type of of this record (derived), wich is a value from
	 *		  the ResourceRecordType enumuration.
	 *
	 * \returns A value from the ResourceRecordType enumuration which denotes
	 *			the type of this record.
	 */
	ResourceRecordType GetType();

	/*!
	 * \brief Sets the IPV4 address that needs to be serialized.
	 *
	 * \param address The IPV4 address to be serialized.
	 */
	void SetAddress(const std::string &address);

	/*!
	 * \brief Gets the IPV4 address that was deserialized.
	 *
	 * \returns The IP address that was deserialized.
	 */
	std::string GetAddress();

private:
	// Contains the address that is going to be serialized, or the address that was deserialized.
	std::string m_address;
};

} // namespace Dns
} // namespace Senergy

#endif // SY_RECORD_IPV4_ADDRESS_H
