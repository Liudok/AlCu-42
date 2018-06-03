/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <lberezyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 22:50:29 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/10 23:34:37 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/alcu.h"

int			last_move(t_big *s)
{
	int		ret;

	if (s->arr[0] % 4 == 1 || s->arr[0] % 4 == 2)
		ret = 1;
	else if (s->arr[0] % 4 == 3)
		ret = 2;
	else if (s->arr[0] % 4 == 0)
		ret = 3;
	return (ret);
}

void		we_take(t_big *s, int i)
{
	int ret;

	if (i - 1 < 0)
		ret = last_move(s);
	else
	{
		if (s->arr[i] % 4 == 1)
			ret = 1;
		else if (s->arr[i] % 4 == 2)
			ret = (s->move[i - 1] == 1) ? 1 : 2;
		else if (s->arr[i] % 4 == 3)
			ret = (s->move[i - 1] == 1) ? 2 : 3;
		else if (s->arr[i] % 4 == 0)
			ret = (s->move[i - 1] == 1) ? 3 : 1;
	}
	s->arr[i] -= ret;
	ft_putstr(YELLOW_FONT);
	ft_putstr("Bot took ");
	ft_putnbr(ret);
	write(1, "\n", 1);
	ft_putstr(COLOR_OFF);
	if (s->arr[i] <= 0)
		s->won = '0';
	s->who = 0;
}

void		takes_match(t_big *s, int i)
{
	char	*line;

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
		!is_valid_input(line) || *line == '0') ? print_bad_input(s, line, i) :
		(s->arr[i] -= ft_atoi(line));
		free(line);
	}
	if (s->arr[i] <= 0)
		s->won = '1';
	s->who = 1;
}

void		algo(t_big *s)
{
	int		i;
	int		j;

	i = s->rows - 1;
	while (i >= 0)
	{
		if (s->who == 0)
			takes_match(s, i);
		else
			we_take(s, i);
		j = -1;
		while (++j < s->rows)
			print_sticks(s->arr[j], s->biggest);
		if (s->arr[i] <= 0)
			i--;
	}
	ft_putstr(RED_FONT);
	if (s->won == '1')
		ft_putendl("You have lost the game..");
	else if (s->won == '0')
	{
		ft_putstr(s->current_name);
		ft_putendl("! You are the champion! Congratulations!");
	}
	ft_putstr(COLOR_OFF);
}

t_num		*add_node(t_num *list, int n)
{
	t_num	*new;

	if (!(new = (t_num*)malloc(sizeof(t_num))))
		return (NULL);
	new->n = n;
	new->next = NULL;
	if (list)
		new->next = list;
	return (new);
}
