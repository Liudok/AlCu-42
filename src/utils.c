/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <lberezyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 23:10:24 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/10 23:33:29 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/alcu.h"

void		two_takes_match(t_big *s, int i)
{
	char *line;

	ft_putstr(GREEN_FONT);
	ft_putstr(s->current_name);
	ft_putstr(", please take 1 to ");
	if (s->arr[i] >= 3)
		ft_putendl("3 matches");
	else if (s->arr[i] == 2)
		ft_putendl("2 matches");
	else if (s->arr[i] == 1)
		ft_putendl("1 match");
	ft_putstr(COLOR_OFF);
	if (get_next_line(0, &line) == 1)
	{
		(ft_atoi(line) > 3 || ft_atoi(line) < 1 || ft_atoi(line) > s->arr[i] ||
		!is_valid_input(line)) ? print_bad_input(s, line, i) :
		(s->arr[i] -= ft_atoi(line));
		free(line);
	}
	if (s->arr[i] <= 0)
		s->won = '1';
	if (!ft_strcmp(s->current_name, s->player))
		s->current_name = s->player2;
	else
		s->current_name = s->player;
}

void		two_players(t_big *s)
{
	int		i;
	int		j;

	i = -1;
	s->biggest = 0;
	while (++i < s->rows)
		if (s->biggest < s->arr[i])
			s->biggest = s->arr[i];
	i = -1;
	while (++i < s->rows)
		print_sticks(s->arr[i], s->biggest);
	i = s->rows - 1;
	while (i >= 0)
	{
		two_takes_match(s, i);
		j = -1;
		while (++j < s->rows)
			print_sticks(s->arr[j], s->biggest);
		if (s->arr[i] <= 0)
			i--;
	}
	ft_putstr(RED_FONT);
	ft_putstr(s->current_name);
	ft_putendl("! You are the champion! Congratulations!");
	ft_putstr(COLOR_OFF);
}

void		print_sticks(int n, int max)
{
	int		i;
	int		white;

	i = 0;
	if (n % 2 == 0 && n)
		write(1, " ", 1);
	white = (max / 2 - n / 2) * 2;
	while ((i++ < white) && n)
	{
		write(1, " ", 1);
	}
	i = 0;
	while (i++ < n)
	{
		write(1, "|", 1);
		write(1, " ", 1);
	}
	if (n)
		write(1, "\n", 1);
}

int			list_to_arr(t_big *s)
{
	int		i;
	t_num	*cur;
	t_num	*tmp;

	hello(s);
	ft_putendl("Type numbers from 1 to 10000 and press ENTER.");
	ft_putendl("Then press one more ENTER or ctrl+D");
	if ((read_input(s, 0)) == 0)
	{
		ft_putendl_fd(MES2, 2);
		free(s->player);
		free(s->player2);
		return (-1);
	}
	i = s->rows - 1;
	cur = s->list;
	s->arr = (int *)malloc(sizeof(int) * s->rows);
	while (cur)
	{
		tmp = cur;
		s->arr[i--] = cur->n;
		cur = cur->next;
		free(tmp);
	}
	return (1);
}

void		hello(t_big *s)
{
	char	*name;

	ft_putstr(BLUE_FONT);
	ft_putendl("Hello, player! Let's get started!\nWhat is your name?");
	if ((get_next_line(0, &name)) == 1)
		s->player = ft_strdup(name);
	free(name);
	ft_putendl("If you want to play against other player press 2");
	ft_putendl("If you want to play against bot press ENTER");
	if (get_next_line(0, &name) == 1)
	{
		if (is_valid_input(name))
			s->mode = (ft_atoi(name) == 2) ? 2 : 1;
		else
			s->mode = 1;
	}
	free(name);
	if (s->mode == 2)
	{
		ft_putendl("What is the name of second player?");
		if (get_next_line(0, &name) == 1)
			s->player2 = ft_strdup(name);
		free(name);
	}
	ft_putstr(COLOR_OFF);
}
