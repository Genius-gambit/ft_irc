/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:07:24 by wismith           #+#    #+#             */
/*   Updated: 2023/05/12 15:22:47 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/channels.hpp"
#include <iostream>

using namespace ft;

channels::channels(void) : _len(0)
{
	this->_pass = "";
}

channels::~channels() {}

void	channels::setChannelName(const std::string &name)
{
	this->_chan = name.substr(1, name.length());
}

void	channels::setChannelPass(const std::string &pass)
{
	this->_pass = pass;
}

std::string	channels::get_pass() { return (this->_pass); }

std::string	channels::getChannelName() { return (this->_chan); }

void	channels::add_clients(int fd)
{
	for (std::vector<int>::iterator it = this->fds.begin(); it  != this->fds.end(); it++)
	{
		if (*it == fd)
		{
			std::cout << "Already a Member" << std::endl;
			return ;
		}
	}
	this->fds.push_back(fd);
	this->_len++;
	std::cout << "Length: " << this->_len << std::endl;
}

void	channels::kick_client(int fd)
{
	std::vector<int>::iterator	it;

	for (it = this->fds.begin(); it != this->fds.end(); it++)
	{
		if (*it == fd)
		{
			this->_len--;
			break;
		}
	}
	this->fds.erase(it);
}

int	channels::get_length() { return (this->_len); }

std::vector<int>	&channels::getFds() { return (this->fds); }

//sendtoAll function should send message to all clients
//except to itself
void	channels::sendToAll(const std::string &msg, std::map<int, CLIENT> &clients, int fd)
{
	for (std::vector<int>::iterator it = this->fds.begin(); it != this->fds.end(); it++)
	{
		if (*it != fd)
			clients[*it].addBacklog(msg);
	}
}


void	channels::print_clients()
{
	for (std::vector<int>::iterator it = this->fds.begin(); it != this->fds.end(); it++)
		std::cout << *it << std::endl;
}