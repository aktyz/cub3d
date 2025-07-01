/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:10:04 by zslowian          #+#    #+#             */
/*   Updated: 2025/07/03 13:19:43 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				ft_tokenize(t_cub3d *data);
void				ft_add_token(int *i, char *line, t_cub3d *data);
bool				ft_is_data_identifier(int *i, char *line, t_cub3d *data);
void				ft_add_data_id_value(int *i, char *line, t_token *last,
						 t_cub3d *data);
static const char	**ft_get_data_identifiers(void);

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
	int		line_len;

	while ((line = get_next_line(data->infile_fd)) != NULL)
	{
		i = 0;
		line_len = ft_strlen(line);
		while (i < line_len)
			ft_add_token(&i, line, data);
		free(line);
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
 *
 */
void	ft_add_token(int *i, char *line, t_cub3d *data)
{
	bool	is_id;
	t_token	*last;

	is_id = ft_is_data_identifier(i, line, data);
	if (is_id)
		return ;
	last = (t_token *) ft_lstlast(data->tokens)->content;
	if (!last->value)
		ft_add_data_id_value(i, line, last, data);
	else if (line[*i] != '\n')
		ft_add_map_line(i, line, data);
	else
		*i = *i + 1;
}

/**
 * Function checks the token for being one of the cub3d map data
 * identifiers, and if yes, it adds it to the token list, returning
 * true.
 * It returns false if the token is not a data identifier, so that
 * the string can be added as a word.
 *
 */
bool	ft_is_data_identifier(int *i, char *line, t_cub3d *data)
{
	t_token	*new_token;
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
			new_token = ft_calloc(sizeof(t_token), 1);
			if (new_token == NULL)
				ft_error(MEM_ERROR, "ft_is_data_identifier", data);
			new_token->data_id = (t_cub3d_token_types) j;
			if (data->tokens == NULL)
				data->tokens = ft_lstnew((void *) new_token);
			else
				ft_lstadd_back(&data->tokens, ft_lstnew((void *) new_token));
			*i = k + ft_strlen(ft_get_data_identifiers()[j]);
			return (true);
		}
	}
	return (false);
}

/**
 * Function adds the data value to the last token from the list if there's
 * list node with data_id type created.
 *
 */
void	ft_add_data_id_value(int *i, char *line, t_token *last, t_cub3d *data)
{
	char	*ptr;
	int		char_count;
	int		k;

	if (data->tokens == NULL)
		ft_error(TOKENIZING_ERROR, "ft_add_data_id_value", data);
	if ((last->data_id < NO || last->data_id > C) // only for tokens with the data_id to be enriched
		|| ((last->data_id >= NO && last->data_id <= C) && last->value != NULL) // make sure you don't overwrite
		|| (last->data_id && last->value != NULL)) // make sure you don't overwrite a different type data_id token
		ft_error(TOKENIZING_ERROR,
			"ft_add_data_id_value - data value is being added on wrong token", data);
	ptr = &line[*i];
	char_count = 0;
	k = *i;
	while (ft_isspace(*ptr))
	{
		ptr++;
		k++;
	}
	while (ft_isspace(*ptr) == 0)
	{
		char_count++;
		ptr++;
	}
	last->value = ft_calloc(sizeof(char), char_count + 1);
	ft_strlcpy(last->value, &line[k], char_count);
	*i = k + char_count;
}

static const char	**ft_get_data_identifiers(void)
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
