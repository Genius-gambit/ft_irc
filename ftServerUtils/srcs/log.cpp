/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:50:54 by wismith           #+#    #+#             */
/*   Updated: 2023/05/01 20:34:14 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/log.hpp"

/** @brief Name Constructor: inits all values
 * 	@note takes a file name as parameter. File does not have
 * 			to be an existing file.
 */
ft::log::log (const std::string &name) : lineNum(0), Name(name),
	Content(), lastLog() {}

/** @brief Destructor*/
ft::log::~log() {}

/** @brief pushLog method used to push a new log message into chosen
 * 			log file. If Log file exists prior to log object construction
 * 			content within will be replaced with new content upon initial 
 * 			call to method, afterwhich content will simply be added below
 * 			current content.
*/
void	ft::log::pushLog(const std::string &msg)
{
	std::ofstream	outfile(this->Name.c_str());
	this->lastLog = msg;
	this->lineNum++;
	if (outfile.good())
	{
		this->Content += (std::string() << this->lineNum) + " : ";
		this->Content += msg;
		this->Content += "\n";
		outfile << this->Content;
	}
	outfile.close();
}

/** @brief returns a string of the log file's name */
std::string	ft::log::getFileName() const
{
	return (this->Name);
}

/** @brief returns a string of the last logged message */
std::string	ft::log::getLastLog() const
{
	return (this->lastLog);
}

/** @brief returns an int of number of lines logged within file */
int			ft::log::getNumLines() const
{
	return (this->lineNum);
}

/** @brief << operator overload used to push new message into
 * 			the log file.
*/
ft::log	&operator<<(ft::log &l, std::string const &msg)
{
	l.pushLog(msg);
	return (l);
}
