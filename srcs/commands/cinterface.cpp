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

#include "../../includes/commands/cinterface.hpp"

using namespace ft;

cinterface::cinterface(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	clients(c), pfds(p), password(pw) {}

cinterface::~cinterface() {}
