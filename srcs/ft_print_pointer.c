/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_void.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 08:33:07 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/24 10:44:13 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_void(va_list ap)
{
	char			*arg;
	unsigned long	c;

	ft_putstr("0x");
	c = va_arg(ap, unsigned long);
	arg = ft_hextoa(c);
	ft_putstr(arg);
	return (ft_strlen(arg) + 2);
}
