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

#include <iostream>
#include <senergy/senergy.h>

int main(int argc, char **argv)
{	
	Senergy::Socket socket(Senergy::Socket::SocketProtocol::UDP);
	socket.SetTimeout(2000);
	
	if(!socket.Listen(53))
	{
		printf("Error: Unable to start listening on port 53\n");
		return 1;
	}

	printf("Info: Listening on port 53\n");

	while(true)
	{
		Senergy::ByteBuffer receive_buffer;
		
		int bytes_received = socket.Receive(receive_buffer, 1024);
		if(bytes_received <= 0)
		{
			if(socket.GetErrorCode() != Senergy::SocketError::Timeout)
				printf("Error: During receiving a socket error occured: %i\n\n", socket.GetErrorCode());
			continue;
		}

		receive_buffer.SetPosition(0);
		printf("Info: received message from: %s\n", socket.GetRemoteHost().c_str());

		Senergy::Dns::Message dns_message;
		if(!dns_message.Deserialize(receive_buffer))
		{
			printf("Error: unable to deserialize message\n\n");
			continue;
		}

		int question_count = dns_message.GetQuestionCount();

		if(question_count <= 0)
		{
			printf("Error: did not receive any questions\n\n");
			continue;
		}

		printf("Info: received %i questions\n", question_count);
		for(int i = 0; i < question_count; i++)
		{
			std::string requested_hostname = dns_message.Questions[i]->GetHostname();
			printf("Info: received question for %s\n", requested_hostname.c_str());
		}

		printf("\n");
	}

	return 0;
}
