/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:22:44 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:22:45 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while ((*(s + i)))
	{
		if (*(s + i) == (char)c)
			return (char *)(s + i);
		i += 1;
	}
	if (c == '\0')
		return (char *)(s + i);
	return (NULL);
}
