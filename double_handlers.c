/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 13:56:58 by nmei              #+#    #+#             */
/*   Updated: 2019/11/03 16:23:31 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#define DABS(x) (((x) < 0.0f) ? (-x) : (x))
#define DOUBLE_UPPER(x) ((x)=='F'||(x)=='E'||(x)=='G'||(x)=='A')

/*
**	Q: How do we check if we have a valid double?
**	A: Use bit mask equivalence!
**
**	As shown in:
**	https://en.wikipedia.org/wiki/Double-precision_floating-point_format
**	bits 52-63 are where we look to check validity
**
**	luckily those addresses are well known:
**	https://www.doc.ic.ac.uk/~eedwards/compsys/float/nan.html
**
**	If we have an actual long double casting as double should preserve
**	exponent bits and chop off the mantissa so this should still work...
*/

static int			ld_isnan(long double d)
{
	union u_union	u;

	u.d = (double)(d);
	return (u.l == 0x7FF8000000000000ll || u.l == 0xFFF8000000000000ll);
}

static int			ld_isinf(long double d)
{
	union u_union	u;

	u.d = (double)(d);
	if (u.l == 0x7FF0000000000000ll)
		return (1);
	else if (u.l == 0xFFF0000000000000ll)
		return (-1);
	else
		return (0);
}

/*
**	REALLY useful general resources:
**	https://en.wikipedia.org/wiki/Double-precision_floating-point_format
**	https://en.wikipedia.org/wiki/Long_double
**	https://stackoverflow.com/a/5228616
**
**	sizeof(long double) == 16 bytes (but may use fewer...)
**	sizeof(double) == 8 bytes
**	sizeof(float) == 4 bytes
**
**	We cast everything to long double because it is convenient (and you
**	don't lose precision if you can properly parse floats+)
*/

long double			get_ld_arg(t_info *info, size_t *len, int base)
{
	long double		nbr;
	uintmax_t		tmp;

	*len = 0;
	if (info->flags & FLOAT_L_FLAG)
		nbr = va_arg(info->args, long double);
	else
		nbr = (long double)va_arg(info->args, double);
	tmp = (uintmax_t)DABS(nbr);
	if (tmp == 0)
		*len += 1;
	while (tmp && ++(*len))
		tmp /= base;
	return (nbr);
}

/*
**	handle_invalid()
**	What happenes when we get an double?
**	We figure out if it's a NAN, +INF, or -INF (also figure out upper case
**	or whether we show the + in +INF or not...)
*/

static void			handle_invalid(t_info *info, long double nbr, int inf_t)
{
	int len;

	len = ((inf_t == -1 || info->flags & PLUS_FLAG) && !ld_isnan(nbr)) ? 4 : 3;
	(info->flags & ZERO_FLAG) ? info->flags ^= ZERO_FLAG : 0;
	handle_int_prepad(p, len, 0);
	if (ld_isnan(nbr))
	{
		if (DOUBLE_UPPER(info->specifier))
			buff(p, "NAN", 3);
		else
			buff(p, "nan", 3);
	}
	else if (inf_t)
	{
		if (inf_t == -1)
			buff(p, "-", 1);
		else if (info->flags & PLUS_FLAG)
			buff(p, "+", 1);
		if (DOUBLE_UPPER(info->specifier))
			buff(p, "INF", 3);
		else
			buff(p, "inf", 3);
	}
	if (info->flags & WIDTH_FLAG && info->flags & MINUS_FLAG)
		pad_width(p, len);
}

/*
**	handle_double()
**
**	The function name is a lie! (The cake too!!!)
**
**	The basic strategy is to realize that we can separate any floating
**	point into an int part and a fraction part. (ex: 125.25 -> 125 and 25)
**	we can easily access the int part with a cast.
**
**	===========================================================================
**
**	SUPER IMPORTANT NOTE: This method has the severe flaw that it can't deal
**	with even full 'float' 'double' and 'long double' representations.
**
**	This can be tested by comparing the following with system printf:
**	#include <float.h>
**	ft_printf("testing |%f|\n", FLT_MAX);
**	ft_printf("testing |%f|\n", DBL_MAX);
**	ft_printf("testing |%Lf|\n", LDBL_MAX);
**	FLT_MAX for example is: 340282346638528859811704183484516925440
**
**	Tackling true 'float' 'double' and 'long double' would be a huge undertaking
**	See: https://stackoverflow.com/questions/1218149/
**
**	===========================================================================
**
**	1) While we get the va_arg cast as long double, also count the int
**	   component of our long double (i.e. the part before the decimal '.')
**	2) Check if our nbr is an invalid type (INF, NAN, -INF) and handle it...
**	3) 'aAfFeEgG' default to a precision of 6 (if precision isn't given
**	   or if the precision is a nonsense number)
**	4) If we do have a precision that's not 0 or we have a '#' flag we
**	   set our total nbr_len to 1 (to account for '.' char), otherwise, 0.
**	5) We need to account for ',' if we have apostrophe mode enabled
**	6) Our total double length is thus: "integer part + '.' + precision"
**	7) Do prepadding (as usual) then TIME TO CONVERT!
*/

void				handle_double(t_info *info)
{
	long double		nbr;
	size_t			int_len;
	size_t			tot_len;

	info->base = 10;
	nbr = get_ld_arg(p, &int_len, info->base);
	if (ld_isinf(nbr) || ld_isnan(nbr))
		handle_invalid(p, nbr, ld_isinf(nbr));
	else
	{
		if (!(info->flags & PRECISION_FLAG) || info->precision < 0)
			info->precision = 6;
		tot_len = (info->precision != 0 || info->flags & HASH_FLAG) ? 1 : 0;
		info->neg = (nbr < 0.0) ? 1 : 0;
		int_len += (info->flags & APOST_FLAG) ? ((int_len - 1) / 3) : 0;
		tot_len += int_len + info->precision;
		if (nbr < 0.0 || info->flags & PLUS_FLAG || info->flags & SPACE_FLAG)
			info->width--;
		handle_double_prepad(p, tot_len);
		pf_ldtoa_base(p, nbr, int_len, tot_len);
		if (info->flags & WIDTH_FLAG && info->flags & MINUS_FLAG)
			pad_width(p, tot_len);
	}
}
