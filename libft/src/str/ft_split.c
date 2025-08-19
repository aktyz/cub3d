/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/03/24 16:17:37 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/24 16:17:37 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_allocate_word(char const *s, char c);
static char		**ft_allocate_words(char const *s, char c, char **ptr);
static size_t	ft_count_words(char const *s, char c);
static size_t	ft_word_length(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		nb_words;

	nb_words = (ft_count_words(s, c) + 1);
	ptr = malloc(nb_words * sizeof(char *));
	if (!ptr)
		return (0);
	ptr = ft_allocate_words(s, c, ptr);
	if (!ptr)
	{
		ft_clear_char_array(&ptr, nb_words);
		return (0);
	}
	return (ptr);
}

static char	*ft_allocate_word(char const *s, char c)
{
	char	*word;
	size_t	k;

	k = 0;
	word = (char *)malloc(ft_word_length(s, c) + 1);
	if (!word)
		return (0);
	while (s[k] && s[k] != c)
	{
		word[k] = s[k];
		k++;
	}
	word[k] = '\0';
	return (word);
}

static char	**ft_allocate_words(char const *s, char c, char **ptr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			ptr[j] = ft_allocate_word(s + i, c);
			if (ptr[j] == 0)
			{
				while (j--)
					free(ptr[j]);
				free(ptr);
				return (0);
			}
			i += ft_word_length(s + i, c);
			j++;
		}
		else
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	nb_words;
	size_t	i;

	nb_words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			nb_words++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (nb_words);
}

static size_t	ft_word_length(char const *s, char c)
{
	size_t	length;

	length = 0;
	while (s[length] && s[length] != c)
		length++;
	return (length);
}

/* static void	ft_assign_vars(size_t *i, int *j, int *s);
static void	*ft_free(char **strs, int count);
static int	ft_word_count(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	int		j;
	int		word_start;

	ft_assign_vars(&i, &j, &word_start);
	result = ft_calloc((ft_word_count(s, c) + 1), sizeof(char *));
	if (!result)
		return (0);
	while (i <= ft_strlen((char *)s))
	{
		if (s[i] != c && word_start < 0)
			word_start = i;
		else if ((s[i] == c || i == ft_strlen((char *)s))
			&& word_start >= 0)	
			j++;
		}
		i++;
	}
	return (result);
}

static void	ft_assign_vars(size_t *i, int *j, int *s)
{
	*i = 0;
	*j = 0;
	*s = -1;
}

static void	*ft_free(char **strs, int count)
{
	while (count > 0)
	{
		free(strs[count]);
		count--;
	}
	free(strs);
	return (0);
}

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;
	int	is_word;

	count = 0;
	i = 0;
	is_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && is_word == 0)
		{
			is_word = 1;
			count++;
		}
		else if (s[i] == c)
			is_word = 0;
		i++;
	}
	return (count);
}
	*/