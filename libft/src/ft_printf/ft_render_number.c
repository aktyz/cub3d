/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:48:27 by zslowian          #+#    #+#             */
/*   Updated: 2024/05/21 18:48:27 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_set_padding_zeros_wrapper(t_data *data);
static void	ft_set_padding_spaces(t_data *data);
static void	ft_sign(t_data *data);
static void	ft_put0x(t_data *data);
void		ft_render_number(t_data *data);

/**
 * Wrapper around ft_putnumber_buffer function
 * to handle the left adjustment and all the flags
 *
 */
void	ft_render_number(t_data *data)
{
	ft_itoa_buffer(data, data->value_to_print);
	ft_set_padding_zeros_wrapper(data);
	if (data->format.space || data->format.width)
		ft_set_padding_spaces(data);
	if (data->format.minus)
	{
		ft_sign(data);
		ft_putchar_buffer('0', data->format.nbr_padding_zeros, data);
		ft_putstring_buffer(data->temp, data->format.nbr_length, data);
		ft_putchar_buffer(' ', data->format.nbr_padding_spaces, data);
	}
	else
	{
		ft_putchar_buffer(' ', data->format.nbr_padding_spaces, data);
		ft_sign(data);
		ft_putchar_buffer('0', data->format.nbr_padding_zeros, data);
		ft_putstring_buffer(data->temp, data->format.nbr_length, data);
	}
}

/**
 * Function to set the number of zeros to pad the eventual
 * number to be printed
 */
static void	ft_set_padding_zeros_wrapper(t_data *data)
{
	if (data->format.precision > 0)
	{
		if (data->format.precision > data->format.nbr_length)
		{
			data->format.nbr_padding_zeros = data->format.precision - \
				data->format.nbr_length;
			return ;
		}
	}
	if (data->format.zero_pad)
		ft_set_padding_zeros(data);
	if (data->format.nbr_padding_zeros < 0)
		data->format.nbr_padding_zeros = 0;
}

/**
 * Function to set the number of spaces to pad the eventual
 * number to be printed
 */
static void	ft_set_padding_spaces(t_data *data)
{
	char	specifier;

	specifier = data->format.specifier;
	if (data->format.width)
		data->format.nbr_padding_spaces = data->format.width - \
			data->format.nbr_padding_zeros - data->format.nbr_length;
	else if (!data->format.is_number_negative)
		data->format.nbr_padding_spaces++;
	if (ft_in("uxXp", specifier))
	{
		if (((ft_in("xX", specifier) && data->format.hash && \
				data->temp[0] != '0')) || specifier == 'p')
			data->format.nbr_padding_spaces -= 2;
		return ;
	}
	if (data->format.is_number_negative)
	{
		data->format.nbr_padding_spaces--;
		return ;
	}
	if (!data->format.is_number_negative && data->format.plus)
	{
		data->format.nbr_padding_spaces--;
		return ;
	}
}

/**
 * Function to handle special signs that can occur in front
 * of a number: "+-0x..."
 */
static void	ft_sign(t_data *data)
{
	if (data->format.base == BASE_16 && data->value_to_print.l_value != 0)
		ft_put0x(data);
	else if (data->format.plus)
	{
		if (data->temp[0] != '0' && !data->format.is_number_negative)
			ft_putchar_buffer('+', 1, data);
		else if (data->value_to_print.l_value == 0)
			ft_putchar_buffer('+', 1, data);
		else if (!data->format.plus && data->format.space)
			ft_putchar_buffer(' ', 1, data);
	}
}

/**
 * Function to proceed the memory addres with appropriate
 * symbols: "0X" or "0x"
 */
static void	ft_put0x(t_data *data)
{
	if (((ft_in("xX", data->format.specifier) && data->format.hash && \
				data->temp[0] != '0')) || data->format.specifier == 'p')
	{
		if (data->format.upper_case)
			ft_putstring_buffer("0X", 2, data);
		else
			ft_putstring_buffer("0x", 2, data);
	}
}
