/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:35:16 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/27 18:42:16 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_unsigned(unsigned int nb)
{
	size_t	len;

	len = 0;
	if (nb > 9)
	{
		len += print_unsigned((nb / 10));
		len += print_unsigned((nb % 10));
	}
	else
	{
		ft_putchar_fd(nb + 48, 1);
		len++;
	}
	return (len);
}

size_t	print_hex(unsigned long long n, char *base)
{
	size_t	len;

	len = 0;
	if (n > 15)
	{
		len += print_hex(n / 16, base);
		len += print_hex(n % 16, base);
	}
	else
	{
		ft_putchar_fd(base[n], 1);
		len++;
	}
	return (len);
}

size_t	print_pointer(unsigned long long p)
{
	size_t	len;

	len = 0;
	if (!p)
		return (write(1, "(nil)", 5), 5);
	write(1, "0x", 2);
	len += print_hex(p, "0123456789abcdef");
	return (len + 2);
}
