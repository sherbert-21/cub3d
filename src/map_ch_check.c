/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ch_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 04:47:33 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/31 04:47:35 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_square(char **tmp, t_win *win)
{
    unsigned long	j;
    unsigned long	k;
    int				succ;

    j = -1;
    succ = 1;
    k = 0;
    while (++j < win->size && succ)
        succ = (ft_strchr(" 1", tmp[j][0])) ? 1 : 0;
    while (++k < win->len && succ)
        succ = (ft_strchr(" 1", tmp[j - 1][k])) ? 1 : 0;
    while (--j > 0 && succ)
        succ = (ft_strchr(" 1", tmp[j][k - 1])) ? 1 : 0;
    succ = (ft_strchr(" 1", tmp[j][k - 1])) ? 1 : 0;
    while (--k > 0 && succ)
        succ = (ft_strchr(" 1", tmp[j][k])) ? 1 : 0;
    succ = (ft_strchr(" 1", tmp[j][k])) ? 1 : 0;
    return (succ);
}

int		check_symbol(char **tmp, int j, int k, t_win *win)
{
    if (tmp[j][k] == ' ')
    {
        if (ft_strchr(" 1", tmp[j + 1][k]) ||
            ft_strchr(" 1", tmp[j - 1][k]) ||
            ft_strchr(" 1", tmp[j][k + 1]) ||
            ft_strchr(" 1", tmp[j][k - 1]))
            return (SUCCESS);
    }
    else if (ft_strchr("012NSWE", tmp[j][k]))
        return (SUCCESS);
    return (invalid_file(3, win));
}
