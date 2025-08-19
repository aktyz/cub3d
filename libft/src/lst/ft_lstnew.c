/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:18:29 by zslowian          #+#    #+#             */
/*   Updated: 2024/09/26 21:18:29 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list_node;

	list_node = malloc(sizeof(t_list));
	list_node->content = content;
	list_node->lst_size = 1;
	list_node->next = 0;
	return (list_node);
}
