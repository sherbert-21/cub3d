#include "cub3d.h"

static int		valid_identifier(char *ident, t_win *win)
{
	int i;

	i = 0;
	while (ident[i] == ' ')
		i++;
	if (ft_strchr("RSF", ident[i]) && ident[i + 1] == ' ')
		return (SUCCESS);
	else if (ft_strchr("SN", ident[i]) && ident[i + 1] == 'O')
		return (SUCCESS);
	else if (ident[i] == 'W' && ident[i + 1] == 'E')
		return (SUCCESS);
	else if (ident[i] == 'E' && ident[i + 1] == 'A')
		return (SUCCESS);
	else
		return (invalid_file(1, win));
}

static int		identifier_parce(char *ident, t_win *win)
{
	int i;

	i = 0;
	while (ident[i] == ' ')
		i++;
	if (ident[i] == 'R')
		return (resolution(++ident, win));
	else if (ident[i] == 'F' || ident[i] == 'C')
		return (color(ident, ident[i], i, win));
	else
		return (texture(ident, win));
}

static int		file_parce(char **file, t_win *win, int size)
{
	int i;
	int succ;

	i = 0;
	succ = 1;
	while (succ && file[i] && file[i][0] != ' ' && file[i][0] != '1')
	{
		while (file[i][0] == '\n')
			i++;
		if ((succ = valid_identifier(file[i], win)))
			succ = (!(identifier_parce(file[i++], win))) ? 0 : succ;
	}
	return (succ || map_parce(file, i, size, win));
}

static int		lst_to_str(t_list *file_lst, int size, t_win *win)
{
	char	**file;
	int		i;
	int 	k;
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
	succ = file_parce(file, win, size);
	free_str(&file);
	return (succ);
}

int				file(int argc, char **argv, t_win *win)
{
	int		fd;
	t_list	*file_lst;
	char	*line;
	int		succ;

	file_lst = NULL;
	succ = valid_input(argc, argv, win);
	if (succ)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line))
			ft_lstadd_back(&file_lst, ft_lstnew(line));
		ft_lstadd_back(&file_lst, ft_lstnew(line));
		succ = (!(lst_to_str(file_lst, ft_lstsize(file_lst), win))) ? 0 : succ;
	}
	ft_lstclear(&file_lst, free);
	return (succ);
}
