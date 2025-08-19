/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:04:15 by zslowian          #+#    #+#             */
/*   Updated: 2025/04/10 21:16:23 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char_array(char **arr, int arr_size)
{
	if (arr == NULL)
		return ;
	while (arr_size--)
	{
		ft_printf("%s\n", *arr);
		arr++;
	}
}
