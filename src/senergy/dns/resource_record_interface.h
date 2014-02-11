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
private:
	// Simple typedef for a shared pointer to an instance of the ResoureceRecordInterface
	// class. Warning, this is redefined at the bottom of this file for public access.
	typedef std::shared_ptr<ResourceRecordInterface> ResourceRecordInterfacePtr; 

public:
	
};

/*!
 * \brief Typedef for a shared pointer to an instance of the ResourceRecordInterface class.
 */
typedef std::shared_ptr<ResourceRecordInterface> ResourceRecordInterfacePtr; 

} // namespace Dns
} // namespace Senergy

#endif // SY_RESOURCE_RECORD_INTERFACE_H
