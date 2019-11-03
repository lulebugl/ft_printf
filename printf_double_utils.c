/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_double_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:30:27 by nmei              #+#    #+#             */
/*   Updated: 2019/11/03 15:22:54 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>
#define UPPER(x) ((x)=='X'||(x)=='F'||(x)=='E'||(x)=='G'||(x)=='A')
#define HEX(x) ((x)=='x'||(x)=='X'||(x)=='p'||(x)=='a'||(x)=='A')
#define DABS(x) (((x) < 0.0f) ? (-x) : (x))

/*
**	ft_pw()
**	Recursive power function.
**	We can take a shortcut if our power is even!
**
**	Because everything is unsigned if we overflow we just get wrap around
**	(nonsensical) results (I'm okay with that...)
*/

uintmax_t		ft_pw(uintmax_t nb, uintmax_t power)
{
	uintmax_t i;

	if (power == 0)
		return (1);
	if (power % 2 == 0)
	{
		i = ft_pw(nb, power / 2);
		return (i * i);
	}
	else
		return (nb * ft_pw(nb, power - 1));
}

/*
**	pf_ldtoa_int_base()
**	function to convert either integer part or fraction part of the
**	floating point number we'd like to convert.
*/

void			pf_ldtoa_int_base(t_info *info, uintmax_t nbr, size_t int_len,
									char res[59])
{
	char		char_case;
	int			base;
	size_t		tmp_len;
	size_t		len_diff;

	base = info->base;
	char_case = ('a' - 10 - (('a' - 'A') * UPPER(info->specifier)));
	tmp_len = int_len;
	while (tmp_len--)
	{
		if (info->flags & LDTOA_FRAC && info->precision-- == 0)
			break ;
		len_diff = int_len - tmp_len;
		if (info->flags & APOST_FLAG && len_diff % 4 == 0 && len_diff > 0)
			res[tmp_len] = ',';
		else
		{
			res[tmp_len] = (nbr % base) + ((nbr % base < 10) ? '0' : char_case);
			nbr /= base;
		}
	}
}

/*
**	pf_ldtoa_base() - Just like pf_itoa_base, but for long doubles!
**
**	Why have such a huge result array? try:
**	#include <float.h> and
**	ft_printf("testing |%f|\n", FLT_MAX);
**
**	FLT_MAX is: 340282346638528859811704183484516925440.0
**
**	Recall number of separators is: (nbr_len - 1) / 3
**	so (39 - 1) / 3 = 12
**
**	Theoretical max number of chars we should have to deal with:
**	39 (+ 12) + '.' + 6 + '\0' = 59
**
**	1) Convert the int portion of our floating point nbr to ascii
**	2) Set our fraction flag (fraction flag stop printing fraction part of
**	   float when the specified precision is reached)
**	3) We need to temporarily increase our precision (so we return the right
**	   rounded value with the given significance we want)
**	4) To get the fraction part of our number we can just subtract from it the
**	   'int' part. (i.e. 125.25 - 125 = 0.25). We then multiply with our
**		increased significance to get an int AND with that extra digit.
**	5) We then assess if the extra digit we got is larger or smaller than
**	   half the base we are using. If it's >= base/2 round up.
**	6) Write our fraction part int our 'res' temp buffer
**	7) Write our decimal point '.' if necessary
**	8) Add the converted float to our overall buffer.
*/

void			pf_ldtoa_base(t_info *info, long double nbr, size_t int_len,
							size_t tot_len)
{
	char		res[59];
	long double	frac;
	int			base;

	base = info->base;
	pf_ldtoa_int_base(p, (uintmax_t)DABS(nbr), int_len, res);
	info->flags |= LDTOA_FRAC;
	if (info->precision != 0)
	{
		if (info->flags & APOST_FLAG)
			info->flags ^= APOST_FLAG;
		info->precision++;
		frac = (DABS(nbr) - (uintmax_t)DABS(nbr)) * ft_pw(base, info->precision);
		frac = ((uintmax_t)DABS(frac) % base >= (uintmax_t)(base / 2)) ?
			(frac / base) + 1 : frac / base;
		pf_ldtoa_int_base(p, (uintmax_t)DABS(frac), tot_len, res);
	}
	if (info->precision != 0 || info->flags & HASH_FLAG)
		res[int_len] = '.';
	buff(p, res, tot_len);
}

/*
**	handle_double_prepad() && handle_double_prepend()
**
**	Currently, exact copies of the int/uint versions. This is okay for normal
**	floats but hex floats and sci floats may require substantial changes to get
**	working. Having this modularity will allow for easier changes to be made
**	without have to worry about propagation effects...
*/

static void		handle_double_prepend(t_info *info)
{
	int	spec;

	spec = info->specifier;
	if (info->neg)
		buff(p, "-", 1);
	else if (info->flags & PLUS_FLAG)
		buff(p, "+", 1);
	else if (info->flags & SPACE_FLAG)
		buff(p, " ", 1);
	if (info->flags & HASH_FLAG && HEX(spec))
		(UPPER(spec)) ? buff(p, "0X", 2) : buff(p, "0x", 2);
}

void			handle_double_prepad(t_info *info, int nbr_len)
{
	int		zp_len;
	int		wp_len;

	wp_len = (info->flags & PRECI_OB_FLAG) ? MAX(info->precision, nbr_len) : nbr_len;
	zp_len = (info->precision > nbr_len) ? info->precision - nbr_len : 0;
	if (info->flags & WIDTH_OB_FLAG && !(info->flags & DASH_FLAG))
	{
		if (info->flags & ZERO_FLAG)
			wp_len = info->width - wp_len;
		if (info->flags & PRECI_OB_FLAG)
			pad_width(p, zp_len + nbr_len);
		else if (!(info->flags & ZERO_FLAG))
			pad_width(p, wp_len);
	}
	handle_double_prepend(p);
	if (info->flags & PRECI_OB_FLAG)
		pad(p, zp_len, '0');
	else if (info->flags & WIDTH_OB_FLAG && !(info->flags & DASH_FLAG))
		if (info->flags & ZERO_FLAG)
			pad(p, wp_len, '0');
}
