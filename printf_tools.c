/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:56:29 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/17 20:42:04 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "ft_printf.h"

void	print_buffer(t_pfinfo *info)
{
	write(info->fd, info->buf, info->buf_len);
	info->buf_len = 0;
}

void	buff(t_pfinfo *info, const void *s, size_t n)
{
	unsigned char	*str;
	size_t			remain;

	str = (unsigned char *)s;
	while (info->buf_len + n > BUFF_SIZE)
	{
		remain = BUFF_SIZE - info->buf_len;
		while (remain-- && n--)
		{
			info->buf[info->buf_len++] = *str++;
			info->len++;
		}
		print_buffer(info);
	}
	while (n--)
	{
		info->buf[info->buf_len++] = *str++;
		info->len++;
	}
}

void	pad(t_pfinfo *info, int pad_len, char c)
{
	char	*pad_str;

	pad_str = NULL;
	if (pad_len > 0)
	{
		if ((pad_str = (char *)malloc(pad_len + 1)) != NULL)
		{
			pad_str[pad_len] = '\0';
			ft_memset(pad_str, c, (size_t)pad_len);
			buff(info, pad_str, pad_len);
			free(pad_str);
		}
	}
}

void	pad_width(t_pfinfo *info, int arg_width)
{
	int pad_width;

	pad_width = info->width - arg_width;
	if ((info->flags & PRECISION_FLAG) &&
		(info->flags & ZERO_FLAG) && (info->precision < 0))
		pad(info, pad_width, '0');
	else
		pad(info, pad_width, ' ');
}

void	reset_printf(t_pfinfo *info)
{
	info->flags = 0;
	info->width = 0;
	info->precision = 0;
	info->base = 0;
	info->neg = 0;
	info->hex_int = 0;
	info->arg_type = '\0';
}
