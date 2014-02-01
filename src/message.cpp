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

#include <senergy/dns/message.h>

namespace Senergy
{
namespace Dns
{

Message::Message()
{
}

bool Message::Deserialize(ByteBuffer &buffer)
{
	MessageHeader header;

	if(!header.Deserialize(buffer))
		return false;

	Reset();

	header.Dump();

	for(int i = 0; i < header.Fields.QuestionCount; ++i)
	{
		MessageQuestionPtr new_message = MessageQuestionPtr(new MessageQuestion());
		if(!new_message->Deserialize(buffer))
			return false;

		this->Questions.push_back(new_message);
	}

	// \todo implement deserialization of rest of packet

	return true;
}

bool Message::Serialize(ByteBuffer &buffer)
{
	MessageHeader header;
	header.Fields.QuestionCount = (unsigned short) std::min(GetQuestionCount(), 256);

	if(!header.Serialize(buffer))
		return false;
	
	int question_count = GetQuestionCount();

	for(int i = 0; i < question_count; ++i)
	{
		MessageQuestionPtr current_question = this->Questions[i];
		if(!current_question)
			continue;

		if(!current_question->Serialize(buffer))
			return false;
	}

	// \todo implement serialization of rest of packet
	return true;
}

void Message::Reset()
{
	this->Questions.clear();
}

int Message::GetQuestionCount()
{
	return (int) this->Questions.size();
}

void Message::Dump()
{
	// \todo implement
}

} // namespace Dns
} // namespace Senergy
