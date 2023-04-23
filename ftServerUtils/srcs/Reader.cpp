/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:24:48 by wismith           #+#    #+#             */
/*   Updated: 2023/04/18 22:56:30 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Reader.hpp"
#include <unistd.h>

ft::Reader::Reader() {
	this->data = new std::string;
}

ft::Reader::Reader(int nfd) {
	this->data = new std::string;
	this->fd = nfd;
}

ft::Reader::Reader(const Reader &r) {
	this->data = new std::string;
	this->operator=(r);
}

ft::Reader::~Reader() {
	delete this->data;
}

ft::Reader	&ft::Reader::operator=(const ft::Reader &r)
{
	if (this != &r)
	{
		*this->data = *r.data;
		this->fd = r.fd;
	}
	return (*this);
}

ft::Reader	&ft::Reader::retrieve()
{
	char		Buff[BUFFER] = { 0 };

	recv(this->fd, Buff, sizeof(Buff), 0);
	*this->data = std::string(Buff);
	return (*this);
}

void	ft::Reader::setFd(int nfd) {
	this->fd = nfd;
}

std::string	ft::Reader::getData()
{
	return (*this->data);
}
