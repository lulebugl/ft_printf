/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:49:30 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 17:41:19 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <sys/types.h>
# include <stdint.h>
# include <stdarg.h>
# include <unistd.h>

# define HASH_FLAG		1
# define ZERO_FLAG		2
# define MINUS_FLAG		4
# define PLUS_FLAG		8
# define SPACE_FLAG		16
# define WIDTH_FLAG		32
# define PRECISION_FLAG	64
# define INVALID		128

# define MAX(x, y) (((x) > (y)) ? (x) : (y))
# define ABS(x) (((x) < 0) ? -(x) : (x))

# define BUFF_SIZE	4096

typedef struct	s_info
{
	const char	*f;
	const char	*cpy_str;
	va_list		args;
	int			fd;
	size_t		len;
	size_t		buf_len;
	char		buf[BUFF_SIZE];
	int			flags;
	int			width;
	int			precision;
	int			base;
	int			neg;
	uintmax_t	hex_int;
	char		arg_type;
}				t_info;

int				ft_vfprintf(int fd, const char *format, va_list args);
int				ft_printf(const char *format, ...);

/*
**	printf_gen_utils.c
*/
void			print_buffer(t_info *info);
void			buff(t_info *info, const void *s, size_t nbyte);
void			pad(t_info *info, int pad_len, char c);
void			pad_width(t_info *info, int arg_width);
void			reset_printf(t_info *info);

/*
**	printf_int_utils.c
*/
void			pf_itoa_base(t_info *info, uintmax_t nbr, int nbrlen);
void			handle_int_prepad(t_info *info, int nbrlen, int signed_int);

/*
**	parse_prearg_types.c
**
**	We'll separate into separate parsing steps:
**	[flags]: '-', '+', ' ', '#', '0'
**	[width]: 'number', '*'
**	[.precision]: '.number', '.*'
**	[length]: '(none)', 'hh', 'h', 'l', 'll', 'j', 'z', 't', 'L'
*/
void			parse_flags(t_info *info);
void			parse_width(t_info *info);
void			parse_precision(t_info *info, int nb_rec);
void			parse_length(t_info *info);

/*
**	parse_arg_type.c
**
**	After parsing pre-arg_types we'll use a conv_ table to get proper
**	handlers for all the different possible arg_types.
**	arg_types: '%', 'di', 'ouxX', 'c', 's', 'p'
*/
typedef void	(*t_convtable)(t_info *info);
t_convtable		get_handler_funct(char c);

/*
**	int_handlers.c
**	handles 'd', and 'i' arg_types
*/
void			handle_int(t_info *info);

/*
**	uint_handlers.c
**	handles 'o', 'u', 'xX', and 'p' arg_types
*/
void			handle_uint(t_info *info);
void			handle_uint_hex(t_info *info);

void			handle_char(t_info *info);
void			handle_str(t_info *info);
void			handle_percent(t_info *info);

#endif
