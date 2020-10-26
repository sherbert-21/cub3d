#include "cub3d.h"

static int	data_to_bmp(t_pic *screen, int fd)
{
	int i;

	i = screen->width * screen->height - 1;
	while (i >= 0)
	{
		write(fd, &screen->data[i * screen->bpp / 8], 4);
		i--;
	}
	return (SUCK);
}

static void	vert_pixel(t_pic *screen, int i, int *e, int f)
{
	char	save;
	int		k;

	k = 3;
	while (k >= 0)
	{
		save = screen->data[*e + (i * screen->size)];
		screen->data[*e + (i * screen->size)] =
			screen->data[f - k + (i * screen->size - 1)];
		screen->data[f - k + (i * screen->size - 1)] =
			save;
		k--;
		*e = *e + 1;
	}
}

static int	vert(t_pic *screen)
{
	int		i;
	int		e;
	int		f;

	i = 0;
	while (i < screen->height)
	{
		e = 0;
		f = screen->size;
		while (e < f && e != f)
		{
			vert_pixel(screen, i, &e, f);
			f -= 4;
		}
		i++;
	}
	return (SUCK);
}

static int	bmp_info_header(t_pic *screen, int fd)
{
	int size;
	int nbr;
	int o_count;

	size = 40;
	nbr = 1;
	write(fd, &size, 4);
	write(fd, &screen->width, 4);
	write(fd, &screen->height, 4);
	write(fd, &nbr, 2);
	write(fd, &screen->bpp, 2);
	o_count = 0;
	while (o_count < 28)
	{
		write(fd, "\0", 1);
		o_count++;
	}
	return (SUCK);
}

int			create_bmp(t_pic *screen, char *name)
{
	int fd;
	int size;
	int first_pix;

	name = ft_strjoin(name, ".bmp");
	fd = open(name, O_CREAT | O_RDWR);
	size = 14 + 40 + 4 + (screen->width * screen->height) * 4;
	first_pix = 14 + 40 + 4;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	bmp_info_header(screen, fd);
	vert(screen);
	data_to_bmp(screen, fd);
	close(fd);
	free(name);
	return (SUCK);
}
