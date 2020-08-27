#include "cub3d.h"

static char     **tmp_map(char **map, int i, int size)
{
    int     len = 0;
    char    **tmp;
    int     k = 0;
    int     j = i;

    while (map[++j])
        len = (len < ft_strlen(map[j])) ? ft_strlen(map[j]) : len;
    tmp = ft_calloc(size - i + 1, sizeof(char *));
    while (map[++i])
    {
        j = 0;
        tmp[k] = ft_calloc(len + 1, sizeof(char));
        while (map[i][j])
        {
            tmp[k++][j] = map[i][j];
            j++;
        }
        while (j < len)
            tmp[k][j++] = ' ';
        k++;
    }
    return (tmp);
}

static int      check_square(char **tmp)
{
    int     j = -1;
    int     k = -1;
    int     e = 0;

    while (tmp[++j])
        e = (*tmp[j] != 32 || *tmp[j] != 49 || *tmp[j] != '\n') ? 1 : e;
    j--;
    while (tmp[j][++k])
        e = (tmp[j][k] != 32 || tmp[j][k] != 49 || tmp[j][k] != '\n') ? 1 : e;
    k--;
    while (j >= 0)
    {
        e = (tmp[j][k] != 32 || tmp[j][k] != 49 || tmp[j][k] != '\n') ? 1 : e;
        j--;
    }
    j++;
    while (k >= 0)
    {
        e = (tmp[j][k] != 32 || tmp[j][k] != 49 || tmp[j][k] != '\n') ? 1 : e;
        k--;
    }
    return (e);
}

int             check_map(char **map, int i, int size)
{
    char    **tmp = tmp_map(map, i - 1, size);
    int     err = 0;
    int     j = i;
    int     k;
    int     player = 0;

    err = (check_square(tmp)) ? 1 : er;
    while (++j < size - 1)
    {
        k = 0;
        while (++k < ft_strlen(tmp[j]) - 1)
        {
            if (tmp[j][k] == 32)
            {
                if (!ft_strchr(" 1", tmp[j + 1][k]) ||
                    !ft_strchr(" 1", tmp[j - 1][k]) ||
                    !ft_strchr(" 1", tmp[j][k + 1]) ||
                    !ft_strchr(" 1", tmp[j][k - 1]))
                    err = 1;
            }
            player = (ft_strchr("NSWE", tmp[j][k])) ? player + 1 : player;
        }
    }
    err = (player != 1) ? 1 : err;
    return (err);
}

int             valid_input(int argc, char **argv)
{
    if (argc > 3 || argc == 1)
        return (1);
    else
    {
        if (argc == 1)
        {
            if (ft_strnstr(argv[1], "--save", ft_strlen("--save")))
                return (2);
            else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
                return (1);
        }
        if (argc == 2)
        {
            if (ft_strnstr(argv[1], "--save", ft_strlen("--save")))
                return (1);
            else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
                return (1);
        }
    }
    return (0);
}
