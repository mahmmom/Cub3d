#include "cub3d.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void    *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    if (ptr == NULL)
        return (malloc(new_size));
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
    {
        free(ptr);
        return (NULL);
    }
    ft_memcpy(new_ptr, ptr, old_size); // Copy old data
    free(ptr); // Free the old pointer
    return (new_ptr);
}

void    print_array(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        printf("map line = %s\n", str[i]);
        i++;
    }
}


void get_map(t_data *data)
{
    int i;
    char **temp_map;

    temp_map = NULL;
    i = 0;
    while (data->comp.file.line != NULL)
    {
        remove_newline(&data->comp.file.line);
        data->comp.file.f_2d = ft_split(data->comp.file.line, ' ');
        if (!data->comp.file.f_2d || !*data->comp.file.f_2d || data->comp.file.f_2d[0][0] == '\0')
        {
            free_array(data->comp.file.f_2d);
            //free(data->comp.file.line);
            data->comp.file.line = get_next_line(data->comp.file.fd);
            continue;
        }
        if (is_map_char(data->comp.file.f_2d))
        {
            temp_map = (char **)ft_realloc(temp_map, i * sizeof(char *), (i + 2) * sizeof(char *));
            if (temp_map == NULL)
            {
                error_handler("Memory allocation failed", data);
                return;
            }
            temp_map[i] = ft_strdup(data->comp.file.line);
            i++;
        }
        else
            error_handler("Invalid Char", data);
        free(data->comp.file.line);
        free_array(data->comp.file.f_2d);
        data->comp.file.line = get_next_line(data->comp.file.fd);
    }
    temp_map[i] = NULL;
    data->comp.map.map_2d = temp_map;
	//print_array(data->comp.map.map_2d);
    data->comp.map.map_h = i;
    // Now that data->comp.map.map_2d has the allocated memory,
    // we can safely free temp_map
    free_array(temp_map);
}

