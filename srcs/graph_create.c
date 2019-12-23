/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:40:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/06 09:40:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

static t_result	get_opposite_roomlink(
	t_linkarr *larr, t_roomdata *room, int n, t_linkdata *link)
{
	t_linkdata	*ldata;
	size_t		index;

	index = -1;
	while (ft_array_get(larr, ++index, (void **)&ldata) == 0)
	{
		if (room == ldata->left || room == ldata->right)
		{
			if (!n--)
			{
				link->right = room == ldata->left ?
					ldata->right : ldata->left;
				return (RET_OK);
			}
		}
	}
	return (ERR_WRONG_LINK);
}

t_adjlist		*create_adjlist(t_list **adjlist, t_roomarr *rooms)
{
	size_t		index;
	t_roomdata	*room;

	index = -1;
	while (ft_array_get(rooms, ++index, (void **)&room) == 0)
		add_adjdata(adjlist, room);
	return (*adjlist);
}

static void		del_one_adj(void *data, size_t size)
{
	t_adjdata *adata;

	(void)size;
	adata = (t_adjdata *)data;
	ft_array_remove_all(&adata->neigs, free);
	ft_memdel(&data);
}

void			delete_adjlist(t_list **adjlist)
{
	ft_lstdel(adjlist, del_one_adj);
}

t_result		graph_create(t_lemin *lem)
{
	size_t		size;
	t_linkdata	link;
	t_adjdata	*adata;
	t_adjdata	*neig;
	t_adjlist	*adjlist;

	adjlist = create_adjlist(&lem->adjm, &lem->rooms);
	while (adjlist)
	{
		adata = (t_adjdata *)adjlist->content;
		size = 0;
		link.left = adata->room;
		while ((get_opposite_roomlink(
			&lem->links, adata->room, size++, &link)) == RET_OK)
		{
			neig = find_adjdata_by_room(lem->adjm, link.right);
			if (neig)
				add_neig_to_adjlist(adata, neig, 1);
		}
		adjlist = adjlist->next;
	}
	dijkstra_algo(lem->adjm);
	return (RET_OK);
}
