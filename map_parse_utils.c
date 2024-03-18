#include "cub3d.h"

int all_map_comp(t_data *data)
{

}


int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v'
			&& line[i] != '\f' && line[i] != '\r' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
