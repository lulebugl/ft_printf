/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:02:34 by lulebugl          #+#    #+#             */
/*   Updated: 2019/10/16 22:33:11 by lulebugl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;
	int		i;
	int		limit;

	i = 0;
	last = lst;
	limit = ft_lstsize(lst) - 1;
	while (i < limit)
	{
		i++;
		last = last->next;
	}
	return (last);
}
