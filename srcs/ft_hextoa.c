/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:04:25 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 18:38:25 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_hextoa(unsigned int n)
{
	char				*str;
	int					len;
	unsigned int		nbr;

	nbr = n;
	len = 0;
	while (nbr /= 16)
		len++;
	if (!(str = (char*)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	str[len + 1] = '\0';
	while (len > 0)
	{
		if ((n % 16 > 9) && (n % 16 < 16))
			str[len] = n % 16 + 87;
		else if (n % 16 <= 9)
			str[len] = n % 16 + 48;
		len--;
		n /= 16;
	}
	if ((n % 16 > 9) && (n % 16 < 16))
		str[len] = n % 16 + 87;
	else if (n % 16 <= 9)
		str[len] = n % 16 + 48;
	return (str);
}
