/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 08:15:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 18:34:13 by lulebugl         ###   ########.fr       */
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
	else if (c == 'o')
		return (ft_print_octal(ap));
	else if (c == 'x')
		return (ft_print_hex(ap));
	else if (c == 'X')
		return (ft_print_hex_cap(ap));
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
	ft_printf("my printf :\n%s\n%c\n%d\n\n", "", 'c', -2147483648);
	printf("printf : %s\n%c\n%d\n\n", "", 'c', -2147483648);
	ft_printf("my printf printunsign : %u\n\n", "544544214544");
	printf("printf printunsign : %u\n\n", "544544214544");
	ft_printf("my printf printoctal : %o\t %o\t %o\n\n", "lop", 785421, "");
	printf("printf printoctal : %o\t %o\t %o\n\n", "lop", 785421, "");
	ft_printf("my printf : %x\n\n", 123456789);
	printf("printf : %x\n\n", 123456789);
	ft_printf("my printf : %X\n\n", 123456789);
	printf("printf : %X\n\n", 123456789);
	return (0);
}