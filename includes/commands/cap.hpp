/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:24:54 by wismith           #+#    #+#             */
/*   Updated: 2023/05/07 17:27:11 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CAP_HPP
# define CAP_HPP

# include "cinterface.hpp"

namespace ft
{
	class cap : public ft::cinterface
	{
		public :
			cap (std::map<CLIENT_FD, CLIENT> &, std::vector<pollfd> &, std::string &);
			~cap ();

			void exec(int, const std::vector<std::string> &);
	};
};

#endif