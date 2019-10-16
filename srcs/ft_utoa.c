/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:51:48 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 14:21:44 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_utoa(unsigned int n)
{
	int				len;
	char			*str;
	unsigned int	nbr;

	nbr = n;
	len = 0;
	while (nbr /= 10)
		len++;
	if (!(str = (char*)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = n % 10 + 48;
		n /= 10;
		len--;
	}
	return (str);
}
