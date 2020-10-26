#include "cub3d.h"

void    free_str(char ***str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
		save_free(&str[i]);
		str[i] = NULL;
        i++;
	}
}