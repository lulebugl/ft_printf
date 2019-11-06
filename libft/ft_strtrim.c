/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:23:38 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 18:25:44 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calc_border(const char c, const char *s)
{
	while (*s)
		if (c == *s++)
			return (1);
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_calc_border(*(s1 + start), set))
		start += 1;
	if (!*(s1 + start))
		return (ft_calloc(1, 1));
	end = ft_strlen(s1) - 1;
	while (ft_calc_border(*(s1 + end), set))
		end -= 1;
	return (ft_substr(s1, start, end - start + 1));
}
