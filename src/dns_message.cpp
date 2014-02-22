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

Message::Message() : 
	m_header	()
{
}

bool Message::Deserialize(ByteBuffer &buffer)
{
	if(!m_header.Deserialize(buffer))
		return false;

	Reset();

	for(int i = 0; i < m_header.Fields.QuestionCount; ++i)
	{
		MessageQuestionPtr new_message = MessageQuestionPtr(new MessageQuestion());
		if(!new_message->Deserialize(buffer))
			return false;	

		this->Questions.push_back(new_message);
	}

	if(!this->ResourceRecords.Deserialize(m_header, buffer))
		return false;

	this->ResourceRecords.Dump();
	return true;
}

bool Message::Serialize(ByteBuffer &buffer)
{
	m_header.Fields.QuestionCount = (unsigned short) std::min(GetQuestionCount(), 256);

	if(!m_header.Serialize(buffer))
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
	m_header.Dump();
}

} // namespace Dns
} // namespace Senergy
