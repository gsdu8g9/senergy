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

#include <senergy/dns/requester.h>

namespace Senergy
{
namespace Dns
{

Requester::Requester(const std::string &dns_server) :
	m_dns_server	(dns_server)
{
	
}

StringVector Requester::Lookup(ResourceRecordType record_type, const std::string &hostname)
{
	if(hostname.empty())
		return StringVector();
	
	Socket socket(Socket::SocketProtocol::UDP);
	socket.SetTimeout(2000);
	if(!socket.Connect(m_dns_server, 53))
	{
		printf("Error: Unable to set up UDP connection with specified DNS server\n");
		return StringVector();
	}
	
	ByteBuffer send_buffer;

	Senergy::Dns::Message send_dns_message;
	send_dns_message.Questions.Add(MessageQuestion::Create(hostname, record_type));

	if(!send_dns_message.Serialize(send_buffer))
	{	
		printf("Error: Unable to serialize message\n");
		return StringVector();
	}

	send_buffer.SetPosition(0);
	socket.Send(send_buffer);

	ByteBuffer receive_buffer;
	int bytes_received = socket.Receive(receive_buffer, 1024);
	if(bytes_received <= 0)
	{
		if(socket.GetErrorCode() != Senergy::SocketError::Timeout)
			printf("Error: During receiving a socket error occured: %i\n\n", socket.GetErrorCode());
		return StringVector();
	}

	receive_buffer.SetPosition(0);

	Senergy::Dns::Message received_dns_message;
	if(!received_dns_message.Deserialize(receive_buffer))
	{
		printf("Error: unable to deserialize message\n\n");
		return StringVector();
	}

	received_dns_message.Dump();
	return StringVector();
}

} // namespace Dns
} // namespace Senergy
