/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:30:53 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 14:31:00 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/ft_printf.h"

static void		setup_conv_table(t_conv_table conv_table[128])
{
	conv_table['c'] = &handle_char;
	conv_table['s'] = &handle_str;
	conv_table['p'] = &handle_uint_hex;
	conv_table['d'] = &handle_int;
	conv_table['i'] = &handle_int;
	conv_table['u'] = &handle_unsigned_int_dec;
	conv_table['x'] = &handle_uint_hex;
	conv_table['X'] = &handle_uint_hex;
	conv_table['%'] = &handle_escape;
}

/*
**	get_func() - Setup a conv_table so that we can get the relevant function
**	for any given arg_type that we find.
**
**	We make our conv_table static so we only need to set it once per printf call
**	and give it a size of 127 + 1 (the max value for an ascii char)
**
**	We need to protect our conv_ table lookup by making sure our char c is
**	an ascii.
*/

t_conv_table		get_handler_funct(char c)
{
	static t_conv_table	arg_type_jt[128] = {NULL};

	if (arg_type_jt['%'] == NULL)
		setup_conv_table(arg_type_jt);
	if (ft_isascii(c))
		return (arg_type_jt[(int)c]);
	else
		return (NULL);
}
