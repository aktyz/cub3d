/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:42:04 by zslowian          #+#    #+#             */
/*   Updated: 2024/09/26 21:42:04 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function free the whole lst using del function to free the content of each
 * of it's nodes.
 *
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		if ((*lst)->next)
			head = (*lst)->next;
		else
			head = NULL;
		ft_lstdelone(*lst, del);
		*lst = head;
	}
	*lst = 0;
}
