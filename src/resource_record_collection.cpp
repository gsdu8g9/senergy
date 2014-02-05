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

#include <senergy/dns/resource_record_collection.h>

namespace Senergy
{
namespace Dns
{

ResourceRecordCollection::ResourceRecordCollection()
{
}

bool ResourceRecordCollection::Serialize(MessageHeader &header, ByteBuffer &buffer)
{
	
}

bool ResourceRecordCollection::Deserialize(MessageHeader &header, ByteBuffer &buffer)
{
	__clear_collections();

	int resource_records_count = (int) header.Fields.AnswerCount;

	for (int i = 0; i < resource_records_count; ++i)
	{

	}
}

void ResourceRecordCollection::__clear_collections()
{
	this->ARecords.clear();
}

} // namespace Dns
} // namespace Senergy
