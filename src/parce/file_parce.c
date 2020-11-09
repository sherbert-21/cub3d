/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:12:20 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 14:15:57 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	file_parce(int argc, char **argv, t_cub *cub)
{
	t_list	*file;
	t_list	*top;
	char	*line;
	int		fd;

	ft_putstr_fd("\tChecking input...", 1);
	valid_input(argc, argv, cub);
	line = NULL;
	file = NULL;
	if (!(fd = open(argv[1], O_RDONLY)))
		err_exit(1);
	ft_putendl_fd("\t\t\t\t\tOK", 1);
	while (get_next_line(fd, &line))
		ft_lstadd_back(&file, ft_lstnew(line));
	ft_lstadd_back(&file, ft_lstnew(line));
	top = file;
	ft_putendl_fd("\tChecking file...", 1);
	ft_putendl_fd("\tIdentifiers:", 1);
	parce_ident(&file, cub);
	ft_putstr_fd("Map:", 1);
	parce_map(&file, cub);
	ft_putendl_fd("\t\t\t\t\t\t\t\tOK", 1);
}
