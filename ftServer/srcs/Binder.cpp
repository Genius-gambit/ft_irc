/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Binder.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:28:30 by wismith           #+#    #+#             */
/*   Updated: 2023/04/14 02:58:04 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Binder.hpp"

ft::Binder::Binder(int domain, int service, int protocol, int port, unsigned long interface)
	: SetSocket(domain, service, protocol, port, interface)
{
	this->setConnection(this->connect_net(this->getSock(), this->getAddress()));
}

int	ft::Binder::connect_net(int sock, struct sockaddr_in addr)
{
	return (bind(sock, (struct sockaddr *)&addr, sizeof(addr)));
}

ft::Binder	&ft::Binder::operator=(const Binder &b){(void)b; return (*this);}