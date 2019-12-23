/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:55:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/21 15:55:52 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		make_link_neg(t_adjdata *from, t_adjdata *to)
{
	t_neigdata	*ndata;
	size_t		size;

	size = ft_array_size(&from->neigs);
	while (size--)
	{
		if (ft_array_get(&from->neigs, size, (void **)&ndata) == 0)
		{
			if (ndata->node == to)
				ndata->weight = -ndata->weight;
		}
	}
}

static void		copy_values(t_adjdata *out, t_adjdata *in, t_adjdata *next)
{
	t_neigdata	*ndata;
	size_t		index;

	out->weight = in->weight;
	out->room = in->room;
	out->dij_vis = in->dij_vis;
	index = -1;
	while (ft_array_get(&in->neigs, ++index, (void **)&ndata) == 0)
	{
		if (ndata->node != next)
		{
			if (ft_array_remove(&in->neigs, index, NULL) == 0)
			{
				ft_array_add(&out->neigs, ndata);
				index--;
			}
		}
	}
}

static void		make_duples(t_adjlist **root, t_adjdata *prev,
	t_adjdata *data, t_adjdata *next)
{
	t_adjdata	*out;
	t_adjlist	*newlst;
	int			weigth;

	if (next)
	{
		newlst = add_adjdata(root, NULL);
		if (newlst)
		{
			out = (t_adjdata *)newlst->content;
			copy_values(out, data, next);
			add_neig_to_adjlist(out, data, 0);
			if (remove_neig_from_adjlist(prev, data, &weigth) == RET_OK)
				add_neig_to_adjlist(prev, out, weigth);
		}
	}
}

void			suurballe_algo(t_adjlist **root)
{
	t_adjdata	*prev;
	t_adjdata	*cur;
	t_adjdata	*next;

	prev = find_node_by_cmd(*root, LEM_CMD_END);
	if (!prev)
		return ;
	if ((cur = prev->prev))
	{
		while (cur)
		{
			next = cur->prev;
			remove_neig_from_adjlist(cur, prev, NULL);
			make_link_neg(prev, cur);
			if (cur->room->cmd == LEM_CMD_START)
				break ;
			make_duples(root, prev, cur, next);
			prev = cur;
			cur = next;
		}
	}
}
