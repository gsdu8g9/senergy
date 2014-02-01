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

#include <senergy/dns/message_header.h>

namespace Senergy
{
namespace Dns
{

MessageHeader::MessageHeader()
{
	this->Fields.QuestionCount = 0;
	this->Fields.AnswerCount = 0;
	this->Fields.NameServerCount = 0;
	this->Fields.AdditionalCount = 0;
}

int MessageHeader::GetSize()
{
	return sizeof(MessageHeaderFields);
}

bool MessageHeader::Deserialize(ByteBuffer &buffer)
{
	int header_size = GetSize();

	if(buffer.GetRemainingSize() < header_size)
		return false;

	if(!buffer.Read((char*)&this->Fields, header_size))
		return false;

	__network_to_host_byte_order();
	return true;
}

bool MessageHeader::Serialize(ByteBuffer &buffer)
{	
	int header_size = GetSize();
	buffer.Reserve(header_size);

	__prepare_serialization();
	__host_to_network_byte_order();

	buffer.Write((char *)&this->Fields, header_size);

	__host_to_network_byte_order();
	return true;
}

void MessageHeader::__host_to_network_byte_order()
{
	this->Fields.Id 				= htons(this->Fields.Id);
	this->Fields.QuestionCount 		= htons(this->Fields.QuestionCount);
	this->Fields.AnswerCount 		= htons(this->Fields.AnswerCount);
	this->Fields.NameServerCount 	= htons(this->Fields.NameServerCount);
	this->Fields.AdditionalCount 	= htons(this->Fields.AdditionalCount);
}

void MessageHeader::__network_to_host_byte_order()
{
	this->Fields.Id 				= ntohs(this->Fields.Id);
	this->Fields.QuestionCount 		= ntohs(this->Fields.QuestionCount);
	this->Fields.AnswerCount 		= ntohs(this->Fields.AnswerCount);
	this->Fields.NameServerCount 	= ntohs(this->Fields.NameServerCount);
	this->Fields.AdditionalCount 	= ntohs(this->Fields.AdditionalCount);
}

void MessageHeader::__prepare_serialization()
{
	this->Fields.Id 				= 1337; // \todo fix this, make random id factory here
	this->Fields.IsResponse 		= 0;
	this->Fields.Opcode 			= 0;
	this->Fields.ResponseCode 		= 0;
	this->Fields.Truncation 		= 0;
	this->Fields.RecursionAvailable = 0;
	this->Fields.Reserved 			= 0;
	this->Fields.AuthenticatedData 	= 0;
	this->Fields.CheckingDisabled 	= 0;
	this->Fields.Authoritative 		= 1;
	this->Fields.RecursionDesired 	= 1;
}

void MessageHeader::Dump()
{
	printf("Id: %hu\n", this->Fields.Id);
	printf("RecursionDesired: %hu\n", this->Fields.RecursionDesired);
	printf("Truncation: %u\n", this->Fields.Truncation);
	printf("Authoritative: %u\n", this->Fields.Authoritative);
	printf("Opcode: %u\n", this->Fields.Opcode);
	printf("IsResponse: %u\n", this->Fields.IsResponse);
	printf("ResponseCode: %u\n", this->Fields.ResponseCode);
	printf("CheckingDisabled: %u\n", this->Fields.CheckingDisabled);
	printf("AuthenticatedData: %u\n", this->Fields.AuthenticatedData);
	printf("Reserved: %u\n", this->Fields.Reserved);
	printf("RecursionAvailable: %u\n",this->Fields.RecursionAvailable);
	printf("QuestionCount: %hu\n", this->Fields.QuestionCount);
	printf("AnswerCount: %hu\n", this->Fields.AnswerCount);
	printf("NameServerCount: %hu\n", this->Fields.NameServerCount);
	printf("AdditionalCount: %hu\n", this->Fields.AdditionalCount);
}

} // namespace Dns
} // namespace Senergy
