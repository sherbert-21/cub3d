/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <sherbert@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:25:58 by sherbert          #+#    #+#             */
/*   Updated: 2020/07/26 23:26:01 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

void	save_free(char **str);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1, int *err);
char	*ft_strjoin(char *s1, char *s2, int *err);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
int		get_next_line(int fd, char **line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
#endif
