/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:54:27 by wismith           #+#    #+#             */
/*   Updated: 2023/04/20 23:05:09 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SetSocket.hpp"

/**	@brief : Default constructor */
ft::SetSocket::SetSocket(){}

/**	@brief : Value Constructor initializes data to the arguments passed
 * @note : example input :
 * 			Domain: AF_INET, Service: SOCK_STREAM, protocol: 0, port: 6697, interface: INADDR_ANY
*/
ft::SetSocket::SetSocket(int domain, int service, int protocol, int port, unsigned long interface)
{
	this->setInfo(domain, service, protocol, port, interface);
}

/**	@brief : Destructor
 * @note : Upon destruction of the object, the socket file descriptor is closed
 */
ft::SetSocket::~SetSocket()
{
	shutdown (this->sock, SHUT_RDWR);
}

/**	@brief : Copy assignment operator overload
 * @note : Simply voids the parameter since it is market private
 */
ft::SetSocket	&ft::SetSocket::operator=(const SetSocket &e)
{
	(void)e;
	return (*this);
}

/**	@brief : getAddress getter will return the address structure
 * @note : return type is 'struct sockaddr_in' 
 */
struct sockaddr_in	&ft::SetSocket::getAddress()
{
	return (this->address);
}

/**	@brief : getSock getter returns the socket file-descriptor */
int	ft::SetSocket::getSock() const
{
	return (this->sock);
}

/**	@brief : getConnection getter returns the status returned by bind(), connect(), and listen()
 * 				depending on the heir (inheriting object)
 */
int	ft::SetSocket::getConnection() const
{
	return (this->connection);
}

/**	@brief : setConnection Method sets the connection attribute in SetSocket;
 * 			the connection is the return of bind(), connect(), or listen() system
 * 				calls, depending on the heir (inheriting object)
 */
void	ft::SetSocket::setConnection(int con)
{
	this->connection = con;
}

/**	@brief : setAddress method sets the address attribute to the value passed as
 * 				parameter. The address attribute is of type struct sockaddr_in.
 */
void	ft::SetSocket::setAddress(const struct sockaddr_in &addr)
{
	this->address = addr;
}

/**	@brief : setSocket sets the socket fd to the file descriptor returned by socket */
void	ft::SetSocket::setSock(const int sockfd)
{
	this->sock = sockfd;
}

/**	@brief : setInfo method sets the attributes of the address structure to the values passed
 * 			as parameter. It will then perform a socket system call and set the sock attribute to
 * 				the socket file descriptor. If socket failed then SocketFailure() exception is thrown.
 * @note : example of input:
 * 				Domain: AF_INET, Service: SOCK_STREAM, protocol: 0, port: 6697, interface: INADDR_ANY
 */
void	ft::SetSocket::setInfo(int domain, int service, int protocol, int port, unsigned long interface)
{
	this->address.sin_family = domain;
	this->address.sin_port = htons(port);
	this->address.sin_addr.s_addr = htonl(interface);
	this->setSock(socket(domain, service, protocol));

	error().SocketCheck(this->getSock());
}
