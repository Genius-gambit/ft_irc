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

channels::channels(void) : _len(0) {}

channels::~channels() {}

void	channels::setChannelName(const std::string &name)
{
	this->_chan = name;
}

void	channels::add_clients(int fd)
{
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

void	channels::print_clients()
{
	std::cout << "*******Clients*******" << std::endl;
	std::cout << "Number of Clients: " << get_length() << std::endl;
	for (std::vector<int>::iterator it = this->fds.begin(); it != this->fds.end(); it++)
		std::cout << *it << std::endl;
	std::cout << "*******End*******" << std::endl;
}