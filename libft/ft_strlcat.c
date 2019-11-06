/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:22:57 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:23:00 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = ft_strlen(dst);
	if (i > dstsize || !dstsize)
		return (ft_strlen(src) + dstsize);
	return (i + ft_strlcpy(dst + i, src, dstsize - i));
}
