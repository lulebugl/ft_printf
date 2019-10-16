/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:46:34 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 18:23:00 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_otoa(unsigned int n)
{
	int				len;
	char			*str;
	unsigned int	nbr;

	nbr = n;
	len = 0;
	while (nbr /= 8)
		len++;
	if (!(str = (char*)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = n % 8 + 48;
		n /= 8;
		len--;
	}
	return (str);
}
