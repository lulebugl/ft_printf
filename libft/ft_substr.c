/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:53:25 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 20:04:51 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*newstring;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		if (!(newstring = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
		newstring[i] = '\0';
		return (newstring);
	}
	if (!(newstring = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		newstring[i] = s[start];
		i++;
		start++;
	}
	newstring[i] = '\0';
	return (newstring);
}
