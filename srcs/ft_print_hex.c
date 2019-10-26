/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:23:51 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 03:57:04 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_and_left_align(unsigned int nbr, t_struct *flag, char c)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_hextoa(nbr));
	if (nbr == 0 && flag.precised && !flag.precision)
	{
		while (flag.width)
		{
			flag.pos += write(1, " ", 1);
			flag.width--;
		}
		return ;
	}
	while (nbrlen++ < flag.precision)
		flag.pos += write(1, "0", 1);
	(c == 'x') ? ft_putstr(ft_hextoa(nbr)) : ft_putstr(ft_hexcaptoa(nbr));
	flag.pos += ft_strlen(ft_hextoa(nbr));
	while (flag.width >= nbrlen)
	{
		flag.pos += write(1, " ", 1);
		flag.width--;
	}
}

static void	ft_padding(int nbrlen, t_struct *flag)
{
	if (!flag.precised)
		while (flag.width-- > nbrlen)
		{
			if (flag.zero)
				flag.pos += write(1, "0", 1);
			else
				flag.pos += write(1, " ", 1);
		}
	else
	{
		if (flag.zero)
			flag.width--;
		while (flag.width-- > nbrlen)
		{
			if (flag.zero)
				flag.pos += write(1, "0", 1);
			else
				flag.len += write(1, " ", 1);
		}
	}
}

static void	ft_print_and_right_align(unsigned int nbr, t_struct *flag, char c)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_hextoa(nbr));
	if (nbr == 0 && flag.precised && !flag.precision)
	{
		while (flag.width)
		{
			flag.pos += write(1, " ", 1);
			flag.width--;
		}
		return ;
	}
	ft_padding(nbrlen, flag);
	while (nbrlen++ < flag.precision)
		flag.pos += write(1, "0", 1);
	(c == 'x') ? ft_putstr(ft_hextoa(nbr)) : ft_putstr(ft_hexcaptoa(nbr));
	flag.pos += ft_strlen(ft_hextoa(nbr));
}

void		ft_print_hex(char c, t_struct *flag, va_list ap)
{
	unsigned int nbr;

	if (c == 'x' || c == 'X')
	{
		nbr = va_arg(ap, unsigned int);
		if (flag.minus)
			ft_print_and_left_align(nbr, flag, c);
		else
			ft_print_hex_right_align(nbr, flag, c);
	}
}