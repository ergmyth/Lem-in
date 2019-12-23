/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neigs_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:25:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/23 21:25:18 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

t_adjlist		*add_adjdata(t_adjlist **adjlist, t_roomdata *room)
{
	t_adjlist	*lst;
	t_adjdata	*data;

	lst = ft_lstaddblank(adjlist, sizeof(t_adjdata));
	if (lst)
	{
		data = (t_adjdata *)lst->content;
		ft_array_init(&data->neigs, 64);
		data->room = room;
	}
	return (lst);
}

t_result		add_neig_to_adjlist(t_adjdata *adata, t_adjdata *neig,
	int weight)
{
	t_neigdata	*ndata;

	ndata = (t_neigdata *)ft_memalloc(sizeof(*ndata));
	if (!ndata)
		return (ERR_ENOMEM);
	ndata->weight = weight;
	ndata->node = neig;
	if (ft_array_add(&adata->neigs, ndata))
	{
		ft_memdel((void **)&ndata);
		return (ERR_ENOMEM);
	}
	return (RET_OK);
}

t_adjdata		*find_adjdata_by_room(t_adjlist *adjlist, t_roomdata *room)
{
	t_adjdata	*adata;

	adata = NULL;
	while (adjlist)
	{
		adata = (t_adjdata *)adjlist->content;
		if (adata->room == room)
			return (adata);
		adjlist = adjlist->next;
	}
	return (adata);
}

t_result		remove_neig_from_adjlist(t_adjdata *from, t_adjdata *what,
	int *weigth)
{
	t_neigdata	*ndata;
	int			count;
	size_t		index;

	count = 0;
	index = -1;
	while (ft_array_get(&from->neigs, ++index, (void **)&ndata) == 0)
	{
		if (ndata->node == what)
		{
			if (weigth)
				*weigth = ndata->weight;
			if (ft_array_remove(&from->neigs, index, free) == 0)
			{
				index--;
				count++;
			}
		}
	}
	return (count == 1 ? RET_OK : ERR_NO_LINK_TO_DEL);
}
