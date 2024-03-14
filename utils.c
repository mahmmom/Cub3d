#include "cub3d.h"

char *join_args(char **str)
{
    int i;
    char *color;
    char *temp;

    if (!str || !*str)
        return (NULL);
    i = 0;
    color = ft_strdup(""); // Initialize color to an empty string
    while (str[i])
    {
        temp = ft_strjoin(color, str[i]);
        free(color);
        color = temp;
        i++;
    }
    //free_array(str);
    return (color);
}

int check_args(char **str)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int	convert_to_integer(char **components)
{
    int red; 
	int	green;
	int	blue;
    // Assuming the RGB components are in the format "R,G,B"
    // You can customize this parsing according to your input format
	// Convert each component to integer using atoi function
	red = ft_atoi(components[0]);
	green = ft_atoi(components[1]);
	blue = ft_atoi(components[2]);
	// Ensure each component is in the valid range (0-255)
	if (red < 0 || red > 255 || green < 0 || green > 255
		|| blue < 0 || blue > 255)
	{
		// Handle invalid RGB values
		return (-1); // Or any other error code you prefer
	}
	// Combine the RGB components into a single integer
	return ((red << 16) | (green << 8) | blue);
}

int ft_atoi_rgb(t_data *data, char **str)
{
    char	**temp;
    char	*color;
	int		result;

    color = join_args(str);
    temp = ft_split(color, ',');
    free(color);
    if (!temp)
        return (error_handler(ERROR_Color, data), 1);
    if (check_args(temp) == 0)
    {
        free_array(temp);
        return (error_handler(ERROR_Color, data), 1);
    }
	result = convert_to_integer(temp);
    // Convert color to integer here
    // Example: result = convert_to_integer(temp);
    free_array(temp); // Free memory allocated for temp
    return (result);
}

