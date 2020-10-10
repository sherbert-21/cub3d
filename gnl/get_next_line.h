/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <sherbert@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:25:58 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/07 14:58:26 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

void	save_free(char **str);
int		ft_strlen_err(char *str);
char	*ft_strdup_err(char *s1, int *err);
char	*ft_strjoin_err(char *s1, char *s2, int *err);
char	*ft_strcpy_err(char *dest, char *src);
char	*ft_strchr_err(const char *s, int c);
int		get_next_line(int fd, char **line);
void	error_case(char **s_buf, char **line, int *ret);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
#endif
