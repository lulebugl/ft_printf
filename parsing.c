/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:27:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 18:17:16 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "includes/ft_printf.h"

#define IS_FLAG(x) ((x)=='#'||(x)=='0'||(x)=='-'||(x)=='+'||(x)==' ')

void			parse_flags(t_info *info)
{
	if (IS_FLAG(*info->f))
	{
		if (*info->f == '#')
			info->flags |= HASH_FLAG;
		else if (*info->f == '0')
			info->flags |= ZERO_FLAG;
		else if (*info->f == '-')
			info->flags |= MINUS_FLAG;
		else if (*info->f == '+')
			info->flags |= PLUS_FLAG;
		else if (*info->f == ' ')
			info->flags |= SPACE_FLAG;
		info->f++;
		parse_flags(info);
	}
}

void			parse_width(t_info *info)
{
	int	width;

	if (!(info->flags & INVALID) && (*info->f == '*' || ft_isdigit(*info->f)))
	{
		info->flags |= (info->flags & WIDTH_FLAG) ? INVALID : 0;
		if (!(info->flags & INVALID) && *info->f == '*')
		{
			info->f++;
			width = va_arg(info->args, int);
			info->flags |= (width < 0) ? MINUS_FLAG : 0;
			info->width = ABS(width);
			info->flags |= WIDTH_FLAG;
		}
		if (!(info->flags & INVALID) && ft_isdigit(*info->f))
		{
			info->flags |= (info->flags & WIDTH_FLAG) ? INVALID : 0;
			while (!(info->flags & INVALID) && ft_isdigit(*info->f))
				info->width = info->width * 10 + (*(info->f++) - '0');
			info->flags |= WIDTH_FLAG;
		}
		parse_width(info);
	}
}

void			parse_precision(t_info *t, int nb_rec)
{
	if (!(t->flags & INVALID) && (*t->f == '.' || nb_rec > 0))
	{
		t->f = (*t->f == '.') ? t->f + 1 : t->f;
		if (*t->f == '*' || ft_isdigit(*t->f))
		{
			t->flags |= (t->flags & PRECISION_FLAG) ? INVALID : 0;
			if (!(t->flags & INVALID) && *t->f == '*')
			{
				t->f++;
				t->precision = va_arg(t->args, int);
				t->flags |= PRECISION_FLAG;
			}
			if (!(t->flags & INVALID) && ft_isdigit(*t->f))
			{
				t->flags |= (t->flags & PRECISION_FLAG) ? INVALID : 0;
				while (!(t->flags & INVALID) && ft_isdigit(*t->f))
					t->precision = t->precision * 10 + (*(t->f++) - 48);
				t->flags |= PRECISION_FLAG;
			}
			parse_precision(t, nb_rec + 1);
		}
		t->flags |= PRECISION_FLAG;
	}
}
