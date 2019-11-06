/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:39:40 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/20 05:41:06 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	nb_len(unsigned int nb)
{
	unsigned int	len;

	len = 0;
	while (nb /= 10)
		++len;
	return (len + 1);
}

char			*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	i;
	unsigned int	len;

	if (n < 0)
		nb = (unsigned int)(n * -1);
	else
		nb = n;
	len = nb_len(nb);
	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1 + (n < 0 ? 1 : 0)))))
		return (NULL);
	if (n < 0 && (str[i] = '-'))
		len++;
	i = len - 1;
	while (nb >= 10)
	{
		str[i--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	str[i] = (nb % 10 + 48);
	str[len] = '\0';
	return (str);
}
