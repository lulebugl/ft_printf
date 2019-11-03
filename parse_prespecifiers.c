/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prespecifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:27:37 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/03 17:08:29 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#define IS_FLAG(x) ((x)=='#'||(x)=='0'||(x)=='-'||(x)=='+'||(x)==' ')

/*
**	Parse the format string we just encountered!
**	%[flags][width][.precision][length]specifier
**
**	We'll separate into separate parsing steps:
**	[flags]: '-', '+', ' ', '#', '0'
**	[width]: 'number', '*'
**	[.precision]: '.number', '.*'
**	[length]: '(none)', 'hh', 'h', 'l', 'll', 'j', 'z', 't', 'L'
**	specifier: 'di', 'ouxX', 'fFeEgGaA', 'c', 's', 'p', 'n'
*/

/*
**	parse_flags() - We'll use a binary numeral system similar to file
**	permissions to encode which flags we have in our format prespecifier.
**	This way we can encode all our flags in 1 variable and keep things clean.
**
**	Call the function recursively until we do not encounter any more flags...
**
**	'#' : 1		HASH_FLAG		(force prefix)
**	'0' : 2		ZERO_FLAG		(left pad)
**	'-' : 4		MINUS_FLAG 		(left justify)
**	'+' : 8		PLUS_FLAG		(show sign)
**	' ' : 16	SPACE_FLAG		(insert space)
**
**	#0- = 1 + 2 + 4 = 7
**	- + = 4 + 16 + 8 = 28
**	etc...
**
**	Using bitwise 'or' we can easily set each flag:
**	EX: info->flag |= HASH_FLAG; set '#' flag to true
**
**	Using bitwise 'and' we can easily read out the status of each flag:
**	EX: 'if (info->flags & SPACE_FLAG)' checks IFF the ' ' flag is true
**	EX2: 'if (info->flags & MINUS_FLAG)' checks IFF the '-' flag is true
*/

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

void			parse_width(t_info *info)  // ok pour parsing width //
{
	int	width;

	if (!(info->flags & INVALID) && (*info->f == '*' || ft_isdigit(*info->f)))
	{
		info->flags |= (info->flags & WIDTH_FLAG) ? INVALID : 0;
		/* si il y a nos flags et que la width est deja determiner ---> flag = 128 sinon flags = flags */
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

/*
**	parse_precision()
**	For precision we will encounter a '.' followed by 'digits' or a 'wildcard'.
**	Very similar to parse_width. The only difference is the '.' and that we
**	store the precision in the info->precision variable.
**
**	This function will stall if the format string has multiple '.'s. We can use
**	this fact to check if the character in the parse_length() function starts
**	with a '.' to determine if we have an invalid prespecifier.
*/

void			parse_precision(t_info *info, int nb_rec)
{
	if (!(info->flags & INVALID) && (*info->f == '.' || nb_rec > 0))
	{
		info->f = (*info->f == '.') ? info->f + 1 : info->f;
		if (*info->f == '*' || ft_isdigit(*info->f))
		{
			info->flags |= (info->flags & PRECISION_FLAG) ? INVALID : 0;
			if (!(info->flags & INVALID) && *info->f == '*')
			{
				info->f++;
				info->precision = va_arg(info->args, int);
				info->flags |= PRECISION_FLAG;
			}
			if (!(info->flags & INVALID) && ft_isdigit(*info->f))
			{
				info->flags |= (info->flags & PRECISION_FLAG) ? INVALID : 0;
				while (!(info->flags & INVALID) && ft_isdigit(*info->f))
					info->precision = info->precision * 10 + (*(info->f++) - '0');
				info->flags |= PRECISION_FLAG;
			}
			parse_precision(p, nb_rec + 1);
		}
		info->flags |= PRECISION_FLAG;
	}
}
