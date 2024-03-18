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

// int map_comp(t_data *data, char *line)
// {

// }

/*void get_map(t_data *data, int fd)
{
    int     i;
    char    **temp_map;
    char    *line;

    i = 0;
    line = get_next_line(fd);
    temp_map = NULL;
    while (line)
	{
		while (line && is_empty_line(line))
	    {
		    ft_free((void **)&line);
		    line = get_next_line(fd);
	    }
		if (*line && map_comp(data, line) != CORRECT)
			return (close(fd), free(line));
		// ft_free((void **)&map_line);
		line = get_next_line(fd);
        if (is_map_char())
        {
            temp_map = (char **)ft_realloc(temp_map, i * sizeof(char *), (i + 2) * sizeof(char *));
            if (temp_map == NULL)
                return (error_exit(MALLOC_ERR));
            temp_map[i] = ft_strdup();
            i++;
        }
        else
            error_exit(MAP_CHAR_ERR);
        line = get_next_line(fd);
    }
  	if (!all_map_comp(data))
	    return (close(fd), comp_error(data));
}*/
