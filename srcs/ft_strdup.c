/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 07:58:21 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/28 07:59:06 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*cpy;

	i = 0;
	len = ft_strlen(s1);
	if (!(cpy = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	return (ft_strcpy(cpy, s1));
}
