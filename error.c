/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:26:36 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/14 15:47:44 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	if(!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	free_data(t_data *data)
{
	//free_array(data->comp.file.f_2d);
	//cu_free_2d(data->comp.map.map_2d);
	// if (data->comp.file.line)
	// 	free(data->comp.file.line);
	if (data->comp.no)
		free(data->comp.no);
	if (data->comp.so)
		free(data->comp.so);
	if (data->comp.we)
		free(data->comp.we);
	if (data->comp.es)
		free(data->comp.es);
}

void	error_handler(char *msg, t_data *data)
{
	printf("Error\n");
	printf("%s\n", msg);
	free_data(data);
	if (data->comp.file.fd > 0)
		close(data->comp.file.fd);
	exit (1);
}

// void get_map_textures(t_data *data)
// {
// 	char	*line;
// 	int		len;
// 	char	*texture_value ;

//     while ((data->comp.file.line = get_next_line(data->comp.file.fd)) != NULL)
//     {
//         remove_newline(&data->comp.file.line);
//         line = data->comp.file.line;
//         len = ft_strlen(line);
//         if (len == 0)
// 		{
//             free(line);
//             continue ;
//         }
//         // Check for texture identifiers (NO, SO, EA, WE)
//         if (len >= 2 && (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line,
// 			"SO", 2) == 0 ||
// //                          ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line,
// 		"WE", 2) == 0))
//         {
//             // Process texture line
//             texture_value = line + 2; // Skip texture identifier
//             // Update data structure with texture value
//             if (ft_strncmp(line, "NO", 2) == 0 && data->comp.no == NULL)
//                 data->comp.no = ft_strdup(texture_value);
//             else if (ft_strncmp(line, "SO", 2) == 0 && data->comp.so == NULL)
//                 data->comp.so = ft_strdup(texture_value);
//             else if (ft_strncmp(line, "EA", 2) == 0 && data->comp.es == NULL)
//                 data->comp.es = ft_strdup(texture_value);
//             else if (ft_strncmp(line, "WE", 2) == 0 && data->comp.we == NULL)
//                 data->comp.we = ft_strdup(texture_value);
//         }
//         else if (len >= 1 && (line[0] == 'C' || line[0] == 'F'))
//         {
//             // Process color line
//             // Update data structure with color value
//             if (line[0] == 'C' && data->comp.ceiling == -1)
//                 data->comp.ceiling = ft_atoi_rgb(data, &line+1);
//             else if (line[0] == 'F' && data->comp.floor == -1)
//                 data->comp.floor = ft_atoi_rgb(data, &line+1);
//         }
//         else
//         {
//             // Invalid line, handle error or ignore
//             error_handler("Invalid Texture/Color identifier", data);
//         }
//         free(line); // Free the original line
//     }
// }