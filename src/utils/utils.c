int		ft_strisnum(char *str) //COPIED FROM MY LIBFT
{
    if (!str || !*str)
        return (0);
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (0);
        str++;
    }
    return (1);
}

int	ft_numwords(char const *s, char c) //COPIED FROM ft_split
{
    int words;
    int if_word;

    words = 0;
    if_word = 1;
    while (*s)
    {
        if (*s == c)
            if_word = 1;
        else if (if_word == 1)
        {
            if_word = 0;
            words++;
        }
        s++;
    }
    return (words);
}
