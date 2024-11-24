/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:34:45 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/27 18:42:32 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_arg(va_list args, char c)
{
	if (!c)
		return (0);
	if (c == '%')
		return (ft_putchar_fd('%', 1), 1);
	else if (c == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1), 1);
	else if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (c == 'd')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (c == 'u')
		return (print_unsigned(va_arg(args, unsigned int)));
	else if (c == 'p')
		return (print_pointer(va_arg(args, unsigned long long)));
	else if (c == 'x')
		return (print_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (print_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			len += print_arg(args, *(format + 1));
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			len++;
		}
		format++;
	}
	va_end(args);
	return (len);
}
