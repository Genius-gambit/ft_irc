/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:07:24 by wismith           #+#    #+#             */
/*   Updated: 2023/04/08 22:21:42 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

bool	args_check(int argc, std::string port)
{
	if (argc != 3 || port.find_first_not_of("0123456789") != port.npos)
		return (true);
	return (false);	
}

int	main(int argc, char **argv)
{
	if (args_check(argc, argv[1]))
	{
		std::cerr << "ft_irc: Err: Incorrect Arguments!\n";
		std::cout << "Please execute as follows:\n\t";
		std::cout << "./ft_irc <port number> <password>\n";
		return (1);
	}
	return (0);
}