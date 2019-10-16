/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_octal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:48:40 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 18:23:35 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_octal(va_list ap)
{
	unsigned int	nbr;
	char			*str;

	if (!(nbr = va_arg(ap, unsigned int)))
	{
		ft_putchar('0');
		return (0);
	}
	if (!(str = ft_otoa(nbr)))
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
