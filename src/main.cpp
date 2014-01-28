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

typedef struct
{
unsigned short id;       // identification number
unsigned char rd :1;     // recursion desired
unsigned char tc :1;     // truncated message
unsigned char aa :1;     // authoritive answer
unsigned char opcode :4; // purpose of message
unsigned char qr :1;     // query/response flag
unsigned char rcode :4;  // response code
unsigned char cd :1;     // checking disabled
unsigned char ad :1;     // authenticated data
unsigned char z :1;      // its z! reserved
unsigned char ra :1;     // recursion available
unsigned short q_count;  // number of question entries
unsigned short ans_count; // number of answer entries
unsigned short auth_count; // number of authority entries
unsigned short add_count; // number of resource entries
} DNS_HEADER;

unsigned char* ReadName(unsigned char* reader,unsigned char* buffer,int* count)
{
    unsigned char *name;
    unsigned int p=0,jumped=0,offset;
    int i , j;
 
    *count = 1;
    name = (unsigned char*)malloc(256);
 
    name[0]='\0';
 
    //read the names in 3www6google3com format
    while(*reader!=0)
    {
        if(*reader>=192)
        {
            offset = (*reader)*256 + *(reader+1) - 49152; //49152 = 11000000 00000000 ;)
            reader = buffer + offset - 1;
            jumped = 1; //we have jumped to another location so counting wont go up!
        }
        else
        {
            name[p++]=*reader;
        }
 
        reader=reader+1;
 
        if(jumped==0) *count = *count + 1; //if we havent jumped to another location then we can count up
    }
 
    name[p]='\0'; //string complete
    if(jumped==1) 
    {
        *count = *count + 1; //number of steps we actually moved forward in the packet
    }
 
    //now convert 3www6google3com0 to www.google.com
    for(i=0;i<(int)strlen((const char*)name);i++)
    {
        p=name[i];
        for(j=0;j<(int)p;j++)
        {
            name[i]=name[i+1];
            i=i+1;
        }
        name[i]='.';
    }
     
    name[i-1]='\0'; //remove the last dot
     
    return name;
}

int main(int argc, char **argv)
{	
	Senergy::Socket socket(Senergy::Socket::SocketProtocol::UDP);
	
	socket.SetTimeout(9999);
	socket.Listen(53);

	while(true)
	{
		Senergy::ByteBuffer receive_buffer;
		int bytes_received = socket.Receive(receive_buffer, 1024);
		if(bytes_received < 0)
		{
			if(socket.GetErrorCode() != 9)
				printf("Error: socket error %i\n", socket.GetErrorCode());
			continue;
		}

		printf("Received from: %s\n", socket.GetRemoteHost().c_str());
		receive_buffer.SetPosition(0);

		Senergy::Dns::Message dns_message;
		if(!dns_message.Deserialize(receive_buffer))
		{
			printf("Deserialization failed!\n");
			continue;
		}


		for(int i = 0; i < dns_message.Header.Fields.QuestionCount; ++i)
		{
			int remaining_bytes = receive_buffer.Size() - receive_buffer.GetPosition();
			char *remaining = (char*)malloc(remaining_bytes);

			printf("Questions: %hu\n", dns_message.Header.Fields.QuestionCount);
			
			if(!receive_buffer.Read(remaining, remaining_bytes))
			{
				printf("Error: failed to read name\n");
				free(remaining);
				break;
			}

			int name_len = 0;
			unsigned char *name = ReadName((unsigned char *)remaining, (unsigned char*)remaining, &name_len);
			printf("Question for: %s\n\n", name);
		}

		//printf("%s\n", receive_buffer.ReadAll().c_str());	
	}
	return 0;
}
