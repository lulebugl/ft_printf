/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:45 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/17 20:42:04 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_printf.h"

void	handle_char(t_pfinfo *info)
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

void	handle_str(t_pfinfo *info)
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
