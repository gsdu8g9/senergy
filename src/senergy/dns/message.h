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

#ifndef SY_DNS_MESSAGE_H
#define SY_DNS_MESSAGE_H

namespace Senergy
{
namespace Dns
{

/*!
 * \brief Represents a DNS packet as described in section 4 of RFC-1035. A DNS packet is the standard
 *		  message format that is transmitted and received by DNS clients and hosts.
 * 
 * \author Swen Kooij (Photonios)
 */
class Message
{
public:
	/*!
	 * \brief Initializes a new instance of the Message class, with default values, without questions,
	 *		  answers, authorities and additionals.
 	 */
	Message();
};

} // namespace Dns
} // namespace Senergy

#endif // SY_DNS_MESSAGE_H
