/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:30:41 by lulebugl          #+#    #+#             */
/*   Updated: 2019/11/04 13:30:43 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void			handle_escape(t_info *info)
{
	int		fg;

	fg = info->flags;
	if (fg & WIDTH_FLAG && !(fg & MINUS_FLAG))
		pad_width(info, 1);
	buff(info, "%", 1);
	if (fg & WIDTH_FLAG && (fg & MINUS_FLAG))
		pad_width(info, 1);
}
