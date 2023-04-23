/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:39:31 by wismith           #+#    #+#             */
/*   Updated: 2023/04/23 01:45:05 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

//* ------------- Constructors ------------- *//
/** @brief client default constructor */
ft::client::client() {}

/** @brief client file descriptor constructor
 * @note initializes fd to one passed as parameter,
 * 		sets status as illegal (Default), and instantiates,
 * 		reader with file descriptor.
*/
ft::client::client(int nfd) : fd(nfd), status(ILLEGAL), nick(), reader(fd) {}

/** @brief Copy Constructor */
ft::client::client(const ft::client &c) : fd(c.fd), status(c.status),
	nick(c.nick), reader(c.reader) {}
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
		this->reader = c.reader;
	}
	return (*this);
}

//! ------------- Server Operation Methods ------------- *//
std::string	ft::client::Read()
{
	return (this->reader.retrieve().getData());
}

void	ft::client::Write(std::string str)
{
	send(this->fd, str.c_str(), str.size(), 0);
}
//! ------------- End Server Operation Methods ------------- *//

//? ------------- Setters ------------- *//
void	ft::client::setFd(int nfd)
{
	this->fd = nfd;
	this->reader.setFd(this->fd);
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
