/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:47:32 by nmei              #+#    #+#             */
/*   Updated: 2019/11/04 13:25:52 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/ft_printf.h"
#define UPPER(x) ((x)=='X')

/*
**	get_unsigned_int_arg()
**	If we're handling uints then we need to invoke va_arg. Because dealing
**	with different size possibilities is a pain, it's easiest to promote
**	everything to the max uint size type.
**
**	We have to do a slight shuffle so that L_FLAG is checked before
**	H_FLAG because U and O arg_type should take precedence...
**
**	pointer addresses ('p') are simply a special case of hex uints.
*/

static	uintmax_t	get_unsigned_int_arg(t_info *info)
{
	if (info->arg_type == 'p')
		return ((uintmax_t)(uintptr_t)va_arg(info->args, void *));
	else
		return ((uintmax_t)va_arg(info->args, unsigned int));
}

void				handle_unsigned_int_dec(t_info *info)
{
	uintmax_t	nbr;
	uintmax_t	tmp;
	int			nbrlen;
	int			fg;

	fg = info->flags;
	info->base = 10;
	nbr = get_unsigned_int_arg(info);
	tmp = nbr;
	nbrlen = 0;
	while (tmp && ++nbrlen)
		tmp /= info->base;
	nbrlen += (nbr == 0 && !(fg & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (fg & PRECISION_FLAG)
		fg ^= ZERO_FLAG;
	handle_int_prepad(info, nbrlen, 0);
	fg_itoa_base(info, (uintmax_t)ABS(nbr), nbrlen);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, MAX(info->precision, nbrlen));
}

void				handle_unsigned_int_oct(t_info *info)
{
	uintmax_t	nbr;
	uintmax_t	tmp;
	int			nbrlen;
	int			fg;

	fg = info->flags;
	info->base = 8;
	nbr = get_unsigned_int_arg(info);
	tmp = nbr;
	nbrlen = 0;
	while (tmp && ++nbrlen)
		tmp /= info->base;
	nbrlen += (nbr == 0 && !(fg & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (fg & PRECISION_FLAG)
		fg ^= ZERO_FLAG;
	if (fg & HASH_FLAG && nbr != 0)
		info->width--;
	handle_int_prepad(info, nbrlen, 0);
	if ((fg & HASH_FLAG && nbr != 0) || (fg & HASH_FLAG && fg & PRECISION_FLAG))
		buff(info, "0", 1);
	fg_itoa_base(info, (uintmax_t)ABS(nbr), nbrlen);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, MAX(info->precision, nbrlen));
}

void				handle_unsigned_int_hex(t_info *info)
{
	uintmax_t	nbr;
	uintmax_t	tmp;
	int			nbrlen;
	int			fg;

	if (info->arg_type == 'p')
		info->flags |= HASH_FLAG;
	fg = info->flags;
	info->base = 16;
	nbr = get_unsigned_int_arg(info);
	info->hex_int = nbr;
	tmp = nbr;
	nbrlen = 0;
	while (tmp && ++nbrlen)
		tmp /= info->base;
	nbrlen += (nbr == 0 && !(fg & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (fg & PRECISION_FLAG)
		fg ^= ZERO_FLAG;
	if (fg & HASH_FLAG && (nbr != 0 || info->arg_type == 'p'))
		info->width -= 2;
	handle_int_prepad(info, nbrlen, 0);
	fg_itoa_base(info, (uintmax_t)ABS(nbr), nbrlen);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, MAX(info->precision, nbrlen));
}
