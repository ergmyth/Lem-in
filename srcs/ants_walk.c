/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:28:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 16:28:05 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "ants_walk.h"
#include "ft_printf.h"

static void	print_move(t_roomdata *cur, int *is_not_first, int colorized)
{
	if (*is_not_first)
		ft_putstr(" ");
	*is_not_first = 1;
	if (colorized)
	{
		ft_printf("\x1b[38;5;%dmL%d-%s\x1b[0m", cur->ant_index % 255,
			cur->ant_index, cur->name);
	}
	else
		ft_printf("L%d-%s", cur->ant_index, cur->name);
}

static int	push_one_move(t_push_move *pm, int *is_not_first,
	const size_t *sum, int is_colorized)
{
	if (pm->prev->ant_count)
	{
		if (pm->prev->cmd == LEM_CMD_START)
		{
			if (pm->index != 0 && pm->prev->ant_count <=
			(int)((ft_array_size(pm->path) - 1) * pm->index) - (int)*sum)
				return (1);
			pm->cur->ant_index = pm->num_ants - pm->prev->ant_count + 1;
		}
		else
			pm->cur->ant_index = pm->prev->ant_index;
		pm->cur->ant_count++;
		pm->prev->ant_count--;
		print_move(pm->cur, is_not_first, is_colorized);
	}
	return (0);
}

static int	push_one_path(size_t index, t_lemin *lem,
	int *is_not_first, size_t *sum)
{
	t_push_move		pm;
	size_t			i;

	pm.index = index;
	pm.num_ants = lem->num_ants;
	if (lem->paths)
	{
		if (ft_array_get(lem->paths, index, (void **)&pm.path) == 0)
		{
			i = ft_array_size(pm.path);
			while (i > 1)
			{
				i--;
				if (ft_array_get(pm.path, i, (void **)&pm.cur) == 0 &&
					ft_array_get(pm.path, i - 1, (void **)&pm.prev) == 0)
				{
					if (push_one_move(&pm, is_not_first, sum, lem->is_colorize))
						break ;
				}
			}
			*sum = *sum + (ft_array_size(pm.path) - 1);
		}
	}
	return (0);
}

void		print_solution(t_lemin *lem)
{
	size_t		path_count;
	size_t		count;
	size_t		total_size;
	int			is_not_first;

	lem->se.start->ant_count = lem->num_ants;
	if (lem->paths)
	{
		while (lem->se.end->ant_count != lem->num_ants)
		{
			count = 0;
			total_size = 0;
			is_not_first = 0;
			path_count = ft_array_size(lem->paths);
			while (count < path_count)
			{
				push_one_path(count, lem, &is_not_first, &total_size);
				count++;
			}
			ft_putendl("");
		}
	}
}
