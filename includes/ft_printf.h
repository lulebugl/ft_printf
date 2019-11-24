/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:49:30 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/17 20:42:04 by lulebugl         ###   ########.fr       */
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

typedef struct	s_pfinfo
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
}				t_pfinfo;

int				ft_printf_fd(int fd, const char *format, va_list args);
int				ft_printf(const char *format, ...);
void			print_buffer(t_pfinfo *info);
void			buff(t_pfinfo *info, const void *s, size_t nbyte);
void			pad(t_pfinfo *info, int pad_len, char c);
void			pad_width(t_pfinfo *info, int arg_width);
void			reset_printf(t_pfinfo *info);
void			parse_flags(t_pfinfo *info);
void			parse_width(t_pfinfo *info);
void			parse_precision(t_pfinfo *info, int nb_rec);
void			parse_length(t_pfinfo *info);
void			handle_char(t_pfinfo *info);
void			handle_str(t_pfinfo *info);
void			handle_percent(t_pfinfo *info);
void			pf_itoa_base(t_pfinfo *info, uintmax_t nbr, int nbrlen);
void			handle_int(t_pfinfo *info);
void			handle_int_prepad(t_pfinfo *info, int nbrlen, int signed_int);
void			handle_uint(t_pfinfo *info);
void			handle_uint_hex(t_pfinfo *info);

typedef void	(*t_convtable)(t_pfinfo *info);
t_convtable		get_funct(char c);

#endif
