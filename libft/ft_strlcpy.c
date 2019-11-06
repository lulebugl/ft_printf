/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:23:02 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:23:05 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t len;

	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	len = (src_len < dstsize - 1) ? src_len : dstsize - 1;
	ft_memcpy(dst, src, len);
	*(dst + len) = '\0';
	return (src_len);
}
