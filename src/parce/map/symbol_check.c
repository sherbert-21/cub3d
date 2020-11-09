/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:06:01 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 15:07:55 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void		check_square(char **tmp, t_cub *cub)
{
	int k;
	int j;
	int ok;

	j = -1;
	k = -1;
	while (++j < cub->map_y && ok)
		ok = (tmp[j][0] == '1' ||
				(tmp[j][0] == ' ' && ft_strchr(" 1", tmp[j][1]))) ? 1 : 0;
	while (++k < cub->map_x && ok)
		ok = (tmp[j - 1][k] == '1' ||
		(tmp[j - 1][k] == ' ' && ft_strchr(" 1", tmp[j - 2][k]))) ? ok : 0;
	while (--j > 0 && ok)
		ok = (tmp[j][k - 1] == '1' ||
		(tmp[j][k - 1] == ' ' && ft_strchr(" 1", tmp[j][k - 2]))) ? ok : 0;
	ok = (tmp[j][k - 1] == '1' ||
		(tmp[j][k - 1] == ' ' && ft_strchr(" 1", tmp[j][k - 2]))) ? ok : 0;
	while (--k > 0 && ok)
		ok = (tmp[j][k] == '1' ||
		(tmp[j][k] == ' ' && ft_strchr(" 1", tmp[j + 1][k]))) ? ok : 0;
	ok = (tmp[j][k] == '1' ||
		(tmp[j][k] == ' ' && ft_strchr(" 1", tmp[j + 1][k]))) ? ok : 0;
	if (!ok)
		err_exit(9);
}

void		check_symbol(char **tmp, int j, int k)
{
	if (tmp[j][k] == ' ')
	{
		if (!(ft_strchr(" 1", tmp[j + 1][k])) ||
			!(ft_strchr(" 1", tmp[j - 1][k])) ||
			!(ft_strchr(" 1", tmp[j][k + 1])) ||
			!(ft_strchr(" 1", tmp[j][k - 1])))
			err_exit(9);
	}
	else if (!(ft_strchr("012NSWE", tmp[j][k])))
		err_exit(10);
}
