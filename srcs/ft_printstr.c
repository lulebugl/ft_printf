/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:08:53 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 14:21:22 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printstr(va_list ap)
{
	char	*str;

	if (!(str = va_arg(ap, char *)))
		return (0);
	ft_putstr(str);
	return (ft_strlen(str));
}
