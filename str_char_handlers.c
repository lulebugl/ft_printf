/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:45 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 13:33:54 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/ft_printf.h"

/*
**	Working version
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
	int		fg;
	char	c;

	fg = info->flags;
	c = (char)va_arg(info->args, int);
	if (fg & WIDTH_FLAG && !(fg & MINUS_FLAG))
		pad_width(info, 1);
	buff(info, &c, 1);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, 1);
}

/*
**	Working version!
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
	int			fg;
	char		*str;
	int			slen;

	fg = info->flags;
	if ((str = va_arg(info->args, char *)) == NULL)
		str = "(null)";
	slen = (int)ft_strlen(str);
	if (info->precision < 0)
		info->precision = slen;
	info->precision = (info->precision > slen) ? slen : info->precision;
	slen = (fg & PRECISION_FLAG) ? info->precision : slen;
	if (fg & WIDTH_FLAG && !(fg & MINUS_FLAG))
		pad_width(info, slen);
	buff(info, str, slen);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, slen);
}
