/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_and_print.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 07:40:09 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/28 08:31:41 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			ft_itoa_base_and_print(uintmax_t nbr, int base, char c)
{
	int				len;
	uintmax_t		value;
	char			*conv;
	char			*str;

	len = 1;
	value = nbr;
	while (value /= base)
		len++;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	conv = (c == 'X') ?
		ft_strdup("0123456789ABCDEF") : ft_strdup("0123456789abcdef");
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = conv[nbr % base];
		nbr /= base;
	}
	len = ft_strlen(str);
	write(1, str, len);
	free(conv);
	free(str);
	return (len);
}