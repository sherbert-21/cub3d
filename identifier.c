#include "cub3d.h"

static int     texture(char *ident, t_ident *parse)
{
    
}

static int     resolution(char *ident, t_ident *parse)
{
    while (*ident == ' ' && *ident)
        ident++;
    if (*ident == '0' || !*ident)
        return(1);
    parse.x = ft_atoi(ident);
    while (*ident == ' ' && *ident)
        ident++;
    if (*ident == '0' || !*ident)
        return(1);
    parse.y = ft_atoi(ident);
    while (*ident == ' ' && *ident)
        ident++;
    if (*ident)
        return(1);
    return(0);
}

static int     color(char *ident, t_ident *parse)
{
    char clr[11];
    int  i = 0;
    int  err = 0;

    while (*ident == ' ' && *ident)
        ident++;
    err = ((ft_atoi(ident) > 255 || ft_atoi(ident) < 0) || !*ident) ? 1 : 0;
    while (*ident != ' ' && *ident != ',')
        clr[i++] = *ident++;
    while ((*ident == ' ' || *ident == ',') && *ident)
        ident++;
    err = ((ft_atoi(ident) > 255 || ft_atoi(ident) < 0) || !*ident) ? 1 : 0;
    while (*ident != ' ' && *ident != ',')
        clr[i++] = *ident++;
    while ((*ident == ' ' || *ident == ',') && *ident)
        ident++;
    err = ((ft_atoi(ident) > 255 || ft_atoi(ident) < 0) || !*ident) ? 1 : 0;
    while (*ident != ' ' && *ident != ',')
        clr[i++] = *ident++;
    while ((*ident == ' ' && *ident)
        ident++;
    err = (*ident) ? 1 : 0;
    (ident(0) == 'C' && err == 0) ?  parse.c_color = clr : parse.f_color = clr;
    return(err);
}

static int     identifier(char *ident, t_ident *parse)
{
    if (ident[0] == 'R')
        return(resolution(++ident), parse);
    else if (ident[0] == 'F' || ident[0] == 'C')
        return(color(ident, parse));
    else
        return(texture(ident, parse));
}

int     valid_identifier(char *ident, t_ident *parse)
{
    if (ft_strchr("RSF", ident[0]) && ident[1] == ' ')
        return(identifier(ident, parse));
    else if (ft_strchr("SN", ident [0]) && ident[1] == 'O')
        return(identifier(ident, parse));
    else if (ident[0] == 'W' && ident[1] == 'E')
        return(identifier(ident, parse));
    else if (ident[0] == 'E' && ident[1] == 'A')
        return(identifier(ident, parse));
    else
        return(1);
}
