/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 13:58:58 by nmei              #+#    #+#             */
/*   Updated: 2019/11/03 16:23:31 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>

/*
**	get_signed_int_arg()
**	If we're handling ints then we need to invoke va_arg. Because dealing
**	with different size possibilities is a pain, it's easiest to promote
**	everything to the max int size type.
**
**	We have to do a slight shuffle so that L_FLAG is checked before
**	H_FLAG and HH_FLAG because the D specifier should take precedence...
*/

static intmax_t	get_signed_int_arg(t_info *info)
{
	if (info->flags & L_FLAG || info->specifier == 'D')
		return ((intmax_t)va_arg(info->args, signed long));
	else if (info->flags & HH_FLAG)
		return ((intmax_t)(signed char)va_arg(info->args, signed int));
	else if (info->flags & H_FLAG)
		return ((intmax_t)(signed short)va_arg(info->args, signed int));
	else if (info->flags & LL_FLAG)
		return ((intmax_t)va_arg(info->args, signed long long));
	else if (info->flags & J_FLAG)
		return (va_arg(info->args, intmax_t));
	else if (info->flags & Z_FLAG)
		return ((intmax_t)va_arg(info->args, ssize_t));
	else if (info->flags & T_FLAG)
		return ((intmax_t)va_arg(info->args, ptrdiff_t));
	else
		return ((intmax_t)va_arg(info->args, signed int));
}

/*
**	handle_int()
**	We have a signed int!
**	1) Get the va_arg and cast it as maxint_t.
**	2) Check if we have a negative int. We'll need to remember that!
**	3) Count the number of digits we have in our int.
**	4) If we have the "'" flag we need to calculate how many commas or periods
**	   need to be added to our nbr_len
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
	int			nbr_len;
	int			pf;

	pf = info->flags;
	info->base = 10;
	nbr = get_signed_int_arg(p);
	tmp = nbr;
	nbr_len = 0;
	info->neg = (nbr < 0) ? 1 : 0;
	while (tmp && ++nbr_len)
		tmp /= info->base;
	nbr_len += (pf & APOST_FLAG) ? ((nbr_len - 1) / 3) : 0;
	nbr_len += (nbr == 0 && !(pf & PRECISION_FLAG && info->precision == 0)) ? 1 : 0;
	if (nbr < 0 || pf & PLUS_FLAG || pf & SPACE_FLAG)
		info->width--;
	if (pf & PRECISION_FLAG)
		pf ^= ZERO_FLAG;
	handle_int_prepad(p, nbr_len, 1);
	pf_itoa_base(p, (uintmax_t)ABS(nbr), nbr_len);
	if (pf & WIDTH_FLAG && (pf & MINUS_FLAG))
		pad_width(p, MAX(info->precision, nbr_len));
}
