/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 08:15:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 15:39:04 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_tab_of_print(va_list ap, char c)
{
	if (c == 'c')
		return (ft_printchar(ap));
	else if (c == 's')
		return (ft_printstr(ap));
	else if (c == 'd' || c == 'i')
		return (ft_printnbr(ap));
	else if (c == 'u')
		return (ft_print_unsign(ap));
	//else if (c == 'o')
	//	return (ft_printoctal(ap));
	//else if (c == 'x')
	//	return (ft_printhexa(ap));
	//else if (c == 'X')
	//	return (ft_printhexa_cap(ap));
	//else if (c == 'p')
	//	return (ft_printvoid(ap));
	//else if (c == '%')
	//	return (ft_putchar(c));
	return (0);
}

int				ft_printf(char const *format, ...)
{
	int			i;
	int			len;
	va_list		ap;

	i = 0;
	len = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			len += ft_tab_of_print(ap, format[i + 1]);
			i++;
		}
		else if (format[i] != '%')
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (len);
}

int	main()
{
	ft_printf("test : %s\n%c\n%d\n", "", 'c', -2147483648);
	ft_printf("test utoa : %u", NULL);
	return (0);
}