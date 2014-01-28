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

#include <senergy/socket.h>

namespace Senergy
{
namespace Networking
{

Socket::Socket(SocketProtocol protocol) :
	m_protocol				(protocol),
	m_connected				(false),
	m_remote_host			(""),
	m_remote_port			(80),
	m_native_socket			(-1),
	m_last_error			(-1),
	m_socket_role			(SocketRole::Client),
	m_timeout_milliseconds	(0)
{
}

Socket::Socket(const Socket &socket)
{
	m_remote_host 			= socket.m_remote_host;
	m_remote_port 			= socket.m_remote_port;
	m_connected 			= socket.m_connected;
	m_last_error 			= socket.m_last_error;
	m_native_socket 		= socket.m_native_socket;
	m_remote_address 		= socket.m_remote_address;
	m_timeout 				= socket.m_timeout;
	m_timeout_milliseconds 	= socket.m_timeout_milliseconds;
	m_socket_role 			= socket.m_socket_role;
	m_protocol				= socket.m_protocol;
}

Socket::Socket(SocketProtocol protocol, int native_socket, struct sockaddr_in remote_address) :
	m_protocol				(protocol),
	m_connected				(true),
	m_remote_host			(""),
	m_remote_port			(80),
	m_native_socket			(native_socket),
	m_last_error			(-1),
	m_socket_role			(SocketRole::Client),
	m_timeout_milliseconds	(0),
	m_remote_address		(remote_address)
{	
}

std::string Socket::GetRemoteHost()
{
	return m_remote_host;
}

bool Socket::IsConnected()
{
	if(m_native_socket < 0)
	{
		m_connected = false;
		return false;
	}
	
	return m_connected;
}

bool Socket::SetTimeout(unsigned int milliseconds)
{		
	m_timeout_milliseconds = milliseconds;	
	return __enfore_timeout();
}

bool Socket::Connect(const std::string &remote_address, unsigned int remote_port)
{
	if(IsConnected())
		return false;
		
	m_remote_host 		= remote_address;
	m_remote_port 		= remote_port;
	
	m_socket_role = SocketRole::Client;
	
	if(!__set_address_struct())
		return false;
		
	if(!__create_native_socket())
		return false;
		
	m_connected = __native_connect();
	return m_connected;
}

bool Socket::Listen(unsigned int port)
{
	if(IsConnected())
		return false;
		
	m_remote_port = port;
	m_socket_role = SocketRole::Server;
		
	if(!__set_address_struct())
		return false;
		
	if(!__create_native_socket())
		return false;
	
	if(!__bind_on_port())
		return false;
		
	if(m_protocol == SocketProtocol::TCP)
	{
		if(!__listen())
			return false;
	}

	m_connected = true;		
	return true;
}

bool Socket::Close(CloseType close_type /* = CloseType::StopAll */)
{
	if(!IsConnected())
		return false;
		
	int shutdown_result = shutdown(m_native_socket, (int)close_type);
	__update_last_error();
	
	return (shutdown_result >= 0);
}

int Socket::Send(const char *data, size_t data_size)
{
	if(data == NULL || data_size <= 0 || !IsConnected())
		return -1;

	int send_result = -1;

	switch(m_protocol)
	{	
		case SocketProtocol::TCP:	
			send_result = send(m_native_socket, (void*)data, data_size, 0);		
		break;

		case SocketProtocol::UDP:
			send_result = sendto(m_native_socket, (void*)data, data_size, 0, (struct sockaddr *)&m_remote_address, sizeof(m_remote_address));
		break;
	}

	__update_last_error();		
	__update_remote_host();

	return send_result;
}

int Socket::Send(const std::string &data, size_t data_size)
{	
	if(data.empty() || data_size <= 0)
		return -1;
		
	return Send(data.c_str(), data_size);
}

int	Socket::Send(const std::string &data)
{
	return Send(data, data.size());
}

int	Socket::Receive(const char *receive_buffer, size_t size)
{
	if(receive_buffer == NULL || size <= 0 || !IsConnected())
		return -1;
		
	fd_set select_data;
	FD_ZERO(&select_data);
	FD_SET(m_native_socket, &select_data);
	
	__enfore_timeout();
	
	struct timeval select_timeout;
	select_timeout.tv_usec = m_timeout_milliseconds;
	
	if(m_timeout_milliseconds >= 1000)
		select_timeout.tv_sec = m_timeout_milliseconds / 1000;
	else if(m_timeout_milliseconds <= 0)
		select_timeout.tv_sec = 0;
	
	if(select(m_native_socket + 1, &select_data, NULL, NULL, &select_timeout) <= 0)
	{
		__update_last_error();
		return -1;
	}
	
	int bytes_received = -1;
	unsigned int address_size = sizeof(m_remote_address);
	
	switch(m_protocol)
	{
		case SocketProtocol::TCP:
			bytes_received = recv(m_native_socket, (void*)receive_buffer, size, 0);
		break;

		case SocketProtocol::UDP:
			bytes_received = recvfrom(m_native_socket, (void*)receive_buffer, size, 0, (struct sockaddr *)&m_remote_address, &address_size);
		break;
	}

	__update_last_error();	
	__update_remote_host();

	return bytes_received;
}

std::string	Socket::Receive(size_t size)
{
	if(!IsConnected() || size <= 0)
		return "";

	char *receive_buffer = (char *)malloc(size);
	if(receive_buffer == NULL)
		return "";
		
	int bytes_received = Receive(receive_buffer, size);
	if(bytes_received <= 0)
	{	
		free(receive_buffer);
		return "";
	}
	
	std::string result = std::string(receive_buffer, bytes_received);
	free(receive_buffer);
	return result;
}

int	Socket::Receive(ByteBuffer &receive_buffer, size_t size)
{
	if(!IsConnected() || size <= 0)
		return -1;
		
	char *temp_receive_buffer = (char *)malloc(size);
	if(temp_receive_buffer == NULL)
		return -1;
		
	int bytes_received = Receive(temp_receive_buffer, size);
	if(bytes_received <= 0)
	{	
		free(temp_receive_buffer);
		return -1;
	}
	
	receive_buffer.Write(temp_receive_buffer, bytes_received);
	free(temp_receive_buffer);
	return bytes_received;
}

SocketPtr Socket::Accept()
{
	if(!IsConnected())
		return SocketPtr();

	struct sockaddr_in remote_address;
	unsigned int address_length = sizeof(remote_address);

	int new_client_socket = accept(m_native_socket, (struct sockaddr*) &remote_address, &address_length);
	__update_last_error();

	if(new_client_socket < 0)
		return SocketPtr();

	SocketPtr client_socket(new Socket(m_protocol, new_client_socket, remote_address));
	client_socket->m_timeout_milliseconds = m_timeout_milliseconds;
	client_socket->m_socket_role = SocketRole::Client;
	client_socket->__update_remote_host();
	
	return client_socket;
}

int Socket::GetErrorCode()
{
	return m_last_error;
}

bool Socket::__create_native_socket()
{
	switch(m_protocol)
	{
		case SocketProtocol::TCP:
			m_native_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		break;

		case SocketProtocol::UDP:
			m_native_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		break;
	}

	__update_last_error();
	
	if(m_native_socket < 0)
		return false;

	return true;
}
	
bool Socket::__set_address_struct()
{
	memset(&m_remote_address, '0', sizeof(m_remote_address));
	m_remote_address.sin_family = AF_INET;
	m_remote_address.sin_port = htons(m_remote_port);

	switch(m_socket_role)
	{
		case SocketRole::Client:
			__enfore_timeout();
		
			struct hostent *host_info;
			host_info = gethostbyname(m_remote_host.c_str());
			__update_last_error();

			if(host_info == NULL)
				return false;
			
			m_remote_address.sin_addr = *(struct in_addr *) host_info->h_addr;
		break;
	
		case SocketRole::Server:
			m_remote_address.sin_addr.s_addr = htonl(INADDR_ANY);
		break;
	}

	__update_remote_host();
	
	return true;	
}

bool Socket::__native_connect()
{
	__enfore_timeout();
	
	int connection_result = connect(m_native_socket, (struct sockaddr *)&m_remote_address, sizeof(m_remote_address));
	__update_last_error();
	__update_remote_host();
	
	return (connection_result >= 0);
}

bool Socket::__bind_on_port()
{
    int bind_result = bind(m_native_socket, (struct sockaddr *)&m_remote_address, sizeof(m_remote_address));
	__update_last_error();	
	
    return (bind_result >= 0);
}

bool Socket::__listen()
{
	int listen_result = listen(m_native_socket, 5);
	__update_last_error();
	
	return (listen_result >= 0);
}

void Socket::__update_last_error()
{
	#ifdef _WIN32
		m_last_error = WSAGetLastError();
	#else
		m_last_error = errno;
	#endif
}

bool Socket::__enfore_timeout()
{
    m_timeout.tv_usec = m_timeout_milliseconds;
    
    if(m_timeout_milliseconds >= 1000)
	    m_timeout.tv_sec = m_timeout_milliseconds / 1000;
	else if(m_timeout_milliseconds <= 0)
		m_timeout.tv_sec = 0;
	
	int timeout_result = setsockopt(m_native_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&m_timeout, sizeof(m_timeout));
	timeout_result = setsockopt(m_native_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&m_timeout, sizeof(m_timeout));

	return timeout_result;
}

void Socket::__update_remote_host()
{
	char *current_remote_host = inet_ntoa(m_remote_address.sin_addr);
	if(current_remote_host == NULL)
		return;

	m_remote_host = std::string(current_remote_host);
}

} // namespace Networking
} // namespace Senergy
