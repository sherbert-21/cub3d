/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:51:44 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:51:45 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		file_skip_space(char **file, int size, t_win *win)
{
	int i;
	int k;

	i = -1;
	while (file[++i])
	{
		k = 0;
		while (file[i][k] == ' ' && file[i][k])
			k++;
		if (file[i][k] == '\n' || file[i][k] == '\0')
			continue;
		else
			break;
	}
	return (map_parce(file, i , size, win));
}

static int		file_to_map(t_list *file_lst, int size, t_win *win)
{
	char	**file;
	int		i;
	int		succ;

	i = 0;
	if (!(file = ft_calloc(size + 1, sizeof(char *))))
		return (invalid_file(0, win));
	while (file_lst)
	{
		if (!(file[i] = ft_calloc(ft_strlen(file_lst->content), sizeof(char))))
			return (invalid_file(0, win));
		file[i++] = file_lst->content;
		file_lst = file_lst->next;
	}
	succ = file_skip_space(file, size, win);
	i = -1;
	while (file[++i])
	{
		save_free(&file[i]);
		file[i] = NULL;
	}
	file = NULL;
	return (succ);
}

int				file(char *argv, t_win *win)
{
	t_list	*file_lst;
	char	*line;
	int		succ;
	int		id;
	int     fd;

    ft_putendl_fd("OK\nChecking file...", 1);
	file_lst = NULL;
	id = 0;
	succ = ((fd = open(argv, O_RDONLY)) > 0) ? 1 : 0;
	while (id < 8 && succ && get_next_line(fd, &line))
	{
		succ = ident_parce(line, win);
		id = (succ == 1) ? id + 1 : id;
		save_free(&line);
	}
	while (succ && get_next_line(fd, &line))
		ft_lstadd_back(&file_lst, ft_lstnew(line));
	ft_lstadd_back(&file_lst, ft_lstnew(line));
	succ = (!(file_to_map(file_lst, ft_lstsize(file_lst), win))) ? 0 : succ;
	if (succ && win->save == 0)
        ft_putendl_fd("OK\nCreating new window...", 1);
	return ((succ) ? SUCCESS : ERR);
}
