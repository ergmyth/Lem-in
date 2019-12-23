/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_all_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 07:08:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 07:08:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "ft_printf.h"

static t_path	*get_last_shortest_path(t_adjlist *alist)
{
	t_adjdata	*end;
	t_path		*path;

	path = NULL;
	end = find_node_by_cmd(alist, LEM_CMD_END);
	if (end)
	{
		if (end->prev)
		{
			path = ft_array_new(10);
			if (path)
			{
				while (end)
				{
					ft_array_insert(path, end->room, 0);
					end = end->prev;
				}
			}
		}
	}
	return (path);
}

static int		is_last_path_correct(t_adjlist *alist)
{
	t_adjdata	*end;

	end = find_node_by_cmd(alist, LEM_CMD_END);
	if (end)
	{
		if (end->prev)
		{
			while (end)
			{
				if (end->prev == NULL || end->room->cmd == LEM_CMD_START)
					return (1);
				end = end->prev;
			}
		}
	}
	return (0);
}

static int		path_cmp(const void *d1, const void *d2)
{
	t_path	*p1;
	t_path	*p2;

	p1 = *(t_path **)d1;
	p2 = *(t_path **)d2;
	return ((int)ft_array_size(p1) - (int)ft_array_size(p2));
}

static int		try_new_path(t_lemin *lem, int *prev_len, t_patharr **prev_sol,
	t_patharr **one_sol)
{
	t_path		*newp;
	int			len;
	t_patharr	*newsol;

	newp = get_last_shortest_path(lem->adjm);
	newsol = recalc_values(&lem->rooms, *prev_sol, newp);
	delete_path(&newp);
	ft_bubble_sort(newsol->data, newsol->num_elems,
		sizeof(*newsol->data), path_cmp);
	len = calc_total_len(newsol, lem->num_ants);
	if (len < *prev_len)
	{
		remove_all_paths(prev_sol);
		*one_sol = newsol;
		*prev_len = len;
	}
	else
		return (0);
	*prev_sol = newsol;
	return (1);
}

t_result		find_all_paths(t_lemin *lem)
{
	t_patharr	*sol;
	t_path		*path;
	int			prev_len;
	t_patharr	*onesol;
	int			bf_updated;

	sol = ft_array_new(10);
	path = get_last_shortest_path(lem->adjm);
	add_path_to_arr(sol, path);
	prev_len = calc_total_len(sol, lem->num_ants);
	onesol = sol;
	while (42)
	{
		suurballe_algo(&lem->adjm);
		bf_updated = bellman_ford(lem->adjm);
		if (bf_updated && is_last_path_correct(lem->adjm))
		{
			if (!try_new_path(lem, &prev_len, &sol, &onesol))
				break ;
		}
		else
			break ;
	}
	lem->paths = onesol;
	return (RET_OK);
}
