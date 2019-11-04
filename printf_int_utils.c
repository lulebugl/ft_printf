/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:20:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 13:13:56 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/ft_printf.h"
#define UPPER(x) ((x)=='X')
#define HEX(x) ((x)=='x'||(x)=='X'||(x)=='p')

/*
**	fg_itoa_base()
**	unsigned long long max is: 18,446,744,073,709,551,615 (26 chars + 1 '\0')
**	So a buffer of 27 chars is the biggest we ever have to consider.
**
**	Because '+'/'-'/' ' are handled in the handle_prepad() function we don't
**	need to worry about them and just focus on the numbers.
*/

void			fg_itoa_base(t_info *info, uintmax_t nbr, int nbrlen)
{
	char	res[27];
	int		tmp_len;
	int		len_diff;
	int		base;
	char	char_case;

	base = info->base;
	char_case = ('a' - 10 - (('a' - 'A') * UPPER(info->arg_type)));
	tmp_len = nbrlen;
	while (tmp_len--)
	{
		len_diff = nbrlen - tmp_len;
		res[tmp_len] = (nbr % base) + ((nbr % base < 10) ? '0' : char_case);
		nbr /= base;
	}
	buff(info, res, nbrlen);
}

/*
**	handle_prepend()
**	Write out "-"/"+"/" " " as necessary.
**	NOTE: "-" takes precedence over "+" which both take precedence over " "
**	NOTE2: "-"/"+"/" " are ignored for unsigned ints
*/

static void		handle_prepend(t_info *info, int signed_int)
{
	int	spec;

	spec = info->arg_type;
	if (info->neg)
		buff(info, "-", 1);
	else if (info->flags & PLUS_FLAG && signed_int)
		buff(info, "+", 1);
	else if (info->flags & SPACE_FLAG && signed_int)
		buff(info, " ", 1);
	if (info->flags & HASH_FLAG && HEX(spec) && ((info->hex_int != 0) || spec == 'p'))
		(UPPER(spec)) ? buff(info, "0X", 2) : buff(info, "0x", 2);
}

/*
**	handle_prepad()
**	This one is a doozy... Need to prevent interactions between wp_len
**	and lenzero because in certain situations width also needs to do 0 padding.
**	1) Effective nbr length will be the max of 'nbrlen' vs. 'info->precision'
**	   i.e. ("%6.5d", 1)  our width padding is 6 - 5 = 1
**			("%6.1d", 1)  our width padding is 6 - 1 = 5
**			("%6.1d", 20) our width padding is 6 - 2 = 4
**	2) 'lenzero' (number of zeros to pad) will be:
**     precision - nbrlen if precision > 'nbrlen'
**	   'lenzero' WILL NOT BE USED IN ANY WAY IF WE DON'T HAVE PRECISION_FLAG
**	3) If we have a width and we are right justified
**	   a) If we have a ZERO_FLAG, calculate a tentative width pad that we will
**		  use if we don't encounter a PRECISION_FLAG (after writing out signs)
**	   b) If we have a PRECISION_FLAG then our width pad will be the total
**		  effective nbr length calculated in 1). We don't use wp_len because it
**		  may have been modified in step 3a)
**	   c) If we don't have a precision and we don't have a ZERO_FLAG then just
**		  pad normally
**	4) Handle prepend of our number
**	5) If we have a PRECISION_FLAG then write out our calculated lenzero
**	6) If we DON'T have a PRECISION_FLAG but we have a width, are right
**	   justified, and have a ZERO_FLAG then we write out zeros according to the
**	   wp_len.
*/

void			handle_int_prepad(t_info *info, int nbrlen, int signed_int)
{
	int		lenzero;
	int		wp_len;

	wp_len = (info->flags & PRECISION_FLAG) ? MAX(info->precision, nbrlen) : nbrlen;
	lenzero = (info->precision > nbrlen) ? info->precision - nbrlen : 0;
	if (info->flags & WIDTH_FLAG && !(info->flags & MINUS_FLAG))
	{
		if (info->flags & ZERO_FLAG)
			wp_len = info->width - wp_len;
		if (info->flags & PRECISION_FLAG)
			pad_width(info, lenzero + nbrlen);
		else if (!(info->flags & ZERO_FLAG))
			pad_width(info, wp_len);
	}
	handle_prepend(info, signed_int);
	if (info->flags & PRECISION_FLAG)
		pad(info, lenzero, '0');
	else if (info->flags & WIDTH_FLAG && !(info->flags & MINUS_FLAG))
		if (info->flags & ZERO_FLAG)
			pad(info, wp_len, '0');
}
