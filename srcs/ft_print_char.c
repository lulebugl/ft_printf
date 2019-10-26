/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:45:50 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 05:02:18 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_char_at_left(unsigned char c, t_struct *flag)
{
	flag->pos+= write(1, &c, 1);
	while (flag->width > 1)
	{
		flag->pos+= write(1, " ", 1);
		flag->width--;
	}
}

static void	ft_print_char_at_right(unsigned char c, t_struct *flag)
{
	while (flag->width > 1)
	{
		if (flag->zero)
			flag->pos+= write(1, "0", 1);
		else
			flag->pos+= write(1, " ", 1);
		flag->width--;
	}
	flag->pos+= write(1, &c, 1);
}

void		ft_print_char(t_struct *flag, va_list ap)
{
	unsigned char	c;

	c = va_arg(ap, int);
	if (flag->minus)
		ft_print_char_at_left(c, flag);
	else
		ft_print_char_at_right(c, flag);
}
