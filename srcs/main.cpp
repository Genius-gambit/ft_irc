/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:07:24 by wismith           #+#    #+#             */
/*   Updated: 2023/04/25 00:31:16 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"
#include "../includes/server.hpp"
#include <poll.h>

int	main(int argc, char **argv)
{
	/**	@brief : variable contains port number after parsing */
	int			port;
	std::string	password;

	/**	@brief : Check arguments are valid */
	try {
		error().argc(argc);
		port = error().port(argv[1]);
		password = std::string(argv[2]);
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	ft::server	server(port, password);
	catch_signals();

	try {
		server.init();
		server.run();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}