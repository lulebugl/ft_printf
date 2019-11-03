/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prespecifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 22:45:41 by nmei              #+#    #+#             */
/*   Updated: 2019/11/03 15:22:54 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#define IS_FLAG(x) ((x)=='#'||(x)=='0'||(x)=='-'||(x)=='+'||(x)==' '||(x)=='\'')
#define IS_LEN(y) ((y)=='h'||(y)=='l'||(y)=='j'||(y)=='z'||(y)=='t'||(y)=='L')
#define IS_SLEN(z) ((z)=='j'||(z)=='z'||(z)=='t'||(z)=='L')

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
**	'-' : 4		DASH_FLAG 		(left justify)
**	'+' : 8		PLUS_FLAG		(show sign)
**	' ' : 16	SPACE_FLAG		(insert space)
**	''' : 32	APOST_FLAG		(format ints with locale's 1000's char)
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
**	EX2: 'if (info->flags & DASH_FLAG)' checks IFF the '-' flag is true
*/

void			parse_flags(t_info *p)
{
	if (IS_FLAG(*info->f))
	{
		if (*info->f == '#')
			info->flags |= HASH_FLAG;
		else if (*info->f == '0')
			info->flags |= ZERO_FLAG;
		else if (*info->f == '-')
			info->flags |= DASH_FLAG;
		else if (*info->f == '+')
			info->flags |= PLUS_FLAG;
		else if (*info->f == ' ')
			info->flags |= SPACE_FLAG;
		else if (*info->f == '\'')
			info->flags |= APOST_FLAG;
		info->f++;
		parse_flags(p);
	}
}

/*
**	parse_width()
**	For width we will either encounter either 'digits' or a 'wildcard'...
**	If we encounter a wildcard we'll read an argument out. Negative values for
**	the wildcard arg are invalid so we set our width = 0 if we get one...
**
**	We also want to check if someone tries to give a format like:
**	"%*5d" or "%5*d"
**
**	If we parse a '*'' or 'series of digits' then we set a width obtained flag.
**	If we found that this flag was already previously set, then we also need to
**	set a flag that our entire prespecifier is invalid.
**
**	We need to recursively call parse_width() because we might get an invalid
**	set of prespecifiers. Such as: "%*9*1*4d" (whyyyy would someone do this?)
*/

void			parse_width(t_info *p)
{
	int tentative_width;

	if (!(info->flags & f_INVALID) && (*info->f == '*' || ft_isdigit(*info->f)))
	{
		info->flags |= (info->flags & WIDTH_OB_FLAG) ? f_INVALID : 0;
		if (!(info->flags & f_INVALID) && *info->f == '*')
		{
			info->f++;
			tentative_width = va_arg(info->args, int);
			info->flags |= (tentative_width < 0) ? DASH_FLAG : 0;
			info->width = ABS(tentative_width);
			info->flags |= WIDTH_OB_FLAG;
		}
		if (!(info->flags & f_INVALID) && ft_isdigit(*info->f))
		{
			info->flags |= (info->flags & WIDTH_OB_FLAG) ? f_INVALID : 0;
			while (!(info->flags & f_INVALID) && ft_isdigit(*info->f))
				info->width = info->width * 10 + (*(info->f++) - '0');
			info->flags |= WIDTH_OB_FLAG;
		}
		parse_width(p);
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

void			parse_precision(t_info *p, int recurse_level)
{
	if (!(info->flags & f_INVALID) && (*info->f == '.' || recurse_level > 0))
	{
		info->f = (*info->f == '.') ? info->f + 1 : info->f;
		if (*info->f == '*' || ft_isdigit(*info->f))
		{
			info->flags |= (info->flags & PRECI_OB_FLAG) ? f_INVALID : 0;
			if (!(info->flags & f_INVALID) && *info->f == '*')
			{
				info->f++;
				info->precision = va_arg(info->args, int);
				info->flags |= PRECI_OB_FLAG;
			}
			if (!(info->flags & f_INVALID) && ft_isdigit(*info->f))
			{
				info->flags |= (info->flags & PRECI_OB_FLAG) ? f_INVALID : 0;
				while (!(info->flags & f_INVALID) && ft_isdigit(*info->f))
					info->precision = info->precision * 10 + (*(info->f++) - '0');
				info->flags |= PRECI_OB_FLAG;
			}
			parse_precision(p, recurse_level + 1);
		}
		info->flags |= PRECI_OB_FLAG;
	}
}

/*
**	parse_long_length()
**	This function will specially parse our (potentially) long length options:
**	h, hh, l, and ll
**
**	If our format string equals the char we care about
**		If we have already obtained a length previously
**			If we have the single flag AND don't have the double flag
**				Use bitwise xor to set the single flag to 0
**				Use bitwise or to set our double flag to 1
**			else
**				We have an invalid format on our hands...
**		else
**			Use bitwise or to set our single flag to 1
**			Set our length obtained flag to 1
*/

static void		parse_long_length(t_info *p, char c, int s_flag, int d_flag)
{
	if (*info->f == c)
	{
		if (info->flags & LEN_OB_FLAG)
		{
			if ((info->flags & s_flag) && !(info->flags & d_flag))
			{
				info->flags ^= s_flag;
				info->flags |= d_flag;
			}
			else
				info->flags |= f_INVALID;
		}
		else
		{
			info->flags |= s_flag;
			info->flags |= LEN_OB_FLAG;
		}
	}
}

/*
**	parse_length()
**	This function will parse all our length options. Need to call recursively
**	to check against crazy options like "hhh" or "jzjz" or "hj" or "hhL".
**
**	As mentioned in parse_precision() we also check for '.' in the case
**	that the format string has multiple '.'s
*/

void			parse_length(t_info *p)
{
	if (!(info->flags & f_INVALID) && IS_LEN(*info->f))
	{
		parse_long_length(p, 'h', H_FLAG, HH_FLAG);
		parse_long_length(p, 'l', L_FLAG, LL_FLAG);
		if (IS_SLEN(*info->f))
		{
			if (!(info->flags & LEN_OB_FLAG))
			{
				info->flags |= (*info->f == 'j') ? J_FLAG : 0;
				info->flags |= (*info->f == 'z') ? Z_FLAG : 0;
				info->flags |= (*info->f == 't') ? T_FLAG : 0;
				info->flags |= (*info->f == 'L') ? FLOAT_L_FLAG : 0;
				info->flags |= LEN_OB_FLAG;
			}
			else
				info->flags |= f_INVALID;
		}
		info->f++;
		parse_length(p);
	}
	else if (*info->f == '.')
		info->flags |= f_INVALID;
}
