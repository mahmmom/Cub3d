#include "cub3d.h"
#include "libft/libft.h"

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
    while (str[i])
    {
        printf("map line = [%s]\n", str[i]);
        i++;
    }
}

void get_map(t_data *data)
{
    int i = -1;
    char **temp_map = NULL; // Temporary map to hold the dynamically allocated map

    while ((data->comp.file.line = get_next_line(data->comp.file.fd)) != NULL)
    {
        remove_newline(&data->comp.file.line);
        data->comp.file.f_2d = ft_split(data->comp.file.line, ' ');
       // free(data->comp.file.line);
        if (!data->comp.file.f_2d || !*data->comp.file.f_2d || data->comp.file.f_2d[0][0] == '\0')
        {
            free_array(data->comp.file.f_2d);
            continue;
        }
        if (is_map_char(data->comp.file.f_2d[0]) == 1)
        {
            // Reallocate memory for the map
            temp_map = (char **)ft_realloc(temp_map, i * sizeof(char *), (i + 2) * sizeof(char *));
            if (temp_map == NULL)
            {
                // Handle memory allocation failure
                error_handler("Memory allocation failed", data);
                // You might also want to free resources allocated before exiting
                // For example, free_array(data->comp.file.f_2d);
                return;
            }
            temp_map[++i] = ft_strdup(data->comp.file.line);
            printf("Line = [%s]\n", temp_map[i]);
            free(data->comp.file.line);
        }
        else
            error_handler("Invalid Map", data);
    }
    // Now, we know the size of the map, so update the data structure
    data->comp.map.map_2d = temp_map;
    //print_array(data->comp.map.map_2d);
    data->comp.map.map_h = i + 1; // Number of rows
    //data->comp.map.map_w = get_map_width(temp_map, i + 1); // Assuming you have a function to get map width
}
