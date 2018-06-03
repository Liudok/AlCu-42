/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <lberezyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 23:35:27 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/10 23:35:27 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/alcu.h"

void		ask_who(t_big *s)
{
	char	*line;

	ft_putstr(YELLOW_FONT);
	ft_putendl("Do you want to make first move? [y/n]");
	ft_putstr(COLOR_OFF);
	if (get_next_line(0, &line) == 1)
	{
		if (!ft_strcmp("y", line))
			s->who = 0;
		else if (!ft_strcmp("n", line))
			s->who = 1;
		else
		{
			ft_putstr(RED_FONT);
			ft_putendl("Bad input. Try again. Type \"y\" or \"n\" ");
			ft_putstr(COLOR_OFF);
			ask_who(s);
		}
		free(line);
	}
	s->won = 'S';
}

int			start_game(t_big *s, int ret)
{
	if (ret == 1 && s->arr[0] != 0 && s->mode == 1)
		ask_who(s);
	if (ret == 0 || s->arr[0] == 0)
	{
		ft_putendl_fd(MES2, 2);
		free(s->player);
		free(s->player2);
		return (1);
	}
	s->current_name = s->player;
	if (s->mode == 2)
	{
		two_players(s);
		free(s->arr);
	}
	else
	{
		priority(s);
		free(s->move);
		free(s->arr);
	}
	free(s->player);
	free(s->player2);
	return (0);
}

int			main(int ac, char **av)
{
	t_big	s;
	int		ret;

	s.rows = 0;
	if (ac > 2)
	{
		ft_putendl_fd(MES1, 2);
		return (1);
	}
	if (ac == 2)
		if ((ret = read_map(av[1], &s)) == 1)
			hello(&s);
	if (ac == 1)
		if ((ret = list_to_arr(&s)) == -1)
			return (1);
	return (start_game(&s, ret));
}

void		priority(t_big *s)
{
	int		i;

	i = s->rows - 1;
	s->move = (int *)malloc(sizeof(int) * s->rows);
	s->move[i] = ((s->arr[i] - 1) % 4 == 0) ? 2 : 1;
	i--;
	while (i >= 0)
	{
		s->move[i] = ((s->arr[i] - 1) % 4 == 0) ? 2 : 1;
		if (s->move[i + 1] == 2)
			s->move[i] = (s->move[i] == 2) ? 1 : 2;
		i--;
	}
	i = 0;
	s->biggest = 0;
	while (i < s->rows)
	{
		if (s->biggest < s->arr[i])
			s->biggest = s->arr[i];
		i++;
	}
	i = -1;
	while (++i < s->rows)
		print_sticks(s->arr[i], s->biggest);
	algo(s);
}

void		print_bad_input(t_big *s, char *line, int i)
{
	ft_putstr(RED_FONT);
	ft_putstr(line);
	ft_putendl(" - is a Bad input. Try again.");
	ft_putstr(COLOR_OFF);
	takes_match(s, i);
}
