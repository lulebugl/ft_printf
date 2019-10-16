/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:23:51 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 18:28:46 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_hex(va_list ap)
{
	unsigned int	nbr;
	char			*str;

	if (!(nbr = va_arg(ap, unsigned int)))
	{
		ft_putchar('0');
		return (0);
	}
	if (!(str = ft_hextoa(nbr)))
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
