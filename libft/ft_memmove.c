/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:22:32 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:22:34 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (len && !dst && !src)
		return (NULL);
	if ((char *)dst < (char *)src)
		ft_memcpy(dst, src, len);
	else
	{
		i = 0;
		while (i < len)
		{
			*((char *)(dst + len - (i + 1))) = *((char *)(src + len - (i + 1)));
			i += 1;
		}
	}
	return (dst);
}
