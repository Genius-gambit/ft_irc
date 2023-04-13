/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:50:47 by wismith           #+#    #+#             */
/*   Updated: 2023/04/13 01:02:58 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include <iostream>

bool	g_server_run = true;

void	sighandlr(int signum)
{
	(void) signum;
	g_server_run = false;
	std::cout << "\nStopping server!\n";
}

void	catch_signals()
{
	signal(SIGINT, sighandlr);
	signal(SIGQUIT, sighandlr);
}
