/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:00:34 by zslowian          #+#    #+#             */
/*   Updated: 2025/05/22 12:50:36 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*data;

	data = NULL;
	if (argc != 2)
		ft_error(MAIN_ARGS, "main", data);
	else
	{
		data = ft_calloc(sizeof(t_cub3d), 1);
		if (data == NULL)
			ft_error(MEM_ERROR, "main", data);
		ft_init(argv[1], data);
	}
	ft_clean(data);
	exit(EXIT_SUCCESS);
}
