#include "cub3d.h"
#include "libft/libft.h"

void    get_map(t_data *data)
{
    int i;

    i = -1;
    while ((data->comp.file.line = get_next_line(data->comp.file.fd)) != NULL)
    {
        remove_newline(&data->comp.file.line);
        data->comp.file.f_2d = ft_split(data->comp.file.line, ' ');
        free(data->comp.file.line);
        if (!data->comp.file.f_2d || !*data->comp.file.f_2d || data->comp.file.f_2d[0][0] == '\0')
        {
            free_array(data->comp.file.f_2d);
            continue;
        }
        if (is_map_char(data->comp.file.f_2d[0]) == 1)
        {
            data->map2d[++i] = ft_strdup(data->comp.file.line);
        }
        else
            error_handler("Invalid Map", data);
    }
}