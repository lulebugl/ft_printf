/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:22:06 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:22:08 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	i = 0;
	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	while (i < n)
	{
		*(p_dst + i) = *(p_src + i);
		if (*(p_src + i) == (unsigned char)c)
			return (p_dst + i + 1);
		i += 1;
	}
	if (*(p_src + i) == (unsigned char)c)
		return (p_src + i + 1);
	return (NULL);
}
