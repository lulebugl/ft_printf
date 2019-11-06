/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 23:43:23 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 23:29:17 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst && *lst && del)
	{
		if ((*lst)->next)
			ft_lstclear(&(*lst)->next, del);
		ft_lstdelone((*lst), del);
		*lst = NULL;
	}
}
