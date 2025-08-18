/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:24:33 by zslowian          #+#    #+#             */
/*   Updated: 2024/09/26 21:24:33 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	int	i;

	if (!lst || !new)
		return ;
	i = (*lst)->lst_size;
	new->lst_size = i + 1;
	new->next = *lst;
	*lst = new;
	i--;
	new = new->next;
	while (i--)
	{
		(new->lst_size)++;
		new = new->next;
	}
}
