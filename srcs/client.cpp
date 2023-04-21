/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:39:31 by wismith           #+#    #+#             */
/*   Updated: 2023/04/21 20:12:41 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

ft::client::client() : fd(0), reader() {}

ft::client::client(int nfd) : fd(nfd), reader(fd)
{
	pfd[IN].fd = this->fd;
	pfd[IN].events = POLLIN;
	pfd[OUT].fd = this->fd;
	pfd[OUT].events = POLLOUT;
}

ft::client::client(const ft::client &c) : fd(c.fd), reader(c.reader)
{
	pfd[IN].fd = this->fd;
	pfd[IN].events = POLLIN;
	pfd[OUT].fd = this->fd;
	pfd[OUT].events = POLLOUT;
}

ft::client::~client() {}

ft::client &ft::client::operator=(const client &c)
{
	if (this != &c)
	{
		this->setFd(c.fd);
		pfd[IN].fd = this->fd;
		pfd[IN].events = POLLIN;
		pfd[OUT].fd = this->fd;
		pfd[OUT].events = POLLOUT;
	}
	return (*this);
}

std::string	ft::client::Read()
{
	return (this->reader.retrieve().getData());
}

void	ft::client::Write(std::string str)
{
	send(this->fd, str.c_str(), str.size(), 0);
}

struct pollfd	*ft::client::getPfd()
{
	return (this->pfd);
}

void	ft::client::setFd(int nfd)
{
	this->fd = nfd;
	this->reader.setFd(this->fd);
	pfd[IN].fd = this->fd;
	pfd[IN].events = POLLIN;
	pfd[OUT].fd = this->fd;
	pfd[OUT].events = POLLOUT;
}

int	ft::client::getFd() const
{
	return (this->fd);
}
