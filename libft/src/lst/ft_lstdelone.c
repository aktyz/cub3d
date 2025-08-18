/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:39:02 by zslowian          #+#    #+#             */
/*   Updated: 2024/09/26 21:39:02 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function deletes the lst node on the list, using del function
 * to free the content of this node.
 * DON'T USE IT in separation from ft_lstclear - we need to switch
 * to two directional list in order to refactor it properly
 * or add third paramenter: lst_head
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || del == NULL)
		return ;
	if (lst->content)
		del(lst->content);
	free(lst);
	lst = NULL;
}
