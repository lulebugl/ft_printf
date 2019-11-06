/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 21:46:05 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 23:26:20 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst && *alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	if (alst && !*alst && new)
	{
		new->next = NULL;
		*alst = new;
	}
}
