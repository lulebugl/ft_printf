/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 08:33:07 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 04:48:28 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_pointer_at_left(unsigned int nbr, t_struct *flag)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_hextoa(nbr)) + 2;
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
	ft_putstr("0x");
	ft_putstr(ft_hextoa(nbr));
	flag.pos += ft_strlen(ft_hextoa(nbr)) + 2;
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

static void	ft_print_pointer_at_right(unsigned int nbr, t_struct *flag)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_hextoa(nbr)) + 2;
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
	ft_putstr("0x");
	ft_putstr(ft_hextoa(nbr));
	flag.pos += ft_strlen(ft_hextoa(nbr)) + 2;
}

void		ft_print_pointer(t_struct *flag, va_list ap)
{
	unsigned int nbr;
	
	nbr = va_arg(ap, unsigned int);
	if (flag.minus)
		ft_print_pointer_at_left(nbr, flag);
	else
		ft_print_pointer_at_right(nbr, flag);
}
