/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:16:02 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:16:06 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int res;
	int sign;

	i = 0;
	res = 0;
	while (ft_isspace(*(str + i)))
		i += 1;
	sign = (*(str + i) == '-') ? -1 : 1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i += 1;
	while (ft_isdigit(*(str + i)))
	{
		res = (res * 10) + ((*(str + i) - '0') * sign);
		i += 1;
	}
	return (res);
}
