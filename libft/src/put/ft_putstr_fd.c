/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:36:14 by zslowian          #+#    #+#             */
/*   Updated: 2024/03/09 22:02:22 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	*ptr;

	ptr = s;
	while (*ptr != '\0')
	{
		ft_putchar_fd(*ptr, fd);
		ptr++;
	}
}

// void	ft_putstr_fd(char *s, int fd)
// {
// 	while (*s != '\0')
// 	{
// 		ft_putchar_fd((int)*s, fd);
// 		s++;
// 	}
// }
