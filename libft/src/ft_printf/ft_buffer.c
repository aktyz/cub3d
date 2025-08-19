/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:06:20 by zslowian          #+#    #+#             */
/*   Updated: 2024/10/03 16:15:54 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write_buffer(t_data *data, char c);
void	ft_flush_buffer(t_data *data);
void	ft_putchar_buffer(char c, int precision, t_data *data);
void	ft_putstring_buffer(char *str, size_t precision, t_data *data);
void	ft_itoa_buffer(t_data *data, t_value v);

/**
 * Function to write a Character c in the
 * memory buffer
 *
 **/
void	ft_write_buffer(t_data *data, char c)
{
	if (data->buffer_index == BUF_SIZE)
	{
		ft_flush_buffer(data);
	}
	data->buffer[data->buffer_index++] = c;
}

/**
 * Function to clean the buffer
 * (buffer memory set to 0 aka NULLs)
 *
 **/
void	ft_flush_buffer(t_data *data)
{
	data->nbr_chars += write(STDOUT_FILENO, data->buffer, data->buffer_index);
	my_memset(data->buffer, 0, BUF_SIZE);
	data->buffer_index = 0;
}

/**
 * Function to put into the buffer one Character c
 * taking field width (here precision) into account
 *
 **/
void	ft_putchar_buffer(char c, int precision, t_data *data)
{
	if (precision && precision <= 0)
		return ;
	else
		while (precision--)
			ft_write_buffer(data, c);
}

/**
 * Function to put into the buffer a String str
 * taking field width (here precision) into account
 *
 **/
void	ft_putstring_buffer(char *str, size_t precision, t_data *data)
{
	if (precision && precision <= 0)
		return ;
	else
		while (precision-- && *str)
			ft_write_buffer(data, *str++);
}

/**
 * Function to put into the buffer a String of numbers
 *
 */
void	ft_itoa_buffer(t_data *data, t_value int_value)
{
	t_value	local_temp;

	if (data->format.base < 2 || data->format.base > 16)
		return ;
	if (data->format.is_number_negative && !data->format.is_number_negated)
		ft_negate_number(data, int_value);
	else if (int_value.ul_value < data->format.base)
	{
		if (data->format.upper_case)
			data->temp[data->format.nbr_length++] = \
				UP_SYMBOLS[int_value.ul_value];
		else
			data->temp[data->format.nbr_length++] = \
				LOW_SYMBOLS[int_value.ul_value];
	}
	else
	{
		local_temp.ul_value = int_value.ul_value / data->format.base;
		ft_itoa_buffer(data, local_temp);
		local_temp.ul_value = int_value.ul_value % data->format.base;
		ft_itoa_buffer(data, local_temp);
	}
}
