/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:13:37 by wismith           #+#    #+#             */
/*   Updated: 2023/04/26 19:57:23 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"

using namespace ft;

parser::parser() : cmds() {}

parser::~parser() {}

void	parser::pRecv(const std::string &cmd)
{
	std::stringstream	ss(cmd);
	std::string			word;

	while (!ss.eof())
	{
		getline(ss, word, ' ');
		this->cmds.push_back(word);
	}
}

void	parser::printCmds()
{
	for (size_t i = 0; i != this->cmds.size(); i++)
		std::cout << i << ": " << this->cmds[i] << std::endl;
}

void	parser::clear()
{
	this->cmds.clear();
}

std::vector<std::string>	&parser::getCmds()
{
	return (this->cmds);
}
