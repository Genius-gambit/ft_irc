/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listener.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:00:43 by wismith           #+#    #+#             */
/*   Updated: 2023/04/20 15:56:19 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Listener.hpp"

ft::Listener::Listener() : ft::SetSocket(), backlog(1024) {}

ft::Listener::~Listener() {}

ft::Listener	&ft::Listener::operator=(const ft::Listener &l)
{
	(void) l;
	return (*this);
}

/**	@brief setInfo method is used to set all the attributes for Listener object,
 * 			will call socket system call to initialize the socket fd (sock) attribute.
 * @note example input :
 * 			Domain: AF_INET, Service: SOCK_STREAM, protocol: 0, port: 6697, interface: INADDR_ANY
 * 	@note Throws SocketFailure Exception if socket system call fails. 
 */
void	ft::Listener::setInfo(int domain, int service, int protocol,
						int port, unsigned long interface)
{
	// int	opt = 1;
	struct sockaddr_in	newAddr;

	this->setSock(socket(domain, service, protocol));
	error().SocketCheck(this->getSock());
	
	// int res = setsockopt(this->getSock(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	// std::cout << "res setSockOpt : " << res << std::endl;
	// res = setsockopt(this->getSock(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
	// std::cout << "res setSockOpt : " << res << std::endl;

	newAddr.sin_family = domain;
	newAddr.sin_port = htons(port);
	newAddr.sin_addr.s_addr = htonl(interface);
	
	this->setAddress(newAddr);
}

/**	@brief ListenConnect method initializes listening for the socket
 * @note Method requires no arguments, however, setInfo and BindConnect methods should
 * 			be called before ListenConnect.
 * @note example :
 * @note -> Listener.setInfo(arguments...)
 * @note ->	Listener.nonBlocking()
 * @note ->	Listener.BindConnect()
 * @note ->	Listener.ListenConnect()
 * 	@note Throws ListenFailure Exception if listen fails. 
 */
void	ft::Listener::ListenConnect()
{
	error().LstnCheck(listen(this->getSock(), this->backlog));
}

/**	@brief nonBlocking method uses fcntl system call to set socket
 * 			to non blocking.
 * 			Socket is is an attribute within the SetSocket class inherited by
 * 			Listener.
 *  @note Method requires no arguments, however setInfo method should be
 * 			called before nonBlocking, in order that the attributes of Listener
 * 			may be initialized. Attributes should be initialized for method to work.
 * 	@note throws FcntlFailure exception if fcntl system call fails
 */
void	ft::Listener::nonBlocking()
{
	int	flag = fcntl(this->getSock(), F_GETFL);
	error().BlockCheck(flag);
	flag = fcntl(this->getSock(), F_SETFL, flag | O_NONBLOCK);
	error().BlockCheck(flag);
}

/**	@brief connect_net method used to perform bind system call
 * @note error class is used to check if bind was successful, and
 * 			will throw a BindingFailure Exception if not
 */
int	ft::Listener::connect_net(int sock, struct sockaddr_in addr)
{
	int	res = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	error().BindCheck(res);
	return (res);
}

/**	@brief BindConnect method used to perform bind system call
 * 				assuming required vars have already been set using the value
 * 				constructor, or the setInfo method.
 * @note error class is used to check if bind was successful, and
 * 			will throw a BindingFailure Exception if not
 */
void	ft::Listener::BindConnect()
{
	this->setConnection(this->connect_net(this->getSock(), this->getAddress()));
}

void	ft::Listener::setSockProto(int level, int option_name, int &opt)
{
	error().sockOptErr(setsockopt(this->getSock(), level, option_name, &opt, sizeof(opt)));
}

