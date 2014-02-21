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

#ifndef SY_RESOURCE_RECORD_INTERFACE_H
#define SY_RESOURCE_RECORD_INTERFACE_H

#include <memory>
#include <type_traits>
#include <senergy/dns/resource_record_base.h>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_classes.h>
#include <senergy/bytebuffer.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Defines an interface using pure virtuals for classes that wish to implement a specic
 *		  resource record type.
 *
 * \author Swen Kooij (Photonios).
 */
class ResourceRecordInterface
{
protected:
	// Simple typedef for a shared pointer to an instance of the ResoureceRecordInterface
	// class. Warning, this is redefined at the bottom of this file for public access.
	typedef std::shared_ptr<ResourceRecordInterface> ResourceRecordInterfacePtr; 

public:
	/*!
	 * \brief Initializes a new instance of of the ResourceRecordInterfacePtr class
	 *		  with a reference to an instance of the ResourceRecordBase class.
	 *
	 * \param base A resource record can have multiple types, a class that implents
	 *			   this interface handles the serialization and deserialization of
	 *			   the type-specific part.
	 *				
	 *			   The first part of a resource record is always the same. This is why
	 *			   we need an instance of the base class here.
	 */
	ResourceRecordInterface(ResourceRecordBasePtr base);
					
	/*!
	 * \brief Serializes this record into the specified buffer. This does not handle the serialization
	 *		  of the first (base) part of the resource record. Call SerializeBase for that.
	 *
	 * \param buffer The buffer to serialize to.
	 *
	 * \returns A boolean indicating whether the serialization was successful. 
	 */
	virtual bool Serialize(ByteBuffer &buffer) = 0;

	/*!
	 * \brief Deserializes the record from the specified buffer. This does not handle deserialization
	 *	 	  of the first (base) part of the resource record. Call DeserializeBase for that.
	 *
	 * \param buffer The buffer to deserialize from.
	 */
	virtual bool Deserialize(ByteBuffer &buffer) = 0;

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
	virtual ResourceRecordInterfacePtr Create(ResourceRecordBasePtr base) = 0;

	/*!
	 * \brief Gets the type of of this record (derived), wich is a value from
	 *		  the ResourceRecordType enumuration.
	 *
	 * \returns A value from the ResourceRecordType enumuration which denotes
	 *			the type of this record.
	 */
	virtual ResourceRecordType GetType() = 0;
	
	/*!
	 * \brief Gets the class of this record. This will almost always be 
	 *		  the same and does not have to be implemented by the derived class.
	 *
	 * \returns A value from the ResourceRecordClass enumuration which denotes
	 *			the class of this record.
	 */
	virtual ResourceRecordClass GetClass();

	/*!
	 * \brief Returns the underlying base resource record for this record.
	 *
	 * \returns An instance of the ResourceRecordBase class, which represents
	 *			the first part in this resource record.
	 */
	ResourceRecordBasePtr GetBase() const;

	/*!
	 * \brief Creates a new instance of the specified type with the specified resource record base instance,
	 *        and casts it to a shared ppinter to a ResourceRecordInterface class (polymorhpism).
	 *		  The specified type must inherit from ResourceRecordInterface.
	 *
	 * \typeparam T The type to create and cast to ResourceRecordInterface shared pointer.
	 * 
	 * \returns An instance of the specified type but, casted to an instance of the ResourceRecordInterface class (shared pointer).
	 */
	template<class T>
	static ResourceRecordInterfacePtr CreateCast(ResourceRecordBasePtr base)
	{
		static_assert(std::is_base_of<ResourceRecordInterface, T>::value, "T does not derive from ResourceRecordInterface");

		return std::dynamic_pointer_cast<ResourceRecordInterface>(std::shared_ptr<T>(new T(base)));
	}

protected:
	/*!
	 * \brief Sets the resource size in the base record.
	 *
	 * \param resource_size The size of the resource 
	 */
	void SetResourceSize(unsigned short resource_size);

	/*!
	 * \brief Sets the resource size in the base record.
	 *
	 * \param resource_size The size of the resource 
	 */
	bool SetResourceSize(unsigned int resource_size);

protected:
	/*!
	 * \brief More logical way to allow access to the base class.
	 */
	typedef ResourceRecordBase Base;

protected:
	// Holds the underlying base class.
	ResourceRecordBasePtr m_base;
};

/*!
 * \brief Typedef for a shared pointer to an instance of the ResourceRecordInterface class.
 */
typedef std::shared_ptr<ResourceRecordInterface> ResourceRecordInterfacePtr; 

} // namespace Dns
} // namespace Senergy

#endif // SY_RESOURCE_RECORD_INTERFACE_H
