/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 13:52:46 by nmei              #+#    #+#             */
/*   Updated: 2019/11/03 15:22:54 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void			handle_escape(t_info *info)
{
	int		pf;

	pf = info->flags;
	if (pf & WIDTH_OB_FLAG && !(pf & DASH_FLAG))
		pad_width(p, 1);
	buff(p, "%", 1);
	if (pf & WIDTH_OB_FLAG && (pf & DASH_FLAG))
		pad_width(p, 1);
}

void			handle_n(t_info *info)
{
	if (info->flags & HH_FLAG)
		*va_arg(info->args, signed char *) = (signed char)info->len;
	else if (info->flags & H_FLAG)
		*va_arg(info->args, short int *) = (short int)info->len;
	else if (info->flags & L_FLAG)
		*va_arg(info->args, long int *) = (long int)info->len;
	else if (info->flags & LL_FLAG)
		*va_arg(info->args, long long int *) = (long long int)info->len;
	else if (info->flags & J_FLAG)
		*va_arg(info->args, intmax_t *) = (intmax_t)info->len;
	else if (info->flags & Z_FLAG)
		*va_arg(info->args, ssize_t *) = (ssize_t)info->len;
	else if (info->flags & T_FLAG)
		*va_arg(info->args, ptrdiff_t *) = (ptrdiff_t)info->len;
	else
		*va_arg(info->args, int *) = (int)info->len;
}
