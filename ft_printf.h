/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:35:39 by llebugle          #+#    #+#             */
/*   Updated: 2024/10/28 12:52:38 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);
size_t	ft_putstr_fd(char *s, int fd);
size_t	ft_putnbr_fd(int nb, int fd);
size_t	print_unsigned(unsigned int nb);
size_t	print_hex(unsigned long long n, char *base);
size_t	print_pointer(unsigned long long p);

#endif
