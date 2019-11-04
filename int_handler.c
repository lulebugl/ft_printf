/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:55:33 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 18:01:29 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/ft_printf.h"

void			handle_int(t_info *info)
{
	intmax_t	nbr;
	intmax_t	tmp;
	int			len;
	int			fg;

	fg = info->flags;
	info->base = 10;
	nbr = (intmax_t)va_arg(info->args, signed int);
	tmp = nbr;
	len = 0;
	info->neg = (nbr < 0) ? 1 : 0;
	while (tmp && ++len)
		tmp /= info->base;
	len += (nbr == 0 && !(fg & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (nbr < 0 || fg & PLUS_FLAG || fg & SPACE_FLAG)
		info->width--;
	if (fg & PRECISION_FLAG)
		fg ^= ZERO_FLAG;
	handle_int_prepad(info, len, 1);
	pf_itoa_base(info, (uintmax_t)ABS(nbr), len);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, MAX(info->precision, len));
}
