/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:37:04 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/26 05:13:05 by lulebugl         ###   ########.fr       */
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
	int				i;
	int				pos;
	int				minus;
	int				zero;
	int				space;
	int 			width;
	int 			precision;
	int				precised;
}					t_struct;

int					ft_printf(char const *s, ...);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *str);
int					ft_isdigit(int c);
char				*ft_strchr(const char *s, int c);
void				ft_putstr(char *str);
void				ft_print_char(t_struct *flag, va_list ap);
void				ft_print_str(t_struct *flag, va_list ap);
void				ft_putnbr(int nb);
void				ft_print_nbr(t_struct *flag, va_list ap);
void				ft_print_percent(t_struct *flag);
char				*ft_utoa(unsigned int n);
void				ft_print_unsign(t_struct *flag, va_list ap);
char				*ft_hextoa(unsigned int n);
void				ft_print_hex(char c, t_struct *flag, va_list ap);
char				*ft_hexcaptoa(unsigned int n);
void				ft_print_pointer(t_struct *flag, va_list ap);
void				ft_printing(const char *s, va_list ap, t_struct *flag);
void				ft_parsing(const char *s, t_struct *flag, va_list ap);

#endif
