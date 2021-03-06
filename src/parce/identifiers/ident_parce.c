/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ident_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:25:25 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 19:24:04 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void		skip_space(t_list **lst)
{
	int		i;
	char	*file;

	while (*lst)
	{
		i = -1;
		if (!(file = ft_strdup((*lst)->content)))
			err_exit(2);
		while (file[++i] == ' ' || file[++i] == '\n')
			i++;
		if (file[i] == '\0')
		{
			save_free(&file);
			ft_lstdelone(*lst, save_free);
			*lst = (*lst)->next;
			continue;
		}
		else
		{
			save_free(&file);
			break ;
		}
	}
}

static void		set_ident(char *ident_str, t_cub *cub)
{
	while (*ident_str == ' ')
		ident_str++;
	if (*ident_str == 'R')
	{
		ft_putstr_fd("\t\t\t\tResolution:\t", 1);
		resolution(++ident_str, cub);
	}
	else if (*ident_str == 'F' || *ident_str == 'C')
	{
		if (*ident_str == 'C')
			ft_putstr_fd("\t\t\t\tColor of celling:", 1);
		else
			ft_putstr_fd("\t\t\t\tColor of floor:", 1);
		color(ident_str, cub);
	}
	else
		texture(ident_str, cub);
}

static int		ident_check(char *ident_str)
{
	int i;

	i = 0;
	while (ident_str[i] == ' ')
		i++;
	if (ident_str[i] == '\n' || ident_str[i] == '\0')
		return (NEXT);
	else if (ft_strchr("RSFC", ident_str[i]) && ident_str[i + 1] == ' ')
		return (SUCCESS);
	else if (ft_strchr("SN", ident_str[i]) && ident_str[i + 1] == 'O')
		return (SUCCESS);
	else if (ident_str[i] == 'W' && ident_str[i + 1] == 'E')
		return (SUCCESS);
	else if (ident_str[i] == 'E' && ident_str[i + 1] == 'A')
		return (SUCCESS);
	else
		err_exit(4);
	return (ERR);
}

void			parce_ident(t_list **file_lst, t_cub *cub)
{
	int		ident;
	char	*file;

	ident = 0;
	while (ident != 8 && *file_lst)
	{
		if (!(file = ft_strdup((*file_lst)->content)))
			err_exit(2);
		if (ident_check(file) == 1)
		{
			set_ident(file, cub);
			ident++;
		}
		save_free(&file);
		ft_lstdelone(*file_lst, save_free);
		*file_lst = (*file_lst)->next;
	}
	ft_putstr_fd("\n\t", 1);
	if (ident != 8)
		err_exit(3);
	skip_space(file_lst);
	if (!(*file_lst) && ident == 8)
		err_exit(4);
}
