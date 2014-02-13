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

#include <senergy/dns/resource_record_interface.h>

namespace Senergy
{
namespace Dns
{

ResourceRecordInterface::ResourceRecordInterface(ResourceRecordBasePtr base) :
	m_base	(base)
{
}

ResourceRecordBasePtr ResourceRecordInterface::GetBase() const
{
	return m_base;
}

ResourceRecordClass ResourceRecordInterface::GetClass()
{
	return ResourceRecordClass::Internet;
}

} // namespace Dns
} // namespace Senergy
