/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 04:23:33 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 05:00:23 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_percent_at_left(t_struct *flag)
{
	flag->pos+= write(1, "%", 1);
	while (flag->width > 1)
	{
		flag->pos += write(1, " ", 1);
		flag->width--;
	}
}

static void	ft_print_percent_at_right(t_struct *flag)
{
	while (flag->width > 1)
	{
		if (flag->zero)
			flag->pos += write(1, "0", 1);
		else
			flag->pos += write(1, " ", 1);
		flag->width--;
	}
	flag->pos+= write(1, "%", 1);
}

void		ft_print_percent(t_struct *flag)
{
	if (flag->minus)
		ft_print_percent_at_left(flag);
	else
		ft_print_percent_at_right(flag);
}