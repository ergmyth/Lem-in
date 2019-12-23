/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:48:32 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/15 09:48:32 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result	add_path_to_arr(t_patharr *parr, t_path *path)
{
	if (ft_array_add(parr, path) != 0)
		return (ERR_ENOMEM);
	return (RET_OK);
}

t_result	add_room_to_path(t_path *path, t_roomdata *room)
{
	return (ft_array_add(path, (void *)room) == 0 ? RET_OK : ERR_ENOMEM);
}

static void	del_one_path(void *data)
{
	(void)data;
}

void		delete_path(t_path **path)
{
	ft_array_delete_all(path, del_one_path);
}
