/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <sherbert@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:22:25 by sherbert          #+#    #+#             */
/*   Updated: 2020/05/18 23:22:26 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *lst_new;

	if (!*lst)
		*lst = new;
	else if (*lst && new)
	{
		lst_new = ft_lstlast(*lst);
		lst_new->next = new;
	}
}
