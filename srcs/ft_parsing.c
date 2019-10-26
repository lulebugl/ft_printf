/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:04:21 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 04:57:28 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_precision(const char *s, t_struct *flag, va_list ap)
{
	int precision;

	if (s[flag->i] == '.')
	{
		flag->i++;
		flag->precised = 1;
		if (ft_isdigit(s[flag->i]))
		{
			flag->precision = ft_atoi(&s[flag->i]);
			while (ft_isdigit(s[flag->i]))
				flag->i++;
		}
		else if (s[flag->i] == '*')
		{
			precision = va_arg(ap, int);
			if (precision >= 0)
				flag->precision = precision;
			else
				flag->precised = 0;
			while (s[flag->i] == '*')
				flag->i++;
		}
	}
	if (flag->precised && !flag->minus)
		flag->space = 0;
}

static void	ft_width(const char *s, t_struct *flag, va_list ap)
{
	if (s[flag->i] == '*')
	{
		flag->width = va_arg(ap, int);
		flag->minus = (flag->width < 0) ? 1 : flag->minus;
		flag->width = (flag->width < 0) ? -flag->width : flag->width;
		while (s[flag->i] == '*')
			flag->i++;
	}
	if (ft_isdigit(s[flag->i]))
	{
		flag->width = ft_atoi(&s[flag->i]);
		while (ft_isdigit(s[flag->i]))
		{
			flag->i++;
			if (s[flag->i] == '*')
			{
				flag->width = va_arg(ap, int);
				flag->width = (flag->width < 0) ? -flag->width : flag->width;
				while (s[flag->i] == '*')
					flag->i++;
			}
		}
	}
}

static void	ft_flags(const char *s, t_struct *flag)
{
	while (ft_strchr("-0", s[flag->i]))
	{
		if (s[flag->i] == '-')
			flag->minus = 1;
		else if (s[flag->i] == '0')
			flag->zero = 1;
		flag->i++;
	}
}

void		ft_parsing(const char *s, va_list ap, t_struct *flag)
{
	ft_flags(s, flag);
	ft_width(s, flag, ap);
	ft_precision(s, flag, ap);
}
