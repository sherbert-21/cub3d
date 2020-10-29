/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:53:30 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:53:31 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				resolution(char *ident, int i, t_win *win)
{
	while (ident[i] == ' ' && ident[i])
		i++;
	if (ident[i] == '0' || !ident[i])
		return (invalid_file(5));
	win->x = ft_atoi(&ident[i]);
	while (ft_isdigit(ident[i]))
		i++;
	while (ident[i] == ' ' && ident[i])
		i++;
	if (ident[i] == '0' || !ident[i])
		return (invalid_file(5));
	win->y = ft_atoi(&ident[i]);
	while (ft_isdigit(ident[i]))
		i++;
	while (ident[i] == ' ' && ident[i])
		i++;
	if (ident[i])
		return (invalid_file(5));
	return (SUCCESS);
}
