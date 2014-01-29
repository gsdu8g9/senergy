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

#ifndef SYS_RESOURCE_RECORD_CLASSES_H
#define SYS_RESOURCE_RECORD_CLASSES_H

namespace Senergy
{
namespace Dns
{

/*!
 * \brief An enumuration of all possible resource record classes (RR) as defined in RFC-1035.
 *		  None of them except 'Internet' are really used.
 *
 * \see http://www.iana.org/assignments/dns-parameters/dns-parameters.xhtml
 *
 * \author Swen Kooij (Photonios)
 */
enum class ResourceRecordClass : unsigned short
{
	Reserved = 0,
	Internet = 1,
	Chaos = 2,
	Hesiod = 3,
	None = 254,
	Any = 255
};

} // namespace Dns
} // namespace Senergy

#endif // SYS_RESOURCE_RECORD_CLASSES_H
