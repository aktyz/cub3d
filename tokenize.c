/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:10:04 by zslowian          #+#    #+#             */
/*   Updated: 2025/06/15 13:35:17 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				ft_tokenize(t_cub3d *data);
void				ft_add_token(int *i, char *line, t_cub3d *data);
bool				ft_is_data_identifier(int *i, char *line, t_cub3d *data);
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

	is_id = ft_is_data_identifier(i, line, data);
	if (is_id)
		return ;
	ft_add_word(i, line, data);
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
	char	**data_ids;
	t_token	*new_token;
	int		j;

	data_ids = ft_get_data_identifiers();
	j = -1;
	while (++j < DATA_ID_NB)
	{
		if (ft_strncmp(line[*i], data_ids[j], ft_strlen(data_ids[j])) == 0) // the id is found
		{
			new_token = ft_calloc(sizeof(t_token), 1);
			if (new_token == NULL)
				ft_error(MEM_ERROR, "ft_is_data_identifier", data);
			new_token->data_id = ft_strdup(data_ids[j]);
			if (data->tokens == NULL)
				data->tokens = ft_lstnew((void *) new_token);
			else
				ft_lstadd_back(&data->tokens, ft_lstnew((void *) new_token));
			*i += ft_strlen(data_ids[j]);
			return (true);
		}
	}
	return (false);
}

/**
 * Function add's the data value to the token list if there's
 * list node with data_id type created.
 * If not, it checks if it's already the map content and then
 * add it as map content - line by line.
 */
void	ft_add_word(int *i, char *line, t_cub3d *data)
{
	t_token	*content;
	t_list	*last;
	char	*ptr;
	int		char_count;

	if (data->tokens == NULL)
		ft_error(INVALID_MAP, "ft_add_word", data);
	last = ft_lstlast(data->tokens);
	content = (t_token *) last->content;
	if (content->data_id == NULL
		|| (content->data_id == NULL && content->value != NULL)
		|| (content->data_id == NULL && content->value == NULL))
		ft_error(INVALID_MAP, "ft_add_word", data);
	ptr = line[*i];
	char_count = 0;
	while (ft_isspace(line[*ptr]) == 0)
	{
		char_count++;
		ptr++;
	}
	content->value = ft_calloc(sizeof(char), char_count + 1);
	ft_strlcpy(content->value, line[*i], char_count);
	*i += char_count;
}

static const char	**ft_get_data_identifiers(void)
{
	static const char	*data_identifiers[DATA_ID_NB];

	data_identifiers[0] = "NO"
	data_identifiers[1] = "SO";
	data_identifiers[2] = "WE";
	data_identifiers[3] = "EA";
	data_identifiers[4] = "F";
	data_identifiers[5] = "C";
	return (data_identifiers);
}
