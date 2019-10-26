/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:21:07 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 04:57:28 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_nbr_at_left(int nbr, t_struct *flag)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_itoa(nbr));
	if (nbr == 0 && flag->precised && !flag->precision)
	{
		while (flag->width)
		{
			flag->pos += write(1, " ", 1);
			flag->width--;
		}
		return ;
	}
	while (nbrlen++ < flag->precision)
		flag->pos += write(1, "0", 1);
	ft_putnbr(nbr);
	flag->pos += ft_strlen(ft_itoa(nbr));
	while (flag->width >= nbrlen)
	{
		flag->pos += write(1, " ", 1);
		flag->width--;
	}
}

static void	ft_padding(int nbrlen, t_struct *flag)
{
	if (!flag->precised)
		while (flag->width-- > nbrlen)
		{
			if (flag->zero)
				flag->pos += write(1, "0", 1);
			else
				flag->pos += write(1, " ", 1);
		}
	else
	{
		while (flag->width-- > flag->precision)
		{
			if ((flag->zero && flag->width != flag->precision))
				flag->pos += write(1, "0", 1);
			else
				flag->pos += write(1, " ", 1);
		}
	}
}

static void	ft_print_nbr_at_right(int nbr, t_struct *flag)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_itoa(nbr));
	if (nbr == 0 && flag->precised && !flag->precision)
	{
		while (flag->width)
		{
			flag->pos += write(1, " ", 1);
			flag->width--;
		}
		return ;
	}
	ft_padding(nbrlen, flag);
	flag->precision = (flag->width > flag->precision) ? flag->width : flag->precision;
	while (nbrlen++ < flag->precision)
		flag->pos += write(1, "0", 1);
	ft_putnbr(nbr);
	flag->pos += ft_strlen(ft_itoa(nbr));
}

void		ft_print_nbr(t_struct *flag, va_list ap)
{
	int nbr;

	nbr = va_arg(ap, int);
	if (flag->minus)
		ft_print_nbr_at_left(nbr, flag);
	else
		ft_print_nbr_at_right(nbr, flag);
	}
}
