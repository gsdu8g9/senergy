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
	return true;
}

bool ResourceRecordCollection::Deserialize(MessageHeader &header, ByteBuffer &buffer)
{
	__clear_collections();

	int answer_count 		= (int) header.Fields.AnswerCount;
	int nameserver_count 	= (int) header.Fields.NameServerCount;
	int additional_count 	= (int) header.Fields.AdditionalCount;

	for (int i = 0; i < answer_count; ++i)
	{
		//ResourceRecordPtr resource_record = ResourceRecord::Create();
		std::shared_ptr<ResourceRecord> resource_record = std::shared_ptr<ResourceRecord>(new ResourceRecord);
		if(!resource_record->Deserialize(buffer))
		{
			printf("HERE(%i)!\n", i);
			return false;
		}
	
		resource_record->Dump();

		bool deserialization_result = true;

		if(resource_record->GetType() == ResourceRecordType::A)
		{
			std::shared_ptr<Records::IPV4Address> converted_rr = std::static_pointer_cast<Records::IPV4Address>(resource_record);
			converted_rr->Deserialize(buffer);		
			buffer.IncreasePosition(resource_record->GetResourceSize());
			printf("%i\n", resource_record->GetResourceSize());
			this->IPV4Answers.Add(converted_rr);
		}
		else
		{
			this->UnknownRecords.Add(resource_record);
			buffer.IncreasePosition(resource_record->GetResourceSize());
			deserialization_result = true;
		}

		if(!deserialization_result)
		{
			printf("HERE?\n");
			return false;
		}
	}

	return true;
}

void ResourceRecordCollection::__clear_collections()
{
	this->IPV4Answers.clear();
	this->UnknownRecords.clear();
}

void ResourceRecordCollection::Dump()
{
	int ipv4_count = (int) this->IPV4Answers.size();
	int unknown_count = (int) this->UnknownRecords.size();
	
	printf("\n");

	for(int i = 0; i < ipv4_count; i++)
		this->IPV4Answers[i]->Dump();	

	printf("\n");

	for(int i = 0; i < unknown_count; i++)
		this->UnknownRecords[i]->Dump();		

	printf("\n");
}

} // namespace Dns
} // namespace Senergy
