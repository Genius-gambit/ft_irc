/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:42:43 by wismith           #+#    #+#             */
/*   Updated: 2023/04/13 01:06:05 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef SIGNALS_HPP
# define SIGNALS_HPP

# include <sys/signal.h>


/**	@brief : global determines whether server keeps running */
extern bool	g_server_run;

/**	@brief : signal handler prototype */

/**	@brief : signals that terminate are caught by catch_signals
 * @note : We want to catch signals to avoid memory leaks.
 * 	Instead of terminating the program immediately, we break the
 * 		server loop so the program can move on to freeing and exiting,
 * 		properly.
 */
void	catch_signals();

#endif