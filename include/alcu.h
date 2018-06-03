/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 18:59:55 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/11 19:00:01 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCU_ALCU_H
# define ALCU_ALCU_H

# include "../libft/libft.h"

# define MES1 "Usage : ./alum1 or ./alum1 [file_name]"
# define MES2 "ERROR"

typedef struct		s_num
{
	int				n;
	struct s_num	*next;
}					t_num;

typedef struct		s_big
{
	int				rows;
	int				biggest;
	int				mode;
	int				*move;
	int				*arr;
	t_num			*list;
	char			*player;
	char			*current_name;
	char			*player2;
	char			who;
	char			won;
}					t_big;

int					is_valid_input(char *s);
void				hello(t_big *s);
int					read_map(char *file_name, t_big *s);
int					read_input(t_big *s, int fd);
t_num				*add_node(t_num *list, int n);
void				print_sticks(int n, int max);
int					list_to_arr(t_big *s);
void				priority(t_big *s);
void				algo(t_big *s);
void				takes_match(t_big *s, int i);
void				we_take(t_big *s, int i);
void				two_players(t_big *s);
void				two_takes_match(t_big *s, int i);
void				print_bad_input(t_big *s, char *line, int i);
int					last_move(t_big *s);

#endif
