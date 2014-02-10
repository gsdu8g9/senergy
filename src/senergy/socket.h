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

#ifndef SY_SOCKET
#define SY_SOCKET

#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include <senergy/bytebuffer.h>
#include <senergy/convert.h>

#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <windows.h>
	#include <stdio.h>
#else
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <errno.h>
#endif

namespace Senergy
{

/*!
 * \brief Defines possible errors that can occur within the Socket class.
 */
namespace SocketError
{
	/*!
 	 * \brief Thrown when a socket operation (receing/binding/sending/connecting) times out.
	 */
	const static int Timeout = 9;
} // namespace SocketError

/*!
 * \brief Provides an object-oriented interface for Berkely (BSD) sockets.
 *		  Can act both as a server as well as a client. The main purpose of this class
 *		  class is to provide a more C++ like interface for TCP sockets. 
 *
 *	 	  Another important purpose of this class is thread-safety. Due to the 'global' nature
 *		  nature in C, Berkely sockets are not thread safe. Using mutexes this class is and allows
 *		  the socket to be used in a multi-threaded environment.
 *
 * \note  This class does not use exceptions. Error handeling is done the same way as in the
 *		  Berkely Sockets interface. Call GetErrorCode(..) for the latest BSD error code.
 *
 * \author Swen Kooij / Photonios
 */
class Socket
{
public:
	/*!
 	 * \brief Defines possible ways/means of closing/disconnecting an active socket
	 *		  connection.
	 */
	enum class CloseType : int
	{
		/*!
 		 * \brief Stop receiving incoming data, but send all remaining data.
		 */
		StopReceiving 	= 0,

		/*!
 		 * \brief Stop sending data, but receive all remaining data.
		 */		
		StopSending		= 1,

		/*! 
		 * \brief Stop sending and receiving data immeditially./
		 */		
		StopAll			= 2
	};
	
	/*!
 	 * \brief Defines the possible socket roles we can have. An instance of the Socket
	 *		  socket class can be of two different roles.
	 */
	enum class SocketRole : int
	{
		/*!
	     * \brief The instance is behaving as a client socket, which is connected to
	     *		  a server.
		 */
		Client	= 0,
		
		/*! 
		 * \brief The instance is behaving as a server and is binded on a specific
		 *		  port, and listens for incoming connections.
		 */		
		Server  = 1
	};

	/*!
	 * \brief Defines the possible socket protocols that this class supports.
	 */
	enum class SocketProtocol : int
	{
		TCP,
		UDP
	};

	/*!
 	 * \brief A shared pointer typedef for the Socket class.
	 *
	 * \note This is defined outside the class definition as well
	 *		 to make it usuable for library users.
	 */
	typedef std::shared_ptr<Socket> SocketPtr;
		
public:
	/*! 
	 * \brief Initializes a new instance of the TSocket class that is not connected
	 *		  to a remote host, and starts as the 'client' socket type.
 	 *
	 *		  One should use the Connect(..) or the Listen(..) functions to either
	 *		  connect to a remote host, or to start listening for incoming connections.
	 *
	 * \param protocol A value from the SocketProtocol enumuration, which indicates
	 *				   what kind of protocol this socket is going to use.
	 */
	Socket(SocketProtocol protocol);

	/*! 
	 * \brief Initializes a new instance of the Socket class based on the specified
	 * 		  reference to another instance of the Socket class. This constructor
	 *		  is defined as the 'copy constructor' and performs a hard copy
	 *		  of the specified Socket instance.
	 *
	 * \note  This copy constructor is defined to allow the Socket class to be used
	 *		  in STL collections like map, vector and list.
	 *
	 * \param socket A reference to an instance of the Socket class that needs
	 *				     to be hard-copied into a new instance.
	 */
	Socket(const Socket &socket);

	/*!
	 * \brief Initializes a new instance of the Socket class using the specified
	 *		  native socket and remote address.
	 *
	 *		  The intention of this constructor is to easily allow the user of the library
	 *		  to wrap existing/created Berkely sockets. 
	 *
	 *		  This constructor is also used when an incoming remote connection is accepted.
	 *
	 * \param protocol 		 A value from the SocketProtocol enumuration, which indicates
	 *				   		 what kind of protocol this socket is going to use.
	 * \param native_socket  A valid/connected descriptor for a Berkeley Socket (BSD), that
	 *					     the new instance needs to wrap.
	 * \param remote_address A sockaddr_int structure, which defines the remote host
	 *					 	 that this socket is connected to.
	 */
	Socket(SocketProtocol protocol, int native_socket, struct sockaddr_in remote_address);

