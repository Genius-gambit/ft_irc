/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connecter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:48:45 by wismith           #+#    #+#             */
/*   Updated: 2023/04/14 17:54:28 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connecter.hpp"

ft::Connecter::Connecter(int domain, int service, int protocol, int port, unsigned long interface)
	: SetSocket(domain, service, protocol, port, interface)
{
	this->setConnection(this->connect_net(this->getSock(), this->getAddress()));
}

int	ft::Connecter::connect_net(int sock, struct sockaddr_in addr)
{
	return (connect(sock, (struct sockaddr *)&addr, sizeof(addr)));
}

ft::Connecter	&ft::Connecter::operator=(const Connecter &b){(void)b; return (*this);}