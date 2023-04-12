/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:07:24 by wismith           #+#    #+#             */
/*   Updated: 2023/04/13 01:01:29 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

int	main(int argc, char **argv)
{
	/**	@brief : Check arguments are valid */
	try{
		error().argc(argc);
		error().port(argv[1]);
	}catch(const std::exception &e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	/**	@brief : handle signals */
	catch_signals();

	/**	@brief : run server */
	while (g_server_run)
	{
		std::cout << "running!\n";
		sleep (1);
	}
	
	/**	@brief : free stuff if necessary */

	return (0);
}