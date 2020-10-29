/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <sherbert@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 23:25:45 by sherbert          #+#    #+#             */
/*   Updated: 2020/09/26 23:25:55 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_strlen_err(char *str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char			*ft_strdup_err(char *s, int *ret)
{
	char	*str;
	char	*ptr;
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (!(str = (char*)malloc((i + 1) * sizeof(char))))
	{
		*ret = -1;
		return (NULL);
	}
	ptr = str;
	while (*s)
		*ptr++ = *s++;
	*ptr = '\0';
	return (str);
}

char			*ft_strjoin_err(char *s1, char *s2, int *ret)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!(str = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
	{
		*ret = -1;
		return (NULL);
	}
	while (*s1)
		str[i++] = *s1++;
	while (*s2 && *s2 != '\n')
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char			*ft_strcpy_err(char *dest, char *src)
{
	int			i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void			save_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
