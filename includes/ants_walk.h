/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_walk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:42:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/18 17:42:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTS_WALK_H
# define ANTS_WALK_H

# include "lemin.h"

typedef struct	s_push_move {
	t_roomdata	*cur;
	t_roomdata	*prev;
	t_path		*path;
	size_t		index;
	int			num_ants;
}				t_push_move;

#endif
