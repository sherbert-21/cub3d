/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:55:27 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:55:28 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		valid_input2(char **str)
{
	int i;

	ft_putendl_fd("hui1",  1);
	i = ft_strlen(str[1]) - 1;
	if (!(ft_strncmp(str[1], "--save", 7)) ||
		(str[1][i] != 'b' || str[1][i - 1] != 'u' ||
		str[1][i - 2] != 'c' || str[1][i - 3] != '.') ||
		ft_strncmp(str[1], "--save", 7))
		return (invalid_file(1));
	return (SUCCESS);
}

int				valid_input(int c, char **str, t_win *win)
{
	int i;

	i = ft_strlen(str[1]) - 1;
	win->save = 0;
	if (c < 4 && c > 1)
	{
		if (c == 2)
		{
			if (!(ft_strncmp(str[1], "--save", 7)))
				return (invalid_file(2));
			else if (str[1][i] != 'b' || str[1][i - 1] != 'u' ||
					str[1][i - 2] != 'c' || str[1][i - 3] != '.')
				return (invalid_file(1));
		}
		if (c == 3)
		{
			i = valid_input2(str);
			if (!(ft_strncmp(str[2], "--save", 7)))
			win->save = 1;
		}
		return ((i) ? SUCCESS : ERR);
	}
	return (invalid_file(1));
}
