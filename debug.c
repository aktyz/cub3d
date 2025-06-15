/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:27:04 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/15 18:33:36 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_token_list(t_cub3d *data);

void	ft_print_token_list(t_cub3d *data)
{
	t_list	*ptr;
	int		i;
	t_token	*token;

	if (data && data->tokens)
		ptr = data->tokens;
	i = 0;
	while (ptr && ptr->content)
	{
		token = (t_token *) ptr->content;
		ft_printf("token nb: %d\n", i);
		ft_printf("\tdata type:\t%s\n", token->data_id);
		ft_printf("\tdata value:\t%s\n", token->value);
		ptr = ptr->next;
		i++;
	}
}
