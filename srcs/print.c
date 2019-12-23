/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:18:55 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 15:18:55 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "ft_printf.h"

void	print_rooms(t_roomarr *rooms)
{
	t_roomdata	*data;
	size_t		count;

	count = -1;
	while (ft_array_get(rooms, ++count, (void **)&data) == 0)
		ft_printf("name: \"%s\", x: %d, y: %d\n", data->name, data->x, data->y);
}

void	print_links(t_linkarr *links)
{
	t_linkdata	*linkdata;
	size_t		count;

	count = -1;
	while (ft_array_get(links, ++count, (void **)&linkdata) == 0)
	{
		ft_printf("link 1: \"%s\", link2: \"%s\"\n", linkdata->left->name,
			linkdata->right->name);
	}
}

void	print_neighbors(t_adjlist *adjlist, char *title)
{
	t_adjdata		*adata;
	t_neigdata		*ndata;
	size_t			count;

	if (title)
		ft_printf("------- Stage: %s ---------\n", title);
	while (adjlist)
	{
		adata = (t_adjdata *)adjlist->content;
		ft_printf("name: \"%s\", neighbors: ", adata->room->name);
		count = -1;
		while (ft_array_get(&adata->neigs, ++count, (void **)&ndata) == 0)
			ft_printf("%s, ", ndata->node->room->name);
		adjlist = adjlist->next;
		ft_printf("len: %d\n", adata->weight);
	}
}

void	print_path(t_path *path)
{
	size_t		pcount;
	t_roomdata	*room;

	pcount = -1;
	ft_printf("path len: %d: ", ft_array_size(path));
	while (ft_array_get(path, ++pcount, (void **)&room) == 0)
	{
		if (pcount != 0)
			ft_putstr(", ");
		ft_printf("\"%s\"", room->name);
	}
	ft_putendl("");
}

void	print_paths(t_patharr *parr)
{
	size_t		count;
	t_path		*pdata;

	if (!parr)
		return ;
	count = -1;
	ft_printf("Paths number: %d\n", ft_array_size(parr));
	while (ft_array_get(parr, ++count, (void **)&pdata) == 0)
		print_path(pdata);
}
