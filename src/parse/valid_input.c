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

int				valid_input(int argc, char **argv, t_raw_game *raw_game)
{
    ft_putendl_fd("Checking input...", 1);
    if (argc == 2)
    {
        if (!(file_exist(argv[1])))
            return (invalid_file(1));
        if (!(ft_strncmp(argv[1], "--save", ft_strlen("--save"))))
            return (invalid_file(2));
		raw_game->need_save_first_frame = 0;
        return (SUCCESS);
    }
    if (argc == 3)
    {
        if (!(file_exist(argv[1])))
            return (invalid_file(1));
        if (!(ft_strncmp(argv[2], "--save", ft_strlen("--save"))))
            return (invalid_file(1));
		raw_game->need_save_first_frame = 1;
        return (SUCCESS);
    }
	return (invalid_file(1));
}
