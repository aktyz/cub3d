/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:53:41 by zslowian          #+#    #+#             */
/*   Updated: 2024/10/03 16:15:54 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_render_string(t_data *data, char *str);
static void	ft_set_nbr_padding_spaces(t_data *data, char *s);

/**
 * Wrapper around ft_putstring_buffer function
 * to handle the left adjustment and potential
 * padding
 *
 */
void	ft_render_string(t_data *data, char *str)
{
	if (str == NULL)
	{
		str = "(null)";
	}
	ft_set_nbr_padding_spaces(data, str);
	if (data->format.minus)
	{
		if (data->format.is_precision)
			ft_putstring_buffer(str, data->format.precision, data);
		else
			ft_putstring_buffer(str, ft_strlen(str), data);
		while (data->format.nbr_padding_spaces--)
			ft_putstring_buffer(PADDING_SPACE, 1, data);
	}
	else
	{
		while (data->format.nbr_padding_spaces--)
			ft_putstring_buffer(PADDING_SPACE, 1, data);
		if (data->format.is_precision)
			ft_putstring_buffer(str, data->format.precision, data);
		else
		{
			ft_putstring_buffer(str, ft_strlen(str), data);
		}
	}
}

/**
 * Calculate and set the number of padding spaces
 * in the memory of data structure
 *
 */
static void	ft_set_nbr_padding_spaces(t_data *data, char *str)
{
	int	length;

	length = ft_strlen(str);
	if (data->format.width > 0)
	{
		if (data->format.precision > 0)
		{
			if (data->format.precision >= length)
				data->format.nbr_padding_spaces = data->format.width - length;
			else if (data->format.precision < length)
				data->format.nbr_padding_spaces = data->format.width
					- data->format.precision;
		}
		else
			data->format.nbr_padding_spaces = data->format.width - length;
	}
	if (data->format.nbr_padding_spaces < 0)
		data->format.nbr_padding_spaces = 0;
}
