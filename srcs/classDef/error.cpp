/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:16:09 by wismith           #+#    #+#             */
/*   Updated: 2023/04/13 00:33:57 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.hpp"

error::error(){}

error::error(const error &e){(void)e;}

error::~error(){}

error &error::operator=(const error &e){(void)e; return (*this);}

void	error::argc(const int num){(num != 3 ? throw(IncorrectArgs()) : (void)num);}

void	error::port(const std::string &port_){
	size_t margin = port_.find_first_not_of("0123456789");
	(margin != port_.npos ? throw(IncorrectArgs()) : (void)port_);
}

void	error::SocketCheck(int rtn)
{
	if (rtn < 0)
		throw (SocketFailure());
}

void	error::ConnectionCheck(int rtn)
{
	if (rtn)
		throw (BindingFailure());
}