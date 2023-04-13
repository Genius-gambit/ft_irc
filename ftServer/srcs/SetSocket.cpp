/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:54:27 by wismith           #+#    #+#             */
/*   Updated: 2023/04/14 02:58:43 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SetSocket.hpp"

// ft::SetSocket::SetSocket(){}
// ft::SetSocket::SetSocket(const SetSocket &e){(void)e;}

ft::SetSocket::~SetSocket(){}

ft::SetSocket	&ft::SetSocket::operator=(const SetSocket &e){(void)e; return (*this);}

ft::SetSocket::SetSocket(int domain, int service, int protocol, int port, unsigned long interface)
{
	this->address.sin_family = domain;
	this->address.sin_port = htons(port);
	this->address.sin_addr.s_addr = htonl(interface);
	this->sock = socket(domain, service, protocol);
}

struct sockaddr_in	ft::SetSocket::getAddress() const
{
	return (this->address);
}

int	ft::SetSocket::getSock() const
{
	return (this->sock);
}

int	ft::SetSocket::getConnection() const
{
	return (this->connection);
}

void	ft::SetSocket::setConnection(int con)
{
	this->connection = con;
}