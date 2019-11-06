/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:23:32 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/22 17:23:34 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int last_occurence;

	i = 0;
	last_occurence = -1;
	while ((*(s + i)))
	{
		if (*(s + i) == c)
			last_occurence = i;
		i += 1;
	}
	if (last_occurence > -1)
		return ((char *)(s + last_occurence));
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
