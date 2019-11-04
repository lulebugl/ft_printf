/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:49:14 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 17:59:43 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "includes/ft_printf.h"

void	parse_format(t_info *info)
{
	t_convtable		handler_funct;
	const char		*str;

	str = info->f;
	if (info->f++ != '\0')
	{
		info->cpy_str = info->f;
		parse_flags(info);
		parse_width(info);
		parse_precision(info, 0);
		info->arg_type = *info->f;
		if ((handler_funct = get_funct(info->arg_type)) == NULL)
			info->flags |= INVALID;
		else if (!(info->flags & INVALID))
		{
			handler_funct(info);
			info->f++;
		}
	}
	info->cpy_str = (info->flags & INVALID) ? str : info->f;
}

int		ft_vfprintf(int fd, const char *format, va_list args)
{
	t_info	info;

	ft_bzero(&info, sizeof(info));
	va_copy(info.args, args);
	info.fd = fd;
	info.f = format;
	info.cpy_str = info.f;
	while (*info.f)
	{
		if (*info.f != '%')
			info.f++;
		else
		{
			buff(&info, info.cpy_str, info.f - info.cpy_str);
			parse_format(&info);
			reset_printf(&info);
		}
	}
	buff(&info, info.cpy_str, info.f - info.cpy_str);
	print_buffer(&info);
	va_end(info.args);
	return (info.len);
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (format)
	{
		va_start(args, format);
		len = ft_vfprintf(1, format, args);
		va_end(args);
	}
	return (len);
}
