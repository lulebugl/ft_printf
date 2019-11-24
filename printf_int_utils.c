/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:20:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/17 20:42:04 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "ft_printf.h"

#define HEX(x) ((x)=='x'||(x)=='X'||(x)=='p')

void			pf_itoa_base(t_pfinfo *info, uintmax_t nbr, int len)
{
	int		base;
	char	*conv;
	char	res[27];
	int		tmp_len;

	base = info->base;
	tmp_len = len;
	conv = (info->arg_type == 'X') ?
		ft_strdup("0123456789ABCDEF") : ft_strdup("0123456789abcdef");
	res[len] = '\0';
	while (len-- > 0)
	{
		res[len] = conv[nbr % base];
		nbr /= base;
	}
	free(conv);
	buff(info, res, tmp_len);
}

static void		handle_prepend(t_pfinfo *info, int signed_int)
{
	int	spec;

	spec = info->arg_type;
	if (info->neg)
		buff(info, "-", 1);
	else if (info->flags & PLUS_FLAG && signed_int)
		buff(info, "+", 1);
	else if (info->flags & SPACE_FLAG && signed_int)
		buff(info, " ", 1);
	if (info->flags & HASH_FLAG && HEX(spec) &&
		((info->hex_int != 0) || spec == 'p'))
		(info->arg_type == 'X') ? buff(info, "0X", 2) : buff(info, "0x", 2);
}

void			handle_int_prepad(t_pfinfo *info, int len, int signed_int)
{
	int		lenzero;
	int		prec;

	prec = (info->flags & PRECISION_FLAG) ? MAX(info->precision, len) : len;
	lenzero = (info->precision > len) ? info->precision - len : 0;
	if (info->flags & WIDTH_FLAG && !(info->flags & MINUS_FLAG))
	{
		if (info->flags & ZERO_FLAG)
			prec = info->width - prec;
		if (info->flags & PRECISION_FLAG)
			pad_width(info, lenzero + len);
		else if (!(info->flags & ZERO_FLAG))
			pad_width(info, prec);
	}
	handle_prepend(info, signed_int);
	if (info->flags & PRECISION_FLAG)
		pad(info, lenzero, '0');
	else if (info->flags & WIDTH_FLAG && !(info->flags & MINUS_FLAG))
		if (info->flags & ZERO_FLAG)
			pad(info, prec, '0');
}
