/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:30:53 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 17:57:18 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/ft_printf.h"

static void		setup_conv_table(t_convtable conv_table[128])
{
	conv_table['c'] = &handle_char;
	conv_table['s'] = &handle_str;
	conv_table['p'] = &handle_uint_hex;
	conv_table['d'] = &handle_int;
	conv_table['i'] = &handle_int;
	conv_table['u'] = &handle_uint;
	conv_table['x'] = &handle_uint_hex;
	conv_table['X'] = &handle_uint_hex;
	conv_table['%'] = &handle_percent;
}

t_convtable		get_funct(char c)
{
	static t_convtable	arg_type_ct[128] = {NULL};

	if (arg_type_ct['%'] == NULL)
		setup_conv_table(arg_type_ct);
	if (ft_isascii(c))
		return (arg_type_ct[(int)c]);
	else
		return (NULL);
}
