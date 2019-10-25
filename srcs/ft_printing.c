/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 00:48:38 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 01:35:57 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		ft_print(const char *s, t_struct *flag, va_list ap)
{
	if (s[flag.i] == 'd' || s[flag.i] == 'i')
		ft_print_nbr(s[flag.i], flag, ap);
	else if (s[flag.i] == 'u')
		ft_print_unsign(s[flag.i], flag, ap);
	else if (s[flag.i] == 'x' || s[flag.i] == 'X')
		ft_print_hex(s[flag.i], flag, ap);
	else if (s[flag.i] == 'p')
		ft_print_pointer(s[flag.i], flag, ap);
	else if (s[flag.i] == 'c')
		ft_print_char(s[flag.i], flag, ap);
	else if (s[flag.i] == 's')
		ft_print_str(flag, ap);
	else if (s[flag.i] == '%')
		ft_print_percent_sign(s[flag.i], flag);
}

static void		ft_reset_struct(t_struct *f)
{
	flag->minus = 0;
	flag->zero = 0;
	flag->width = 0;
	//flag->precision_specified = 0;
	flag->precision = 0;
	//flag->length = 0;
}

void			ft_printing(const char *s, va_list ap, t_struct *flag)
{
	while (s[flag.i] != '\0')
	{
		if (s[flag.i] == '%')
		{
			flag.i++;
			if (ft_strchr("-.*0123456789", s[flag.i]))
				ft_parsing(s, flag, ap);
			if (ft_strchr("cspdiuxX%", s[flag.i]))
			{
				ft_print(s, flag, ap);
				if (f.len == -1)
					return ;
				ft_reset_struct(flag);
			}
		}
		else
			f.len += write(1, &s[flag.i], 1);
		flag.i++;
	}
}