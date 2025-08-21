/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:10:04 by zslowian          #+#    #+#             */
/*   Updated: 2025/08/21 14:49:58 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_tokenize(t_cub3d *data);
bool		ft_add_token(int *i, char *line, t_cub3d *data);
static bool	ft_is_data_identifier(int *i, char *line, t_cub3d *data,
				bool *is_error);
static bool	ft_add_data_id_value(int *i, char *line, t_token *last,
				t_cub3d *data);
const char	**ft_get_data_identifiers(void);

/**
 * Function:
 * 1. reads the `.cub` input file line by line
 * 2. transform it into a list of tokens
 *
 */
void	ft_tokenize(t_cub3d *data)
{
	char	*line;

	line = get_next_line(data->infile_fd);
	while (line)
	{
		ft_parse_cub3d_line(data, line);
		if (line)
			free(line);
		line = get_next_line(data->infile_fd);
	}
	if (close(data->infile_fd) == 0)
		data->infile_fd = -1;
	else
		ft_error(FILE_CLOSE, "ft_tokenize", data);
}

/**
 * Function starts at a nonvoid character. It then needs to check
 * if the string forms one of the data identifiers, if yes it add's token
 * if it's not a data identifier it adds a word.
 * If there's any error inside this function, it returns true.
 * Returns false if all good.
 */
bool	ft_add_token(int *i, char *line, t_cub3d *data)
{
	bool	is_id;
	t_token	*last;
	bool	is_error;

	is_error = false;
	is_id = ft_is_data_identifier(i, line, data, &is_error);
	if (is_id)
		return (is_error);
	if (!data->tokens)
		return (true);
	last = (t_token *) ft_lstlast(data->tokens)->content;
	if (!last->value)
		return (ft_add_data_id_value(i, line, last, data));
	else
		return (ft_add_map_token(i, line, last, data));
	*i = *i + 1;
	return (false);
}

/**
 * Function checks the token for being one of the cub3d map data
 * identifiers, and if yes, it adds it to the token list, returning
 * true.
 * It returns false if the token is not a data identifier, so that
 * the string can be added as a word.
 *
 */
static bool	ft_is_data_identifier(int *i, char *line, t_cub3d *data,
		bool *is_error)
{
	int		j;
	int		k;

	j = -1;
	k = *i;
	while (ft_isspace(line[k]))
		k++;
	while (++j < DATA_ID_NB)
	{
		if (ft_strncmp((const char *)&line[k], ft_get_data_identifiers()[j],
			ft_strlen(ft_get_data_identifiers()[j])) == 0)
		{
			*is_error = ft_new_token(data, j, i, k);
			return (true);
		}
	}
	return (false);
}

/**
 * Function adds the data value to the last token from the list if there's
 * list node with data_id type created.
 * If there's any error inside this function, it returns true.
 * Returns false if all good.
 */
static bool	ft_add_data_id_value(int *i, char *line, t_token *last,
		t_cub3d *data)
{
	char	*ptr;
	int		char_count;
	int		k;

	if (ft_check_tokens_before_value_add(data, last))
		return (true);
	ptr = &line[*i];
	char_count = 0;
	k = *i;
	while (ft_isspace(*ptr))
	{
		ptr++;
		k++;
	}
	if (!*ptr)
		return (true);
	while (ft_isspace(*ptr) == 0)
	{
		char_count++;
		ptr++;
	}
	*i = k + char_count;
	return (ft_populate_token_value(last, line, char_count, k));
}

const char	**ft_get_data_identifiers(void)
{
	static const char	*data_identifiers[DATA_ID_NB];

	data_identifiers[0] = "NO";
	data_identifiers[1] = "SO";
	data_identifiers[2] = "WE";
	data_identifiers[3] = "EA";
	data_identifiers[4] = "F";
	data_identifiers[5] = "C";
	return (data_identifiers);
}
