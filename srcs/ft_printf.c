/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 08:15:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/24 10:56:34 by lulebugl         ###   ########.fr       */
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
	else if (c == 'x')
		return (ft_print_hex(ap));
	else if (c == 'X')
		return (ft_print_hex_cap(ap));
	else if (c == 'p')
		return (ft_print_void(ap));
	else if (c == '%')
		return (ft_putchar(c));
	return (0);
}

static int		ft_flags(va_list ap, char c, const char *s, unsigned int i)
{
	unsigned int	nbr;
	unsigned int	len;
	unsigned int	pos;
	void			*arg;
	va_list			at;

	va_copy(at, ap);
	if (!(arg = va_arg(at, void*)))
		return (0);
	if (s[i] != '\0' && s[i] == '.')
		i++;
	nbr = (unsigned int)ft_atoi(s + i);
	len = nbr;
	pos = ft_strlen(ft_utoa((unsigned int)arg));
	if (c == '0' || (c == '-' && s[i - 1] == '.'))
	{
		while ((nbr - pos) > 0)
		{
			write(1, "0", 1);
			nbr--;
		}
	}
	va_end(at);
	return (ft_strlen(ft_utoa(len)));
}

int				ft_printf(char const *s, ...)
{
	int			i;
	int			len;
	va_list		ap;

	i = 0;
	len = 0;
	va_start(ap, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			if (s[i + 1] == '0' || s[i + 1] == '-')
			{
				len += ft_flags(ap, s[i + 1], s, i + 2);
				if (s[i + 1])
					while (s && (s[i + 1] != 'd' && s[i + 1] != 'i'))
						i++;
			}
			len += ft_tab_of_print(ap, s[i + 1]);
			i++;
		}
		else if (s[i] != '%')
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(ap);
	return (len);
}

/*
**	int	main()
**	{
**		//ft_printf("my printf :\n%s\n%c\n%d\n\n", "", 'c', -2147483648);
**		//printf("printf : %s\n%c\n%d\n\n", "", 'c', -2147483648);
**		//ft_printf("my printf printunsign : %u\n\n", "544544214544");
**		//printf("printf printunsign : %u\n\n", "544544214544");
**		ft_printf("my printf : %-.123d\n\n, %0.123d\n\n", 1234567, 666);
**		printf("yr printf : %-.123d\n\n, %0.123d\n\n", 1234567, 666);
**		//ft_printf("my printf : %X\n\n", 123456789);
**		//printf("printf : %X\n\n", 123456789);
**		//ft_printf("my printf : %*p\n\n", 125, (void*)123456789);
**		//printf("printf : %*p\n\n", 125, (void*)123456789);
**		return (0);
**	}
*/
