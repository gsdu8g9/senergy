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

#include <senergy/dns/record_unknown.h>

namespace Senergy
{
namespace Dns
{

UnknownRecord::UnknownRecord(ResourceRecordBasePtr base) : ResourceRecordInterface(base)
{
}

bool UnknownRecord::Deserialize(ByteBuffer &buffer)
{
	if(buffer.GetRemainingSize() < GetBase()->GetResourceSize())
		return false;

	buffer.IncreasePosition(GetBase()->GetResourceSize());
	return true;
}

bool UnknownRecord::Serialize(ByteBuffer &buffer)
{
	int resource_size = GetBase()->GetResourceSize();
	for(int i = 0; i < resource_size; ++i)
		buffer.WriteNop();

	return true;
}

ResourceRecordInterfacePtr UnknownRecord::Create(ResourceRecordBasePtr base)
{
	return ResourceRecordInterface::CreateCast<UnknownRecord>(base);
}

ResourceRecordType UnknownRecord::GetType()
{
	return ResourceRecordType::Unknown;
}

} // namespace Dns
} // namespace Senergy