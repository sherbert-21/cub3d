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
		return (invalid_file(0));
	while (file_lst)
	{
		if (!(file[i] = ft_calloc(ft_strlen(file_lst->content), sizeof(char))))
			return (invalid_file(0));
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

int				file(char **argv, t_win *win)
{
	int		fd;
	t_list	*file_lst;
	char	*line;
	int		succ;
	int		id;

	file_lst = NULL;
	id = 0;
	succ = 0;
	printf("ok");
	fd = open(argv[1], O_RDONLY);
	while (id < 8 && succ && get_next_line(fd, &line))
	{
		printf("check id");
		succ = ident_parce(line, win);
		printf("line");
		id = (succ == 1) ? id + 1 : id;
		save_free(&line);
	}
	printf("1");
	while (succ && get_next_line(fd, &line))
		ft_lstadd_back(&file_lst, ft_lstnew(line));
	ft_lstadd_back(&file_lst, ft_lstnew(line));
	printf("2");
	succ = (!(file_to_map(file_lst, ft_lstsize(file_lst), win))) ? 0 : succ;
	close(fd);
	if (succ)
		printf("YASSSS");
	return ((succ) ? SUCCESS : ERR);
}
