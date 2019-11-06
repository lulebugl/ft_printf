/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:22:25 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:22:27 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*p_dst;
	char	*p_src;

	if (!dst && !src)
		return (NULL);
	i = 0;
	p_dst = (char *)dst;
	p_src = (char *)src;
	while (i < n)
	{
		*(p_dst + i) = *(p_src + i);
		i += 1;
	}
	return (dst);
}
