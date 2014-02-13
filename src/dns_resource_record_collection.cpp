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

ResourceRecordCollection::ResourceRecordCollection() : 
	m_mapper	(),
	m_records	()
{	
	__register_mappings();
}

void ResourceRecordCollection::Clear()
{
	m_records.Clear();
}

bool ResourceRecordCollection::Deserialize(MessageHeader &header, ByteBuffer &buffer)
{
	int amount_answers 		= (int) header.Fields.AnswerCount; 
	int amount_nameservers 	= (int) header.Fields.NameServerCount;
	int amount_additional 	= (int) header.Fields.AdditionalCount; 
	int amount_total 		= amount_answers + amount_nameservers + amount_additional;

	for(int i = 0; i < amount_total; ++i)
	{
		if(buffer.GetRemainingSize() < ResourceRecordBase::GetMinimalSize())
			return false;

		ResourceRecordBasePtr base_record = ResourceRecordBase::Create();
		if(!base_record->Deserialize(buffer))
			return false;

		if(buffer.GetRemainingSize() < base_record->GetResourceSize())
			return false;
			
		ResourceRecordInterfacePtr record = m_mapper.ApplyMapping(base_record->GetType(), base_record);
		if(!record)
		{
			printf("HACK\n");
			printf("%hu\n", (unsigned short)base_record->GetType());
	
			// \todo create a class that handles unknown records and holds the resource data
	 		//		 an internal byte buffer, for now just skip the data
			buffer.IncreasePosition(base_record->GetResourceSize());
			//m_records[ResourceRecordType::Unkown].Add(base_record);
			continue;
		}

		if(!record->Deserialize(buffer))
			return false;

		m_records[record->GetType()].Add(record);
	}		

	return true;
}

void ResourceRecordCollection::__register_mappings()
{
	m_mapper.RegisterMapping<IPV4Record>();
}

void ResourceRecordCollection::Dump()
{
	for(size_t i = 0; i < m_records.size(); ++i)
	{
		size_t amount_records = m_records.at(i).second.size();
		for(size_t y = 0; y < amount_records; y++)
		{
			m_records.at(i).second[y]->GetBase()->Dump();
		}
	}
}

} // namespace Dns
} // namespace Senergy
