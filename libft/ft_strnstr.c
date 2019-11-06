/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:23:26 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 18:50:23 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *needle, size_t len)
{
	size_t i;
	size_t d_len;

	if (!(d_len = ft_strlen(needle)))
		return (char *)s1;
	i = 0;
	while (*(s1 + i) && len - i >= d_len && i < len)
	{
		if (!ft_memcmp(s1 + i, needle, d_len))
			return ((char *)s1 + i);
		i += 1;
	}
	return (NULL);
}
