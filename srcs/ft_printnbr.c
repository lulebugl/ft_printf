/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:21:07 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 14:21:18 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printnbr(va_list ap)
{
	int		nbr;

	nbr = va_arg(ap, int);
	ft_putnbr(nbr);
	return(ft_strlen(ft_itoa(nbr)));
}