	/*!
	 * \brief Gets the textual representation of the remote host that this socket
	 *		  is currently connected to. This can either be an IP address or
	 *		  a host name.
	 *
	 *		  The remote host gets updated when connections are made. When data is received
	 *		  over UDP, the remote host gets updated with the host that we last
	 *		  received data from.
	 *
	 * \returns The textual representation of the remote host, can return an empty
	 *		    string when there is no active connection, or when the remote
	 *	  	 	host is unknown.
	 */
	std::string GetRemoteHost();
	
	/*!
 	 * \brief Determines whether this instance has an active connection with
	 *		  a remote rost and returns the result.
	 *
	 * \note  This cannot be used to accurately determine the status of the
	 *		  connection. When the remote host closes the connection,
	 *		  the status is not updated. The status is only updated when
	 *		  a connection is initiated or destroyed/closed by this instance.
	 *
	 * \returns A boolean indicating whether there's an active connection with
	 *			the remote host. True is returned when there is an active connection
	 *		    and false is returned when there is no active connection.
	 */
	bool			IsConnected();

	/*!
  	 * \brief Sets the timeout time that is used for socket operations, such as 
	 *		  sending, receiving, and connecting. A timeout specifies the maximum
	 *		  time to wait for an operation to complete.
	 *
	 * \param milliseconds The maximum time to wait for an operation to complete.
 	 *					   The timeout has to be specified in milliseconds.
	 *
	 * \returns A boolean indiciating whether setting the timeout succeseeded. True
	 *			is returned when the operation sucesseeded and false when it failed.
	 *		    Failure can be caused by not having an active connection.
	 */ 
	bool			SetTimeout(unsigned int milliseconds);

	/*!
	 * \brief Attempts to setup a TCP connection with the specified remote host over
	 *		  the specified port.
	 *
	 * \note This sets the type of this instance to 'Cient', but only if the operation
	 *		 was succesful.
	 *
	 * \param remote_ip 	A string containing the remote host name or IP address to
	 *				    	connect to.
	 * \param remote_port	The TCP port to connect over to the specified remote host.
	 *
	 * \returns A boolean indicating whether setting up a connection with the specified
	 *			remote host succeseeded. True is returned when setting up the connection
	 *			succseeded and false when it failed. Reason for failure can be an invalid
	 *			or non-existing remote host, or no remote server listening on the specified
	 *			port.
	 */
	bool 			Connect(const std::string &remote_ip, unsigned int remote_port);

	/*!
	 * \brief Starts listening for incoming connections on the specified port. Binds itself
	 *		  to the specified port. Incoming connections can be accepted using the 'Accept(..)' 
	 *		  method.
	 *
	 * \note This sets the type of this instance to 'Server', but only if the operation
	 *	 	 was successful.
	 *
	 * \param port The TCP port number to start listening on for incoming connections.
	 *
	 * \returns A boolean indiciating whether the operation succeseeded. True is returned
	 *			when the operationg succeseeded and false when it failed. Reason for failure
	 *			can be, that another TCP server is already binded/listening on the specified
	 *			port.
	 */
	bool			Listen(unsigned int port);

	/*!
 	 * \brief Closes the current connection with the remote host. The method of closing
	 *		  the connection can be specified.
	 *
	 * \param close_type Optional: Specifies the method of closing the connection with
	 *					 the remote host.
	 *
	 * \returns A boolean indiciating whether the operation succeseeded and false when the
	 *			operation failed. The operation can fail when there is no active connection
	 *			with a remote host.
	 */
	bool			Close(CloseType close_type = CloseType::StopAll);
	
	/*!
 	 * \brief Sends the specified data, with the specified size to the remote host.
 	 *
 	 * \note This operation will fail when there is no active connection with the remote host.
	 *
	 * \param data 		The data to send to the remote host. If NULL is specified, the operation
	 *			   		will immediately fail.
	 * \param data_size The size of the data that was specified, the size of the data to send
	 *					to the remote host. If zero or less is specified, the operation will
	 *					fail immediately.
	 *	
	 * \returns	The amount of bytes that were succesfuly transmitted to the remote host.
	 *			If the operation failed, zero will be returned.
	 */
	int				Send(void *data, size_t data_size);

