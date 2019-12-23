/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 10:38:38 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/24 10:38:45 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	update_bf(t_adjlist *adj)
{
	t_adjdata	*adjdata;
	t_neigdata	*ndata;
	int			visited;
	size_t		index;

	visited = 0;
	while (adj)
	{
		adjdata = (t_adjdata *)adj->content;
		index = -1;
		while (ft_array_get(&adjdata->neigs, ++index, (void **)&ndata) == 0)
		{
			if (adjdata->weight != WEIGHT_MAX &&
				adjdata->weight + ndata->weight < ndata->node->weight)
			{
				ndata->node->weight = adjdata->weight + ndata->weight;
				ndata->node->prev = adjdata;
				visited = 1;
			}
		}
		adj = adj->next;
	}
	return (visited);
}

int			bellman_ford(t_adjlist *adjlist)
{
	size_t		size;
	t_adjdata	*adjdata;
	int			visited;
	int			updated;

	reset_adjlist_values(adjlist);
	adjdata = find_node_by_cmd(adjlist, LEM_CMD_START);
	adjdata->weight = 0;
	visited = 1;
	updated = 0;
	size = ft_lstsize(adjlist);
	while (size > 1 && visited)
	{
		visited = update_bf(adjlist);
		if (visited)
			updated = 1;
		size--;
	}
	return (updated);
}
