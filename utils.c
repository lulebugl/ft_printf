/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:03:34 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/27 18:20:19 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*(s + size))
		size++;
	return (size);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

size_t	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	else
		write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}

size_t	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	size_t	len;

	nb = n;
	len = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		len++;
		nb = -nb;
	}
	if (nb > 9)
	{
		len += ft_putnbr_fd((nb / 10), fd);
		len += ft_putnbr_fd((nb % 10), fd);
	}
	else
	{
		ft_putchar_fd(nb + 48, fd);
		len++;
	}
	return (len);
}
