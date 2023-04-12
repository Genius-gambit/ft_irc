/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:06:06 by wismith           #+#    #+#             */
/*   Updated: 2023/04/13 00:36:16 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ERROR_HPP
# define ERROR_HPP

# include <iostream>
# include <exception>

class IncorrectArgs : public std::exception
{
	public :
		const char* what() const throw()
		{
			return ("ft_irc: Err: Incorrect Arguments!\n");
		}
};

class BindingFailure : public std::exception
{
	public :
		const char* what() const throw()
		{
			return ("ft_irc: Err: Failed to connect!\n");
		}
};

class SocketFailure : public std::exception
{
	public :
		const char* what() const throw()
		{
			return ("ft_irc: Err: Failed to create socket!\n");
		}
};

class error
{
	public :
		error();
		error(const error &e);
		~error();
		
		error	&operator=(const error &e);

		void	argc(const int num);
		void	port(const std::string &str);

		void	SocketCheck(int rtn);
		void	ConnectionCheck(int rtn);
};

#endif