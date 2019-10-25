/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:37:04 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 00:41:58 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct		s_struct
{
	unsigned int	len;
	int				minus;
	int				zero;
	int 			width;
	int 			precision;
}					t_struct;	

int					ft_printf(char const *s, ...);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *str);
void				ft_putstr(char const *str);
int					ft_printchar(va_list ap);
int					ft_putchar(char c);
int					ft_printstr(va_list ap);
void				ft_putnbr(int nb);
int					ft_printnbr(va_list ap);
char				*ft_utoa(unsigned int n);
int					ft_print_unsign(va_list ap);
char				*ft_hextoa(unsigned int n);
int					ft_print_hex(va_list ap);
char				*ft_hexcaptoa(unsigned int n);
int					ft_print_hex_cap(va_list ap);
int					ft_print_void(va_list ap);

#endif
