/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:39:31 by wismith           #+#    #+#             */
/*   Updated: 2023/05/08 23:16:20 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

//* ------------- Constructors ------------- *//
/** @brief client default constructor */
ft::client::client() : fd(0), status(ILLEGAL), nick(), backlog() {}

/** @brief client file descriptor constructor
 * @note initializes fd to one passed as parameter,
 * 		sets status as illegal (Default), and instantiates,
 * 		reader with file descriptor.
*/
ft::client::client(int nfd) : fd(nfd), status(ILLEGAL), nick() {}

/** @brief Copy Constructor */
ft::client::client(const ft::client &c) : fd(c.fd), status(c.status),
	nick(c.nick) {}
//* ------------- End Constructors ------------- *//

/** @brief client destructor */
ft::client::~client() {}

/** @brief Copy assignment operator overload */
ft::client &ft::client::operator=(const client &c)
{
	if (this != &c)
	{
		this->setFd(c.getFd());
		this->setNick(c.getNick());
		this->setStatus(c.getStatus());
	}
	return (*this);
}

//! ------------- Server Operation Methods ------------- *//
std::string	ft::client::Read()
{
	std::string	str;
	str.resize(512);
	recv(this->fd, const_cast<char *>(str.data()), str.size() - 1, 0);
	return (str);
}

void	ft::client::Write(std::string str)
{
	send(this->fd, str.c_str(), str.size(), 0);
}

void	ft::client::addBacklog(const std::string reply)
{
	this->backlog.push_back(reply);
}

size_t	ft::client::getBacklogSize() const
{
	return (this->backlog.size());
}

std::string	ft::client::retrBacklog()
{
	std::string	str(this->backlog.front());

	this->backlog.pop_front();
	return (str);
}
//! ------------- End Server Operation Methods ------------- *//

//? ------------- Setters ------------- *//
void	ft::client::setFd(int nfd)
{
	this->fd = nfd;
}

void	ft::client::setStatus(int stat)
{
	this->status = stat;
}

void	ft::client::setNick(const std::string &Nick)
{
	this->nick = Nick;
}
//? ------------- End Setters ------------- *//

//? ------------- Getters ------------- *//
int	ft::client::getFd() const
{
	return (this->fd);
}

int	ft::client::getStatus() const
{
	return (this->status);
}

std::string	ft::client::getNick() const
{
	return (this->nick);
}
//? ------------- End Getters ------------- *//


//! Non members

void	operator>>(const std::string &str, ft::client &c)
{
	c.Write(str);
}

std::string		&operator<<(std::string &str, ft::client &c)
{
	str = c.Read();
	return (str);
}
