#include "cub3d.h"

int	texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int array_size(char **str)
{
    int i;

    if (!str || !*str)
        return (-1);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	comp_exist(char **array, char *str)
{
	if (ft_strcmp(array[0], str) == 0)
		return (1);
	return (0);
}

int	count_commas(char *str)
{
	int	i;
	int	commas_count;

	i = 0;
	commas_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas_count++;
		i++;
	}
	return (commas_count);
}
