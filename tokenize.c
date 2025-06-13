/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:10:04 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/13 10:34:21 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_tokenize(t_cub3d *data);

/**
 * Function:
 * 1. reads the `.cub` input file line by line
 * 2. transform it into a list of tokens
 *
 */
void	ft_tokenize(t_cub3d *data)
{
	char	*line;
	int		i;
	int		start;

	while (line = get_next_line(data->infile_fd))
	{
		i = 0;
		while (i <= (int) ft_strlen(line))
		{
			while (ft_isspace(line[i]))
				i++;
			ft_add_token(&i, line, data);
		}
		free(line);
	}

}

/**
 * Function starts at a nonvoid character. It then needs to check
 * if the string forms one of the data identifiers, if yes it add's token
 * if it's not a data identifier it adds a word.
 *
 */
void	ft_add_token(int *i, char *line, t_cub3d *data)
{
	bool	is_id;

	is_id = ft_is_data_identifier(i, line);
	if (is_id)
		i = ft_add_data_identifier(i, line, data);
	else
		i = ft_add_word(i, line, data);
}
