/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:36:08 by zslowian          #+#    #+#             */
/*   Updated: 2024/05/19 15:36:08 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	my_memset(void *ptr, t_byte value, size_t n);
bool	ft_in(const char *str, char c);
void	print_my_structure(char *ft_name, t_data *data);
void	print_width_precision(char *ft_name, t_data *data);

/**
 * Set the memory under pointer ptr of size n
 * with unsigned char value
 *
 */
void	my_memset(void *ptr, t_byte value, size_t n)
{
	t_byte	*ptr_byte;

	ptr_byte = (t_byte *)ptr;
	while (n)
	{
		*ptr_byte++ = value;
		--n;
	}
}

/**
 * Check if Character c is one of chars
 * inside string str
 *
 */
bool	ft_in(const char *str, char c)
{
	if (str == 0)
		return (false);
	while (*str)
	{
		if (*str == c)
			return (true);
		++str;
	}
	return (false);
}

/**
 * Debugging helper function to print everything stored
 * in my custom structure
 *
 */
void	print_my_structure(char *ft_name, t_data *data)
{
	printf("Printing my structure in %s\n\n", ft_name);
	printf("Main structure t_data:\n");
	printf("Format string: %s\n", data->str);
	printf("Number of chars to return: %d\n", data->nbr_chars);
	printf("My buffer index: %d\n", data->buffer_index);
	printf("Content of buffer: \"%s\"\n\n", data->buffer);
	printf("Data->format content:\n");
	printf("\tMinus flag: %d\n", data->format.minus);
	printf("\tPlus flag: %d\n", data->format.plus);
	printf("\tSpace flag: %d\n", data->format.space);
	printf("\tHash flag: %d\n", data->format.hash);
	printf("\tZero_pad flag: %d\n", data->format.zero_pad);
	printf("\tSpecifier value: %c\n", data->format.specifier);
	printf("\tBase flag: %c\n", data->format.base);
	printf("\tUpperCase flag: %d\n", data->format.upper_case);
	printf("\tIs_Precision flag: %d\n", data->format.is_precision);
	printf("\tIs_Number_negative flag: %d\n", data->format.is_number_negative);
	print_width_precision(ft_name, data);
	printf("Number to print in case of number specifier: %lu\n",
		data->value_to_print.ul_value);
	printf("\n\n");
}

/**
 * Debugging helper function to print three variables concerning
 * padding
 *
 */
void	print_width_precision(char *ft_name, t_data *data)
{
	printf("Width and precision specifics in %s\n\n", ft_name);
	printf("\tWidth value: %d\n", data->format.width);
	printf("\tPrecision value: %d\n", data->format.precision);
	printf("\tNbr padding spaces value: %d\n", data->format.nbr_padding_spaces);
	printf("\tNumber of padding zeroes value: %d\n",
		data->format.nbr_padding_zeros);
	printf("\tNumber of number length value: %d\n", data->format.nbr_length);
	printf("\n\n");
}
