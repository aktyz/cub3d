/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/18 21:18:10 by zslowian          #+#    #+#             */
/*   Updated: 2024/05/18 21:18:10 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_initialize_data(t_data *data, const char *format);
void		ft_render_format(t_data *data);
void		ft_put_nil(t_data *data);
static void	ft_split_on_numeric_specifier(t_data *data, char specifier);

/**
 * Function replicating the behaviour of stdio.h
 * printf()
 *
 */
int	ft_printf(const char *str, ...)
{
	t_data	data;

	va_start(data.arg_ptr, str);
	if (ft_initialize_data(&data, str))
		return (MALLOC_ERROR);
	while (*data.str != '\0')
	{
		if (*data.str == '%' && *(++data.str))
		{
			if (ft_parsef(&data))
				return (PARSE_ERROR);
			ft_render_format(&data);
		}
		else
			ft_write_buffer(&data, *data.str);
		++data.str;
	}
	ft_flush_buffer(&data);
	va_end(data.arg_ptr);
	free(data.buffer);
	return (data.nbr_chars);
}

/**
 * Function that is initializing t_data structure to hold
 * all the necessary information for printf to work
 * properly
 *
 */
static int	ft_initialize_data(t_data *data, const char *format_string)
{
	data->nbr_chars = 0;
	data->str = format_string;
	data->buffer = malloc(BUF_SIZE * sizeof(char));
	data->value_to_print.l_value = 0;
	if (NULL == data->buffer)
		return (MALLOC_ERROR);
	data->buffer_index = 0;
	my_memset(data->buffer, 0, BUF_SIZE * sizeof(char));
	return (OK);
}

/**
 * Function switching between correct wrappers depending on
 * the format specifier: "cspdiuxX%"
 */
void	ft_render_format(t_data *data)
{
	char	specifier;

	specifier = data->format.specifier;
	if (specifier == '%')
		ft_render_char(data, '%');
	else if (specifier == 'c')
		ft_render_char(data, va_arg(data->arg_ptr, int));
	else if (specifier == 's')
		ft_render_string(data, va_arg(data->arg_ptr, char *));
	if (ft_in("pdiuxX", specifier))
		ft_split_on_numeric_specifier(data, specifier);
}

static void	ft_split_on_numeric_specifier(t_data *data, char specifier)
{
	if (ft_in("di", specifier))
	{
		data->value_to_print.l_value = (long) va_arg(data->arg_ptr, int);
		if (data->value_to_print.l_value < 0)
			data->format.is_number_negative = true;
	}
	else if (specifier == 'p')
	{
		data->value_to_print.ul_value = (unsigned long)
			va_arg(data->arg_ptr, void *);
		ft_put_nil(data);
	}
	else if (ft_in("uxX", specifier))
		data->value_to_print.ul_value = (unsigned long)
			va_arg(data->arg_ptr, unsigned int);
	if (!data->format.nil)
		ft_render_number(data);
}

void	ft_put_nil(t_data *data)
{
	if (data->format.specifier == 'p' && data->value_to_print.l_value == 0)
	{
		ft_putstring_buffer("(nil)", 5, data);
		data->format.nil = true;
	}
}
