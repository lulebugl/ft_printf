/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:16:11 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 18:37:27 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"


// 	checker le cas ou u ----> NULL	 //


int	ft_print_unsign(va_list ap)
{
	unsigned int	nbr;
	char			*str;

	if (!(nbr = va_arg(ap, unsigned int)))
	{
		ft_putchar('0');
		return (0);
	}
	if (!(str = ft_utoa(nbr)))
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
