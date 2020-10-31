/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:48:04 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:48:06 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		get_rgb_from_clr(int r, int g, int b)
{
	int clr;

	clr = r;
	clr = (clr << 8) + g;
	clr = (clr << 8) + b;
	return (clr);
}

static int		get_num_clr(char *str)
{
	int clr;

	clr = ft_atoi(str);
	if (clr < 0 || clr > 255)
		return (-1);
	return (clr);
}

int				parse_ceilling_floor_color(char **splitted_line, t_raw_game *raw_game)
{
	char	**splitted_nums;
	int		r;
	int 	g;
	int 	b;

	splitted_nums = ft_split(splitted_line[1], ',');

	if (ft_numwords(splitted_line[1], ',') != 3 ||
		!ft_strisnum(splitted_nums[0]) || !ft_strisnum(splitted_nums[1]) || !ft_strisnum(splitted_nums[2]))
		return (invalid_file(7));

	if ((r = get_num_clr(str, &i)) == -1
		|| (g = get_num_clr(str, &i)) == -1
		|| (b = get_num_clr(str, &i)) == -1)
		return (invalid_file(7, win));
	clr = get_rgb_from_clr(r, g, b);
	if (c == 'F')
		win->clr_f = clr;
	else if (c == 'C')
		win->clr_c = clr;
}
