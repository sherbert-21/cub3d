#include "cub3d.h"

int     valid_identifier(char *ident)
{
    if (ft_strchr("RSF", ident[0]) && ident[1] == ' ')
        return(identifier(ident));
    else if (ft_strchr("SN", ident [0]) && ident[1] == 'O')
        return(identifier(ident));
    else if (ident[0] == 'W' && ident[1] == 'E')
        return(identifier(ident));
    else if (ident[0] == 'E' && ident[1] == 'A')
        return(identifier(ident));
    else
        return(1);
}

int     identifier(char *ident)
{
    if (ident[0] == 'R')
        return(resolution(++ident));
    else if (ident[0] == 'F' || ident[0] == 'C')
        return(color(ident));
    else
        return(texture(ident));
}

int     texture(char *ident)
{

}

int     resolution(char *ident)
{
    while (*ident == ' ' && *ident)
        ident++;
    if (*ident == '0' || !*ident)
        return(1);
    t_ident.x = ft_atoi(ident);
    while (*ident == ' ' && *ident)
        ident++;
    if (*ident == '0' || !*ident)
        return(1);
    t_ident.y = ft_atoi(ident);
    while (*ident == ' ' && *ident)
        ident++;
    if (*ident)
        return(1);
    return(0);
}

int     color(char *ident)
{

}
