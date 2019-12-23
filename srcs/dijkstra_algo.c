/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 09:40:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 09:40:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_adjdata	*find_min_weight(t_adjlist *adjlist)
{
	t_adjdata	*min;
	t_adjdata	*cur;

	min = NULL;
	while (adjlist)
	{
		cur = (t_adjdata *)adjlist->content;
		if (cur->weight != WEIGHT_MAX && !cur->dij_vis)
		{
			if (min == NULL || cur->weight < min->weight)
				min = cur;
		}
		adjlist = adjlist->next;
	}
	return (min);
}

void				reset_adjlist_values(t_adjlist *adjlist)
{
	t_adjdata	*adjdata;

	while (adjlist)
	{
		adjdata = (t_adjdata *)adjlist->content;
		adjdata->weight = WEIGHT_MAX;
		adjdata->dij_vis = 0;
		adjdata->prev = NULL;
		adjlist = adjlist->next;
	}
}

t_adjdata			*find_node_by_cmd(t_adjlist *adjlist, int cmd)
{
	t_adjdata	*adata;

	while (adjlist)
	{
		adata = (t_adjdata *)adjlist->content;
		if (adata->room->cmd == cmd)
			return (adata);
		adjlist = adjlist->next;
	}
	return (NULL);
}

t_result			dijkstra_algo(t_adjlist *adjlist)
{
	t_adjdata		*adata;
	t_neigdata		*ndata;
	size_t			index;

	reset_adjlist_values(adjlist);
	adata = find_node_by_cmd(adjlist, LEM_CMD_START);
	adata->weight = 0;
	while ((adata = find_min_weight(adjlist)) != NULL)
	{
		index = -1;
		while (ft_array_get(&adata->neigs, ++index, (void **)&ndata) == 0)
		{
			if (adata->weight + ndata->weight < ndata->node->weight)
			{
				ndata->node->weight = adata->weight + ndata->weight;
				ndata->node->prev = adata;
			}
		}
		adata->dij_vis = 1;
	}
	return (RET_OK);
}
