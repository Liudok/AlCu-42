/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 12:00:04 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/10 23:32:45 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/alcu.h"

int			is_valid_input(char *s)
{
	int		i;

	i = 0;
	if (!*s)
		return (0);
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int			ft_open_file(t_big *s, char *file_name)
{
	int		fd;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		free(line);
		s->rows++;
	}
	free(line);
	close(fd);
	return (1);
}

int			map_content(t_big *s, int fd, int ret)
{
	char	*line;
	int		i;

	i = -1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (is_valid_input(line))
		{
			s->arr[++i] = ft_atoi(line);
			free(line);
			if (s->arr[i] > 10000 || s->arr[i] < 1)
			{
				free(s->arr);
				return (0);
			}
		}
		else
		{
			free(s->arr);
			free(line);
			return (0);
		}
	}
	free(line);
	return ((ret < 0) ? 0 : 1);
}

int			read_map(char *file_name, t_big *s)
{
	int		fd;
	int		ret;

	if (ft_open_file(s, file_name))
	{
		if ((fd = open(file_name, O_RDONLY)) < 0)
			return (0);
		s->arr = (int *)malloc(sizeof(int) * s->rows);
		ret = map_content(s, fd, 1);
		if (ret == 0)
		{
			close(fd);
			return (0);
		}
		close(fd);
		return (1);
	}
	return (0);
}

int			read_input(t_big *s, int fd)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		if (is_valid_input(line))
		{
			s->list = add_node(s->list, ft_atoi((const char *)line));
			free(line);
			if (s->list->n == 0 || s->list->n > 10000 || s->list == NULL)
				return (0);
			s->rows++;
		}
		else if (*line == 0)
		{
			free(line);
			return (1);
		}
		else
		{
			free(line);
			return (0);
		}
	}
	return (1);
}
