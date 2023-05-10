/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:07:24 by wismith           #+#    #+#             */
/*   Updated: 2023/05/10 20:07:59 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/channels.hpp"

using namespace ft;

channels::channels(void) {}

channels::~channels() {}

void	channels::setChannelName(const std::string &name)
{
	this->_chan = name;
}

void	channels::add_clients(int fd)
{
	this->fds.push_back(fd);
}

void	channels::kick_client(int fd)
{
	std::vector<int>::iterator	it;

	for (it = this->fds.begin(); it != this->fds.end(); it++)
	{
		if (*it == fd)
			break;
	}
	this->fds.erase(it);
}