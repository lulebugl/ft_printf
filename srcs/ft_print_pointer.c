/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 08:33:07 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/28 08:37:45 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_pointer_at_left(uintmax_t nbr, t_struct *flag)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_itoa_base(nbr, 16, 0)) + 2;
	flag->pos += write(1, "0x", 2);
	if (nbr == 0 && flag->precised && !flag->precision)
		return ;
	while (flag->precision > (nbrlen - 2))
	{
		flag->pos += write(1, "0", 1);
		flag->precision--;
	}
	flag->pos += ft_itoa_base_and_print(nbr, 16, 0);
	while (flag->width > nbrlen)
	{
		flag->pos += write(1, " ", 1);
		flag->width--;
	}
}

static void	ft_print_pointer_at_right(uintmax_t nbr, t_struct *flag)
{
	int nbrlen;

	nbrlen = ft_strlen(ft_itoa_base(nbr, 16, 0)) + 2;
	while (flag->width > nbrlen)
	{
		flag->pos += write(1, " ", 1);
		flag->width--;
	}
	flag->pos += write(1, "0x", 2);
	if (nbr == 0 && flag->precised && !flag->precision)
		return ;
	while ((nbrlen - 2) < flag->precision)
	{
		flag->pos += write(1, "0", 1);
		nbrlen++;
	}
	flag->pos += ft_itoa_base_and_print(nbr, 16, 0);
}

void		ft_print_pointer(t_struct *flag, va_list ap)
{
	uintmax_t nbr;
	
	nbr = (long long)va_arg(ap, void*);
	if (flag->minus)
		ft_print_pointer_at_left(nbr, flag);
	else
		ft_print_pointer_at_right(nbr, flag);
}
