/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalc_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:46:05 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/25 16:46:06 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		add_path_to_adjlist(t_adjlist *alist, t_path *path)
{
	size_t		count;
	t_roomdata	*room;
	t_roomdata	*prev;
	t_adjdata	*acur;
	t_adjdata	*aprev;

	prev = NULL;
	count = -1;
	while (ft_array_get(path, ++count, (void **)&room) == 0)
	{
		if (prev != NULL)
		{
			acur = find_adjdata_by_room(alist, room);
			aprev = find_adjdata_by_room(alist, prev);
			if (acur && aprev)
			{
				if (remove_neig_from_adjlist(acur, aprev, NULL) != RET_OK)
					add_neig_to_adjlist(aprev, acur, 1);
			}
		}
		prev = room;
	}
}

t_result		*get_all_paths(t_patharr *parr, t_adjlist *alist)
{
	t_adjdata	*start;
	t_path		*path;
	t_neigdata	*nndata;
	size_t		index;

	start = find_node_by_cmd(alist, LEM_CMD_START);
	if (!start)
		return (NULL);
	index = -1;
	while (ft_array_get(&start->neigs, ++index, (void **)&nndata) == 0)
	{
		path = ft_array_new(10);
		add_room_to_path(path, start->room);
		while (42)
		{
			add_room_to_path(path, nndata->node->room);
			if (ft_array_get(&nndata->node->neigs, 0, (void **)&nndata) != 0)
				break ;
		}
		add_path_to_arr(parr, path);
	}
	return (RET_OK);
}

t_patharr		*recalc_values(t_roomarr *rooms, t_patharr *paths, t_path *path)
{
	t_adjlist	*adjlist;
	t_path		*pdpath;
	size_t		index;
	t_patharr	*sol;

	adjlist = NULL;
	create_adjlist(&adjlist, rooms);
	index = -1;
	while (ft_array_get(paths, ++index, (void **)&pdpath) == 0)
		add_path_to_adjlist(adjlist, pdpath);
	add_path_to_adjlist(adjlist, path);
	sol = ft_array_new(10);
	if (sol)
		get_all_paths(sol, adjlist);
	delete_adjlist(&adjlist);
	return (sol);
}