	/*!
 	 * \brief Sends the specified data, with the specified size to the remote host.
 	 *
 	 * \note This operation will fail when there is no active connection with the remote host.
	 *
	 * \param data 		The data to send to the remote host. If NULL is specified, the operation
	 *			   		will immediately fail.
	 * \param data_size The size of the data that was specified, the size of the data to send
	 *					to the remote host. If zero or less is specified, the operation will
	 *					fail immediately.
	 *	
	 * \returns	The amount of bytes that were succesfuly transmitted to the remote host.
	 *			If the operation failed, zero will be returned.
	 */
	int				Send(char *data, size_t data_size);

	/*!
 	 * \brief Sends the specified data, with the specified size to the remote host.
 	 *
 	 * \note This operation will fail when there is no active connection with the remote host.
	 *
	 * \param data 		The textual data to transmit to the remote host.
	 * \param data_size The size of the data that was specified, the size of the data to send
	 *					to the remote host. If zero or less is specified, the operation will
	 *					fail immediately.
	 *	
	 * \returns	The amount of bytes that were succesfuly transmitted to the remote host.
	 *			If the operation failed, zero will be returned.
	 */
	int 			Send(const std::string &data, size_t data_size);

	/*!
 	 * \brief Sends the specified data, the size (length) of the specified string is the size
	 *		  of the data that will be transmitted.
 	 *
 	 * \note This operation will fail when there is no active connection with the remote host.
	 *
	 * \param data 		The textual data to transmit to the remote host.
	 *	
	 * \returns	The amount of bytes that were succesfuly transmitted to the remote host.
	 *			If the operation failed, zero will be returned.
	 */
	int				Send(const std::string &data);

	/*!
	 * \brief Sends the contents of the specified buffer. The entire buffer will be transmitted,
	 *		  regardless of the current position of the buffer.
	 *
 	 * \note This operation will fail when there is no active connection with the remote host.
	 *
	 * \param send_buffer The buffer to read the data to transmit from.
 	 *
	 * \returns	The amount of bytes that were succesfuly transmitted to the remote host.
	 *			If the operation failed, zero will be returned.
	 */
	int				Send(ByteBuffer &send_buffer);
	
	/*!
 	 * \brief Attempts to receive the specified amount of data into the specified buffer.
	 *
	 * \note This operation will fail when there is no active connection with the remote host.
	 * 
	 * \param receive_buffer The buffer to store the received data into. Writing starts
	 *						 at the start of the buffer. If NULL is specified, the operation
	 *						 will fail immediately.
	 * \param size			 The amount of bytes to receive. Make sure that the specified
	 *						 receive buffer is this size, or greater.
 	 *
	 * \returns	The amount of bytes that were actually received and stored into the specified
  	 *			receive buffer. This can be less then the specified size, but never greater.
	 *		    If a number below zero is returned, the operation failed. The reason of
	 *			failure can be retrieved using the GetErrorCode() method.
	 */
	int				Receive(const char *receive_buffer, size_t size);

	/*!
 	 * \brief Attempts to receive the specified amount of data and return it as a string.
	 *
	 * \note This operation will fail when there is no active connection with the remote host.
	 * 
	 * \param size The amount of bytes to receive and return as a string.
	 *
	 * \returns A string containing the received data. The length (size) of the returned
	 *			string can be equal or less then the specified size, but never greater.
	 *			If the operatin failed, an empty string is returned.
	 */
	std::string		Receive(size_t size);

	/*!
	 * \brief Attempts to receive the specified amount of data and store it into
	 *		  the specified byte buffer.
	 *
	 * \note This operation will fail when there is no active connection with the remote host.
	 *
	 * \param receive_buffer A reference to an instance of the ByteBuffer class, which is dynamiclly
	 *						 sized binary data container, to store/write to the received data.
	 * \param size			 The amount of bytes to receive.
	 * 
	 * \returns	The amount of bytes that were received. This number can be equal
	 *			or less then the specified desired amount of bytes. If a number below
	 *			zero (negative) is returned, the operation failed. The reason of failure can be
	 *			retrieved using the GetErrorCode() method.
	 */			 
	int				Receive(ByteBuffer &receive_buffer, size_t size);

