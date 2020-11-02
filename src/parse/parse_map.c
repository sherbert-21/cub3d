#include "cub3d.h"

/*
** Needed for malloc(), free() and write(). Also for typedef size_t and sizeof()
*/

# include <unistd.h>
# include <stdlib.h>

/*
** Macro for the buffer size, the max number of file descriptors available, and
** to get the correct return value from the gnl_read_file() function.
** Find the max number of files:
** Mac: launchctl limit maxfiles
** Linux: ulimit -n
*/

# define BUFF_SIZE 8
# define MAX_FD 1024 + 1
# define RET_VALUE(ret)	ret > 0 ? 1 : ret

/*
** Prototype for the get_next_line() function.
*/

/*
** Allocates sufficient memory for a copy of the string s1, does the copy,
** and returns a pointer to it.
*/

static char			*f_strdup(const char *s1)
{
	char		*s2;
	size_t		i;

	i = 0;
	while (s1[i])
		i += 1;
	if (!(s2 = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}

/*
** Allocates with malloc() and returns a “fresh” string ending with ’\0’,
** result of the concatenation of s1 and s2. If the allocation fails the
** function returns NULL.
*/

static char			*f_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	char		*tmp_s3;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	while (s1[i])
		i += 1;
	while (s2[j])
		j += 1;
	if (!s1 || !s2 || !(s3 = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	tmp_s3 = s3;
	while (*s1 != '\0')
		*tmp_s3++ = *s1++;
	while (*s2 != '\0')
		*tmp_s3++ = *s2++;
	*tmp_s3 = '\0';
	return (s3);
}

/*
** Verify if whatever is in the stack, has a newline. If it doesn't, returns
** a zero (0) to indicate that it's not valid. If there is a newline, we make a
** copy of the stack into the line, and we copied whatever was in the stack
** before, back to the stack (with the temporary stack that we created).
*/

static int			gnl_verify_line(char **stack, char **line)
{
	char			*tmp_stack;
	char			*strchr_stack;
	int				i;

	i = 0;
	strchr_stack = *stack;
	while (strchr_stack[i] != '\n')
		if (!strchr_stack[i++])
			return (0);
	tmp_stack = &strchr_stack[i];
	*tmp_stack = '\0';
	*line = ft_strdup(*stack);
	*stack = ft_strdup(tmp_stack + 1);
	return (1);
}

/*
** Reads into the heap, from the file descriptors, a specific number of bytes
** defined by the BUFF_SIZE macro in the get_nex_line.h file. It's going to
** continue the reading when the return value of the read function is greater
** than zero (no errors, or if there is nothing else to read).
** If there is something in the stack, we will concatinate whatever is in
** there, with whatever is read in the heap. If no, we will just add
** whatever is in the heap into the stack. Then we will verify the stack to
** see if there is a newline. If there is, we will break from the while loop
** and force the positive ret value into a one (1), using the RET_VALUE() macro.
** This answer form SO helped me visualize the stack and heap in a better way:
** http://stackoverflow.com/a/1213360
*/

static	int			gnl_read_file(int fd, char *heap, char **stack, char **line)
{
	int				ret;
	char			*tmp_stack;

	while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
	{
		heap[ret] = '\0';
		if (*stack)
		{
			tmp_stack = *stack;
			*stack = f_strjoin(tmp_stack, heap);
			free(tmp_stack);
			tmp_stack = NULL;
		}
		else
			*stack = f_strdup(heap);
		if (gnl_verify_line(stack, line))
			break ;
	}
	return (RET_VALUE(ret));
}

/*
** This is where the real shit happens.
** It first checks for errors (is the line is empty, if the number of the file
** descriptor is invalid, or if it fails to allocate the heap), so it can return
** a minus one (-1) if needed.
**
** If there is something in the stack (because we are using a static variable),
** we verify that there is a newline. If not, we allocate memory for the heap,
** and we read the file.
**
** When the reading of the file ends, we will free the heap (we're not gonna
** use it anymore), and we check for the value of ret (if it's 1 or -1, return
** that, if the stack is empty, return 0). If neither of these conditions are
** valid, we assing line to the value of the stack, free the stack, and return 1
**
** A good read about file descriptors:
** http://www.bottomupcs.com/file_descriptors.xhtml
*/

int					get_line(int const fd, char **line)
{
	static char		*stack[MAX_FD];
	char			*heap;
	int				ret;
	int				i;

	if (!line || (fd < 0 || fd >= MAX_FD) || (read(fd, stack[fd], 0) < 0) \
		|| !(heap = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	if (stack[fd])
		if (gnl_verify_line(&stack[fd], line))
			return (1);
	i = 0;
	while (i < BUFF_SIZE)
		heap[i++] = '\0';
	ret = gnl_read_file(fd, heap, &stack[fd], line);
	free(heap);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}

static t_list          *read_file(int fd, char *first_map_line, t_raw_game *raw_game)
{
    char    *line;
    int     current_line_size;
    t_list *head;
    t_list *node;

    head = NULL;
    if (!(node = ft_lstnew(first_map_line)))
    	return NULL;
    ft_lstadd_back(&head, node);
	raw_game->map_h = 1;
    while (get_line(fd, &line)) //TODO NEED TO CHANGE GNL
    {
        current_line_size = ft_strlen(line);
        if (current_line_size > raw_game->map_w)
            raw_game->map_w = current_line_size;
		if (!(node = ft_lstnew(line)))
			return NULL;
		ft_lstadd_back(&head, node);
        raw_game->map_h++;
    }

    return head;
}

static int 				set_cell(t_raw_game *raw_game, char symbol, int y, int x)
{
	if (symbol == ' ')
		raw_game->map[y][x] = 7;
	else if (symbol >= '0' && symbol <= '2')
		raw_game->map[y][x] = symbol - '0';
	else if (symbol == 'N' || symbol == 'S' || symbol == 'E' || symbol == 'W')
	{
		raw_game->map[y][x] = 0;
		raw_game->hero_y = y;
		raw_game->hero_x = x;
		raw_game->hero_dir_x = 0;
		raw_game->hero_dir_y = 0;
		if (symbol == 'N')
			raw_game->hero_dir_y = -1;
		else if (symbol == 'S')
			raw_game->hero_dir_y = 1;
		else if (symbol == 'W')
			raw_game->hero_dir_x = -1;
		else
			raw_game->hero_dir_x = 1;
	}
	else
		return 0;
	return 1;
}

static int				char_map_to_int(t_list *head, t_raw_game *raw_game)
{
    int     x;
    int     y;
    char    *line;

    if (!(raw_game->map = (int**)malloc(sizeof(int*) * raw_game->map_h)))
        return invalid_file(1);
    y = -1;
    while (head)
    {
        if (!(raw_game->map[++y] = (int*)malloc(sizeof(int) * raw_game->map_w)))
			return invalid_file(1);
        line = (char *)head->content;
        x = -1;
        while (++x < raw_game->map_w)
		{
        	if (x >= ft_strlen(line))
        		raw_game->map[y][x] = 7;
			else if (!set_cell(raw_game, line[x], y, x))
				return invalid_file(3);
		}
        head = head->next;
    }
    return 1;
}

static int             check_map_closed(t_raw_game *raw_game)
{
    int     y;
    int     x;

    y = -1;
    while (++y < raw_game->map_h)
    {
        x = -1;
        while (++x < raw_game->map_w)
        {
			if (raw_game->map[y][x] == 0)
			{
				if (x == 0 || y == 0 || x == raw_game->map_w - 1 || y == raw_game->map_h)
					return invalid_file(3);
				if (raw_game->map[y][x + 1] == 7 || raw_game->map[y + 1][x] == 7)
					return invalid_file(3);
			}
			else if (raw_game->map[y][x] == 7)
			{
				if (x < raw_game->map_w - 1 && raw_game->map[y][x + 1] == 0)
					return invalid_file(3);
				if (y < raw_game->map_h - 1 && raw_game->map[y + 1][x] == 0)
					return invalid_file(3);
				raw_game->map[y][x] = 1;
			}
        }
    }
    return 1;
}

int						parse_map(int fd, char *first_map_line, t_raw_game *raw_game)
{
    t_list *char_map_list;
	t_list *tmp;

    if (!(char_map_list = read_file(fd, first_map_line, raw_game)))
        return invalid_file(1);
    if (!(char_map_to_int(char_map_list, raw_game)))
    	return 0;
    while (char_map_list)
	{
    	free(char_map_list->content);
    	tmp = char_map_list;
    	char_map_list = char_map_list->next;
    	free(tmp);
	}
 	return check_map_closed(raw_game);
}
