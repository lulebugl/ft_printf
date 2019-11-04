/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:55:33 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 13:14:48 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/ft_printf.h"

/*
**	handle_int()
**	We have a signed int!
**	1) Get the va_arg and cast it as maxint_t.
**	2) Check if we have a negative int. We'll need to remember that!
**	3) Count the number of digits we have in our int.
**	4) If we have the "'" flag we need to calculate how many commas or periods
**	   need to be added to our nbrlen
**	5) If 'nbr == 0', then we need to make space for it.
**	   EXCEPT WHEN THE PRECISION IS 0!
**	5) If we have a negative number, a PLUS_FLAG, or SPACE_FLAG that takes up
**	   space so we'll need less width padding.
**	6) We handle the complex prepadding (see: printf_num_utils.c)
**	7) We run our itoa_base (printf version) and pass the absolute val
**	   of our number cast as an max unsigned int (that way we can reuse our
**	   itoa function for other stuff!) (see: printf_num_utils.c)
**	8) We add ' ' padding if have the MINUS_FLAG (left justified)
*/

void			handle_int(t_info *info)
{
	intmax_t	nbr;
	intmax_t	tmp;
	int			nbrlen;
	int			fg;

	fg = info->flags;
	info->base = 10;
	nbr = (intmax_t)va_arg(info->args, signed int);
	tmp = nbr;
	nbrlen = 0;
	info->neg = (nbr < 0) ? 1 : 0;
	while (tmp && ++nbrlen)
		tmp /= info->base;
	/* If 'nbr == 0', then we need to make space for it. EXCEPT WHEN THE PRECISION IS 0! */
	nbrlen += (nbr == 0 && !(fg & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (nbr < 0 || fg & PLUS_FLAG || fg & SPACE_FLAG)
		info->width--;
	if (fg & PRECISION_FLAG)
		fg ^= ZERO_FLAG;
	handle_int_prepad(info, nbrlen, 1);
	fg_itoa_base(info, (uintmax_t)ABS(nbr), nbrlen);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, MAX(info->precision, nbrlen));
}