	/*!
 	 * \brief Attempts to accept an incoming remote connection. This can be used to accept incoming
	 *		  remote connections when this instance is listening for incoming connections.
	 *
 	 * \note This does not work when this instance is not listening for incoming connections.
	 *
	 * \returns A shared pointer to an instance of the Socket class, which represents the accepted
	 *			remote connection. When the operation failed, an invalid shared pointer is returned.
	 *
	 */
	SocketPtr		Accept();
	
	/*!
	 * \brief Gets the last error code that was set by a socket operation. The error code that
	 *		  is returned are normal Berkely sockets error codes. Performing another socket
	 *		  operation overwrites the last error code that was set.
	 *
	 * \returns The last error code that was set during a socket operation. If a negative number
	 *		    or zero is returned, the last operation did not cause an error and was sucessful.
	 */
	int 			GetErrorCode();

	/*!
	 * \brief Converts a 32-bit unsigned integer, which contains a IPV4 address to it's
	 *		  textual representation, where each 8 bit chunk is separated by a dot.
	 *
	 * \param binary The binary value of the IPV4 address to convert to it's textual
	 *				 representation.
	 *
	 * \returns The textual representation of the specified binary IPV4 address.
	 *			An empty string is returned when something went wrong.
	 */
	static std::string IPV4AddressFromBinary(unsigned int binary);

	/*!
	 * \brief Converts the textual representation of a IPV4 address to it's binary form.
	 *	
	 * 		  In it's textual representation, each 8 bit chunk is separated by a dot.
	 *		  During conversion, these 8 bit chunks are parsed out and converted to
	 *		  to fit in a 32 bit integer (8 * 4 = 32).
	 *
	 * \param ip The textual representation of an IPV4 address to convert to it's binary
	 *			 form.
	 *
	 * \returns The binary form of the specified IPV4 address. Zero is returned when something
	 *		 	went wrong.
	 */
	static unsigned int IPV4AddressToBinary(std::string ip);

private:
	// Creates the native socket (BSD socket) and stores it into the 'm_native_socket' member.
	bool		__create_native_socket();

	// Sets the members of the 'sockaddr_in' struct (m_remote_address) to the remote host address
	// and port number. Depending on which type of socket this instance is.
	bool		__set_address_struct();

	// Attempts to setup a connection with the remote host, according to the information
	// stored in 'm_remote_address'. Only used when the socket is of type 'client'.
	bool		__native_connect();
	
	// Binds the underlying native socket on the port specified in 'm_remote_port'. Only used
	// in 'server' mode.
	bool		__bind_on_port();

	// Starts listening for incoming remote connections, should only be used after binding
	// on a port. Only used when the socket is of the type 'server'.
	bool		__listen();
	
	// Updates the member variable 'm_last_error' with errno or WSAGetLastError(), depending
	// on the platform.
	void		__update_last_error();

	// Enfores the timeout, by re-setting socket options with the value from m_timeout_milliseconds.
	bool		__enfore_timeout();

	// Updates the value of 'm_remote_host' with the host name in m_remote_address.
	void		__update_remote_host();

	// Only does something wen compiling for windows, makes sure winsock is initialized.
	void		__init_winsock();

private:
	// Holds the host name or IP address of the remote host that this socket
	// is connected to.
	std::string 			m_remote_host;
	
	// Holds the port number that this socket is connected over.
	unsigned int			m_remote_port;

	// Indicates whether there is an active connection with the remote host.
	bool					m_connected;

	// Holds the last error number that was casued by the last socket operation.
	int						m_last_error;
	
	// Holds the underlying native socket (BSD socket).
	int 					m_native_socket;

	// Holds the address structure, which consists of the remote host and port number.
	struct sockaddr_in		m_remote_address;
	
	// Holds the timeout structure, which consists of the timeout used
	// for connecting, sending and receiving.
	struct timeval 			m_timeout;

	// Holds the timeout that is used for socket operations in milliseconds.
	int						m_timeout_milliseconds;
	
	// Holds the role that this instance is.
	SocketRole				m_socket_role;

	// Holds what kind of protocol this socket uses
	SocketProtocol			m_protocol;
};

/*!
 * \brief A simple typedef for the shared pointer of a TcpSocket instance.
 */
typedef std::shared_ptr<Socket> SocketPtr;

} // namespace Senergy

#endif // SY_SOCKET
