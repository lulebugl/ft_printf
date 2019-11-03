/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 12:15:51 by nmei              #+#    #+#             */
/*   Updated: 2019/11/03 16:23:31 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>
#define UPPER(x) ((x)=='X'||(x)=='F'||(x)=='E'||(x)=='G'||(x)=='A')
#define HEX(x) ((x)=='x'||(x)=='X'||(x)=='p'||(x)=='a'||(x)=='A')

/*
**	pf_itoa_base()
**	unsigned long long max is: 18,446,744,073,709,551,615 (26 chars + 1 '\0')
**	So a buffer of 27 chars is the biggest we ever have to consider.
**
**	Because '+'/'-'/' ' are handled in the handle_prepad() function we don't
**	need to worry about them and just focus on the numbers.
*/

void			pf_itoa_base(t_info *info, uintmax_t nbr, int nbr_len)
{
	char	res[27];
	int		tmp_len;
	int		len_diff;
	int		base;
	char	char_case;

	base = info->base;
	char_case = ('a' - 10 - (('a' - 'A') * UPPER(info->specifier)));
	tmp_len = nbr_len;
	while (tmp_len--)
	{
		len_diff = nbr_len - tmp_len;
		if (info->flags & APOST_FLAG && len_diff % 4 == 0 && len_diff > 0)
			res[tmp_len] = ',';
		else
		{
			res[tmp_len] = (nbr % base) + ((nbr % base < 10) ? '0' : char_case);
			nbr /= base;
		}
	}
	buff(p, res, nbr_len);
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

	spec = info->specifier;
	if (info->neg)
		buff(p, "-", 1);
	else if (info->flags & PLUS_FLAG && signed_int)
		buff(p, "+", 1);
	else if (info->flags & SPACE_FLAG && signed_int)
		buff(p, " ", 1);
	if (info->flags & HASH_FLAG && HEX(spec) && ((info->hex_int != 0) || spec == 'p'))
		(UPPER(spec)) ? buff(p, "0X", 2) : buff(p, "0x", 2);
}

/*
**	handle_prepad()
**	This one is a doozy... Need to prevent interactions between wp_len
**	and zp_len because in certain situations width also needs to do 0 padding.
**	1) Effective nbr length will be the max of 'nbr_len' vs. 'info->precision'
**	   i.e. ("%6.5d", 1)  our width padding is 6 - 5 = 1
**			("%6.1d", 1)  our width padding is 6 - 1 = 5
**			("%6.1d", 20) our width padding is 6 - 2 = 4
**	2) 'zp_len' (number of zeros to pad) will be:
**     precision - nbr_len if precision > 'nbr_len'
**	   'zp_len' WILL NOT BE USED IN ANY WAY IF WE DON'T HAVE PRECISION_FLAG
**	3) If we have a width and we are right justified
**	   a) If we have a ZERO_FLAG, calculate a tentative width pad that we will
**		  use if we don't encounter a PRECISION_FLAG (after writing out signs)
**	   b) If we have a PRECISION_FLAG then our width pad will be the total
**		  effective nbr length calculated in 1). We don't use wp_len because it
**		  may have been modified in step 3a)
**	   c) If we don't have a precision and we don't have a ZERO_FLAG then just
**		  pad normally
**	4) Handle prepend of our number
**	5) If we have a PRECISION_FLAG then write out our calculated zp_len
**	6) If we DON'T have a PRECISION_FLAG but we have a width, are right
**	   justified, and have a ZERO_FLAG then we write out zeros according to the
**	   wp_len.
*/

void			handle_int_prepad(t_info *info, int nbr_len, int signed_int)
{
	int		zp_len;
	int		wp_len;

	wp_len = (info->flags & PRECISION_FLAG) ? MAX(info->precision, nbr_len) : nbr_len;
	zp_len = (info->precision > nbr_len) ? info->precision - nbr_len : 0;
	if (info->flags & WIDTH_FLAG && !(info->flags & MINUS_FLAG))
	{
		if (info->flags & ZERO_FLAG)
			wp_len = info->width - wp_len;
		if (info->flags & PRECISION_FLAG)
			pad_width(p, zp_len + nbr_len);
		else if (!(info->flags & ZERO_FLAG))
			pad_width(p, wp_len);
	}
	handle_prepend(p, signed_int);
	if (info->flags & PRECISION_FLAG)
		pad(p, zp_len, '0');
	else if (info->flags & WIDTH_FLAG && !(info->flags & MINUS_FLAG))
		if (info->flags & ZERO_FLAG)
			pad(p, wp_len, '0');
}
