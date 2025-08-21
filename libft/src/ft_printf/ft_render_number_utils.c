/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_number_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:12:08 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/21 12:37:11 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_padding_zeros(t_data *data);

void	ft_set_padding_zeros(t_data *data)
{
	if (data->format.minus)
		return ;
	if (data->format.width > data->format.nbr_length)
		data->format.nbr_padding_zeros = data->format.width
			- data->format.nbr_length;
	if (data->format.specifier == 'u')
		return ;
	else if (((ft_in("xX", data->format.specifier) && data->format.hash
				&& data->temp[0] != '0')) || data->format.specifier == 'p')
		data->format.nbr_padding_zeros -= 2;
	else if (data->format.is_number_negative
		|| (!data->format.is_number_negative && data->format.plus)
		|| data->format.space)
		data->format.nbr_padding_zeros--;
}
