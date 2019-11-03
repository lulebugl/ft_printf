/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 13:55:08 by nmei              #+#    #+#             */
/*   Updated: 2019/11/03 15:22:54 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <wchar.h>

/*
**	Working version
*/

void			handle_wchar(t_info *info)
{
	int		pf;
	wint_t	wc;

	pf = info->flags;
	wc = (wchar_t)va_arg(info->args, wint_t);
	if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
		pad_width(p, 1);
	pf_putwchar(p, wc);
	if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
		pad_width(p, 1);
}

/*
**	Intentionally crippled version!
**
**
**void			handle_wchar(t_info *info)
**{
**	int		pf;
**	wint_t	wc;
**
**	pf = info->flags;
**	wc = (char)va_arg(info->args, wint_t);
**	if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
**		pad_width(p, 1);
**	buff(p, &wc, 1);
**	if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
**		pad_width(p, 1);
**}
*/

/*
**	handle_char()
**	Our generic char handler, if we're dealing with wide chars (unicode) then
**	send it to the wchar handler, otherwise write out:
**	1) left padding (if applicable)
**	2) Our character
**	3) right padding (if applicable)
*/

void			handle_char(t_info *info)
{
	int		pf;
	char	c;

	pf = info->flags;
	if (pf & L_FLAG || info->specifier == 'C')
		handle_wchar(p);
	else
	{
		c = (char)va_arg(info->args, int);
		if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
			pad_width(p, 1);
		buff(p, &c, 1);
		if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
			pad_width(p, 1);
	}
}

/*
**	calc_precision()
**	Because utf-8 chars can be more than 1 'char' wide, we might have situations
**	where the precision specified has more characters than number of printable
**	utf-9 chars.
**
**	Example: ft_printf("|%15.4S|", L"我是一只猫。");
**	The precision specified is 4 but the utf char '我'' is 3 'chars' wide
**	and the '是' char cannot be printed with only 1 'char' of precision left.
**
**	Therefore use a recursive call to recalculate our precision so that the
**	precision will be trimmed to how ever many utf chars can be
**	successfully displayed.
**
**	1) If the wide str is at the end or we've exhausted our precision,
**	   return our new_prec(ision)
**	2) Otherwise if the current wide str char is 1 byte long subtract 1 from
**	   our desired precision and add one to our new_prec(ision).
**	3) Otherwise if the current wide str char is 2 bytes long and we have at
**	   least 2 more counts in our desired precision then subtract 2 from our
**	   desired precision and add 2 to our new_prec(ision).
**	4) Some more steps...
**	5) The process ends when we either have a wide char larger than 0x10FFFF
**	   or when we no longer have enough of our desired precision to hold another
**	   wide char.
*/

size_t			calc_precision(wchar_t *str, int precision, size_t new_prec)
{
	if (*str == '\0' || precision == 0)
		return (new_prec);
	else if (*str <= 0x007F)
		return (calc_precision(str + 1, precision - 1, new_prec + 1));
	else if (*str <= 0x07FF && precision >= 2)
		return (calc_precision(str + 1, precision - 2, new_prec + 2));
	else if (*str <= 0xFFFF && precision >= 3)
		return (calc_precision(str + 1, precision - 3, new_prec + 3));
	else if (*str <= 0x10FFFF && precision >= 4)
		return (calc_precision(str + 1, precision - 4, new_prec + 4));
	else
		return (new_prec);
}

/*
**	Working version!
*/

void			handle_wstr(t_info *info)
{
	int		pf;
	wchar_t	*wstr;
	int		wslen;

	pf = info->flags;
	if ((wstr = va_arg(info->args, wchar_t *)) == NULL)
		wstr = L"(null)";
	wslen = (int)pf_wstrlen(wstr);
	info->precision = (int)calc_precision(wstr, info->precision, 0);
	if (info->precision < 0)
		info->precision = wslen;
	info->precision = (info->precision > wslen) ? wslen : info->precision;
	wslen = (pf & PRECI_OB_FLAG) ? info->precision : wslen;
	if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
		pad_width(p, wslen);
	pf_putwstr(p, wstr, wslen);
	if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
		pad_width(p, wslen);
}

/*
**	Intentionally crippled version!
**
**void			handle_wstr(t_info *info)
**{
**	int		pf;
**	wchar_t	*wstr;
**	char	*str;
**	int		slen;
**
**	pf = info->flags;
**	if ((wstr = va_arg(info->args, wchar_t *)) == NULL)
**		wstr = L"(null)";
**	slen = (int)pf_wstrlen(wstr);
**	if (info->precision < 0)
**		info->precision = slen;
**	info->precision = (info->precision > slen) ? slen : info->precision;
**	slen = (pf & PRECI_OB_FLAG) ? info->precision : slen;
**	if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
**		pad_width(p, slen);
**	str = (char *)wstr;
**	pf_putwstr(p, wstr, slen);
**	if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
**		pad_width(p, slen);
**}
*/

/*
**	handle_str()
**	Our generic str handler, if we're dealing with wide strs (unicode) then
**	send it to the wstr handler which is pretty similar, otherwise:
**	1) Find our string length (slen)
**	2) Deal with precision and apply it if necessary
**	3) If we have a negative precision (whyy?) default to the string length
**	4) left padding (if applicable)
**	5) Our string
**	6) right padding (if applicable)
*/

void			handle_str(t_info *info)
{
	int			pf;
	char		*str;
	int			slen;

	pf = info->flags;
	if (pf & L_FLAG || info->specifier == 'S')
		handle_wstr(p);
	else
	{
		if ((str = va_arg(info->args, char *)) == NULL)
			str = "(null)";
		slen = (int)ft_strlen(str);
		if (info->precision < 0)
			info->precision = slen;
		info->precision = (info->precision > slen) ? slen : info->precision;
		slen = (pf & PRECI_OB_FLAG) ? info->precision : slen;
		if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
			pad_width(p, slen);
		buff(p, str, slen);
		if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
			pad_width(p, slen);
	}
}
