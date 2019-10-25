/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:08:53 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 01:55:20 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_space_right(char *str, t_struct *flag)
{
	int len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flag.precised && len > 0 && len > flag.precision)
		len = flag.precision;
	flag.pos += write(1, str, len);
	while (flag.width > len)
	{
		flag.pos += write(1, " ", 1);
		flag.width--;
	}
}

static void	ft_print_and_align(char *str, t_struct *flag)
{
	int len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flag.precised && len > 0 && len > flag.precision)
		len = flag.precision;
	while (flag.width > len)
	{
		if (flag.zero)
			flag.pos += write(1, "0", 1);
		else
			flag.pos += write(1, " ", 1);
		flag.width--;
	}
	flag.pos += write(1, str, len);
}

void		ft_print_str(t_struct *flag, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (flag.minus)
		ft_print_space_left(str, flag);
	else
		ft_print_and_align(str, flag);
}