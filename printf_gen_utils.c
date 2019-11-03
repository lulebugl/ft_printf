/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_gen_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:56:29 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/03 15:35:34 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>

void	flush_buffer(t_info *info)
{
	write(info->fd, info->buf, info->buf_len);
	info->buf_len = 0;
}

/*
**	buff()
**	We will buffer our printf to avoid the overhead of multiple 'write(2)' calls
**	Written to closely mirror the arguments of 'write(2)' so we can just do a
**	simple replace.
**
**	1) cast our void *s as an unsigned char
**	2) While our current buf_len and the n we'd like to write are bigger
**	   than our BUFF_SIZE
**	   a) We calculate the remaining space in our buffer
**	   b) We fill the buffer to the brim (and decrement n for each fill)
**	   c) We flush the buffer
**  3) Buffer any left over n now that we know that 'info->buf_len + n'
**	   will fit in our buffer.
*/

void	buff(t_info *info, const void *s, size_t n)
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
		flush_buffer(info);
	}
	while (n--)
	{
		info->buf[info->buf_len++] = *str++;
		info->len++;
	}
}

/*
**	pad()
**	General function that generates a character string of pad_len consisting
**	of the 'pad_char's which then gets sent to the buffer.
*/

void	pad(t_info *info, int pad_len, char pad_char)
{
	char	*infoad_str;

	pad_str = NULL;
	if (pad_len > 0)
	{
		if ((pad_str = (char *)malloc(pad_len + 1)) != NULL)
		{
			pad_str[pad_len] = '\0';
			ft_memset(pad_str, pad_char, (size_t)pad_len);
			buff(info, pad_str, pad_len);
			free(pad_str);
		}
	}
}

/*
**	pad_width()
**	Function to calculate padding that should be added for given specified
**	width and for given argument width. Strictly only pads spaces thus specific
**	for the width prespecifier.
*/

void	pad_width(t_info *info, int arg_width)
{
	int final_pad_width;

	final_pad_width = info->width - arg_width;
	pad(info, final_pad_width, ' ');
}

void	reset_printf(t_info *info)
{
	info->flags = 0;
	info->width = 0;
	info->precision = 0;
	info->base = 0;
	info->neg = 0;
	info->hex_int = 0;
	info->specifier = '\0';
}
