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

static int      file_exist(char *str)
{
    int fd;
    int i;

    i = (int)ft_strlen(str) - 1;
    fd = open(str, O_RDONLY);
    if (fd < 0 || (str[i - 3] != '.' || str[i - 2] != 'c'
                || str[i - 1] != 'u' || str[i] != 'b'))
        i = -1;
    close(fd);
    return((i != -1) ? SUCCESS : ERR);
}

int				valid_input(int c, char **str, t_win *win)
{
    if (c == 2)
    {
        if (!(file_exist(str[1])))
            return (invalid_file(1));
        if (!(ft_strncmp(str[2], "--save", ft_strlen("--save"))))
            return (invalid_file(2));
        win->save = 0;
        return (SUCCESS);
    }
    if (c == 3)
    {
        if (!(file_exist(str[1])))
            return (invalid_file(1));
        if (!(ft_strncmp(str[2], "--save", ft_strlen("--save"))))
            return (invalid_file(1));
        win->save = 1;
        return (SUCCESS);
    }
	return (invalid_file(1));
}
