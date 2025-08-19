/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:34:34 by zslowian          #+#    #+#             */
/*   Updated: 2024/09/26 21:34:34 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tail;
	int		i;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	new->lst_size = (*lst)->lst_size + 1;
	tail = ft_lstlast(*lst);
	tail->next = new;
	tail = *lst;
	i = (*lst)->lst_size;
	while (i--)
	{
		(tail->lst_size)++;
		tail = tail->next;
	}
}
