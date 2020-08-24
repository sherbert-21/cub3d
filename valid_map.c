#include "cub3d.h"

// отослать в тмп мапу i - 1 для сокращения счетчика;
// функция для чека крайних сторон
// функция для чека 1 вокруг пробелов
// рядом с пробелом может стоять пробел, единица или \0

char    **tmp_map(char **map, int i, int size)
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

int     check_square(char **tmp)
{
    int     j = -1;
    int     k = -1;
    int     er;

    while (tmp[++j])
        er = (*tmp[j] != 32 || *tmp[j] != 49 || *tmp[j] != '\n') ? 1 : 0;
    j--;
    while (tmp[j][++k])
        er = (tmp[j][k] != 32 || tmp[j][k] != 49 || tmp[j][k] != '\n') ? 1 : 0;
    k--;
    while (j >= 0)
    {
        er = (tmp[j][k] != 32 || tmp[j][k] != 49 || tmp[j][k] != '\n') ? 1 : 0;
        j--;
    }
    j++;
    while (tmp[j][k])
    {
        er = (tmp[j][k] != 32 || tmp[j][k] != 49 || tmp[j][k] != '\n') ? 1 : 0;
        k--;
    }
    return (er);
}

int     check_map(char **map, int i, int size)
{
    char    **tmp = tmp_map(map, i - 1, size);
    int     er;

    if (check_square(tmp))
        return (1);
}

int     valid_input(int argc, char **argv)
{
    if (argc > 3 || argc == 1)
        return (1);
    else
    {
        if (argc == 1)
        {
            if (ft_strnstr(argv[1], "--save", 10))
                return (2);
            else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
                return (1);
        }
        if (argc == 2)
        {
            if (ft_strnstr(argv[1], "--save", 10))
                return (1);
            else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
                return (1);
        }
    }
    return (0);
}
