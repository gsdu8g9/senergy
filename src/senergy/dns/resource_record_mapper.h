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

#ifndef SY_RESOURCE_RECORD_MAPPER_H
#define SY_RESOURCE_RECORD_MAPPER_H

#include <memory>
#include <string>
#include <type_traits>
#include <map>
#include <senergy/fastmap.h>
#include <senergy/dns/resource_record_types.h>
#include <senergy/dns/resource_record_classes.h>
#include <senergy/dns/resource_record_base.h>
#include <senergy/dns/resource_record_interface.h>

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Helps in mapping values from the ResourceRecordType enumuration to classes that derive from the ResourceRecordInterface
 *		  class. This is to prevent huge switches or blocks of if statements. This is a little bit complex, but it gives us way
 *		  more flexibility and makes the code a bit easier to maintain.
 *
 * \note This implements the abstract factory pattern.
 * \see http://en.wikipedia.org/wiki/Abstract_factory_pattern
 *
 * \author Swen Kooij (Photonios)
 */
class ResourceRecordMapper : protected std::map<ResourceRecordType, ResourceRecordInterfacePtr>
{
public:
	/*!
	 * \brief Initialiazes a new empty instance of the ResourceRecordMapper class.
	 */
	ResourceRecordMapper() :
		m_dummy_resource_record()
	{
	}

	/*!
	 * \brief Maps the specified type, which MUST inherit from ResourceRecordInterface. This will
	 *		  create a dummy instance of T, using a dummy instance of the ResourceRecordBase class,
	 *		  extract the type (->GetType), which is a member of the ResourceRecordType enumuration,
	 *		  and then add this mapping to the underlying map.
	 *
	 *		  To clarify:
	 *		  this[resource_record_type] = dummy_instance;
	 *
 	 * \typeparam T A type that inherits from ResourceRecordInterface.
	 */
	template<class T>
	void RegisterMapping()
	{
		static_assert(std::is_base_of<ResourceRecordInterface, T>::value, "T does not derive from ResourceRecordInterface");

		ResourceRecordInterfacePtr iam_t = std::dynamic_pointer_cast<ResourceRecordInterface>(
			std::shared_ptr<T>(
				new T(m_dummy_resource_record)
			)
		);

		ResourceRecordType type = iam_t->GetType();
		(*this)[type] = iam_t;
	}

	/*!
	 * \brief Applies the mapping between the specified value from the ResourceRecordType enumuration
	 *		  and the correct derived class form ResourceRecordInterface.
	 *
	 *		  If a correct mapping is found, a new instance of the found class is created as a shared
	 *		  pointer, and the specified ResourceRecordBase class instance is based in the constructor.
	 *
	 *		  When no mapping could be found, an invalid pointer (null ptr) is returned.
	 *
	 * \param type The value from the ResourceRecordType enumuration to find a mapping for.
	 * \param base The instance of the ResourceRecordBase class to pass to the constructor of
	 *			   the found type.
	 *
	 * \returns A shared pointer to a new instance of the found the type, but the newly created
	 *			instance is returned as a shared pointer to a ResourceRecordInterface class instance,
	 *			however, polymorphism will come into play and the actual type that is returned
	 *			is the type that is found (a type that derives from the ResourceRecordInterface)
	 *			class.
	 */
	ResourceRecordInterfacePtr ApplyMapping(ResourceRecordType type, ResourceRecordBase &base)
	{
		auto it = this->find(type);
		if(it != this->end())
			return it->second->Create(base);

		return ResourceRecordInterfacePtr();
	}
	
	/*!
	 * \brief Applies reverse mapping, mapping the specified type to the right value from
	 *		  the ResourceRecordType enumuration.
	 *
	 * \typeparam T The type to find the mapped value from the ResourceRecordType enumuration. This must
	 *				inherit from the ResourceRecordInterface class.
	 *
	 * \returns A value from the ResourceRecordType enumuration that is mapped to the specified type.
	 */
	template<class T>
	ResourceRecordType ApplyReverseMapping()
	{
		static_assert(std::is_base_of<ResourceRecordInterface, T>::value, "T does not derive from ResourceRecordInterface");

		ResourceRecordInterfacePtr iam_t = std::dynamic_pointer_cast<ResourceRecordInterface>(
			std::shared_ptr<T>(
				new T(m_dummy_resource_record)
			)
		);

		return iam_t->GetType();
	}

private:
	// Dummy object that we pass to the constructor of classes that derive from the ResourceRecordInterface
	// class...
	ResourceRecordBase m_dummy_resource_record;
	
}; 

} // namespace Dns
} // namespace Senergy

#endif // SY_RESOURCE_RECORD_MAPPER_H
