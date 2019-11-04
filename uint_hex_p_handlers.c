/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_hex_p_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:30:59 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 18:04:30 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/ft_printf.h"
#define UPPER(x) ((x)=='X')

static	uintmax_t	get_arg(t_info *info)
{
	if (info->arg_type == 'p')
		return ((uintmax_t)(uintptr_t)va_arg(info->args, void *));
	else
		return ((uintmax_t)va_arg(info->args, unsigned int));
}

void				handle_uint(t_info *info)
{
	uintmax_t	nbr;
	uintmax_t	tmp;
	int			len;
	int			fg;

	fg = info->flags;
	info->base = 10;
	nbr = get_arg(info);
	tmp = nbr;
	len = 0;
	while (tmp && ++len)
		tmp /= info->base;
	len += (nbr == 0 && !(fg & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (fg & PRECISION_FLAG)
		fg ^= ZERO_FLAG;
	handle_int_prepad(info, len, 0);
	pf_itoa_base(info, (uintmax_t)ABS(nbr), len);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, MAX(info->precision, len));
}

void				handle_uint_hex(t_info *info)
{
	uintmax_t	nbr;
	uintmax_t	tmp;
	int			len;
	int			fg;

	if (info->arg_type == 'p')
		info->flags |= HASH_FLAG;
	fg = info->flags;
	info->base = 16;
	nbr = get_arg(info);
	info->hex_int = nbr;
	tmp = nbr;
	len = 0;
	while (tmp && ++len)
		tmp /= info->base;
	len += (nbr == 0 && !(fg & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (fg & PRECISION_FLAG)
		fg ^= ZERO_FLAG;
	if (fg & HASH_FLAG && (nbr != 0 || info->arg_type == 'p'))
		info->width -= 2;
	handle_int_prepad(info, len, 0);
	pf_itoa_base(info, (uintmax_t)ABS(nbr), len);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, MAX(info->precision, len));
}
