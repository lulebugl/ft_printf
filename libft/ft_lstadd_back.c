/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:19:24 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 23:15:48 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *node;

	if (alst && *alst)
	{
		node = *alst;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else if (alst && !(*alst))
		*alst = new;
}
