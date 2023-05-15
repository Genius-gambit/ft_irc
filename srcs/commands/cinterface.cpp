/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinterface.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:37:28 by wismith           #+#    #+#             */
/*   Updated: 2023/05/05 21:41:17 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

using namespace ft;

cinterface::cinterface(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	clients(c), pfds(p), password(pw) {}

cinterface::~cinterface() {}

void cinterface::reply(ft::client &c, const std::string &code, const std::string &msg)
{
	c.addBacklog(": " + code + " " + c.getNick() + " :" + msg + "\r\n");
}

void cinterface::welcome(ft::client &c)
{
	this->reply(c, RPL_WELCOME, "Welcome to the irc server!");
	this->reply(c, RPL_YOURHOST, "Your host is ircserv, running version 1");
	this->reply(c, RPL_CREATED, "Server development started April 7th");
	this->reply(c, RPL_MYINFO, "");
}
