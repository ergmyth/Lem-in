/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:02:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 10:02:36 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <unistd.h>
#include <stdlib.h>

static void	remove_pathlst_callback(void *data)
{
	(void)data;
}

static void	remove_pdata(void *data)
{
	t_path		*path;

	path = (t_path *)data;
	ft_array_delete_all(&path, remove_pathlst_callback);
}

void		remove_all_paths(t_patharr **parr)
{
	ft_array_delete_all(parr, remove_pdata);
}

void		delete_all(t_lemin *lem)
{
	delete_adjlist(&lem->adjm);
	ft_array_remove_all(&lem->rooms, free);
	ft_array_remove_all(&lem->links, free);
	remove_all_paths(&lem->paths);
	ft_array_remove_all(&lem->strarr, free);
	if (lem->fd != 0)
		close(lem->fd);
}
