/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:13:37 by wismith           #+#    #+#             */
/*   Updated: 2023/05/03 18:43:27 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"

using namespace ft;

parser::parser() : cmds(), log("server.log") {}

parser::~parser() {}

void	parser::pRecv(const std::string &cmd)
{
	std::stringstream			ss(cmd);
	std::string					line;
	std::string					word;
	std::vector<std::string>	save;

	while (!ss.eof())
	{
		getline(ss, line, '\n');
		save.push_back(line);
		// this->cmds.push_back(word);
	}

	for (size_t i = 0; i < save.size(); i++)
	{
		std::stringstream		stream(save[i]);
		while (!stream.eof())
		{
			getline(stream, word, ' ');
			this->cmds.push_back(word);
		}
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
