#include "cub3d.h"

int all_comp_found(t_data *data)
{
    if (data->comp.no && data->comp.so && data->comp.es
        && data->comp.we && data->comp.ceiling != -1 && data->comp.floor != -1)
            return (1);
    return (0);
}

void    comp_error(t_data *data)
{
    if (!data->comp.no || !data->comp.so || !data->comp.es
        || !data->comp.we)
    {
        printf("Error\n");
        printf("Missing Texture\n");
    }
    else if (!data->comp.ceiling || !data->comp.floor)
    {
        printf("Error\n");
        printf("Missing Color\n");
    }
}

void    print_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}
