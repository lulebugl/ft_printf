/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 08:15:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 05:32:27 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_struct	*init_struct(t_struct *flag)
{
	if (!(flag = (t_struct*)malloc(sizeof(t_struct))))
		return(NULL);
	flag->i = 0;
	flag->pos= 0;
	return (flag);
}

int				ft_printf(char const *s, ...)
{
	int			len;
	va_list		ap;
	t_struct	*flag;		
	
	flag = NULL;
	if (!(flag = init_struct(flag)))
		return(-1);
	len = 0;
	va_start(ap, s);
	if (s[0] == '%' && s[1] == '\0')
		;
	else
	{
		ft_printing(s, ap, flag);
	}
	len = flag->pos;
	va_end(ap);
	free(flag);
	return (len);
}
