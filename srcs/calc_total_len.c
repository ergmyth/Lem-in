/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_total_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:43:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/15 09:43:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					calc_total_len(t_patharr *paths, int count)
{
	int			sum_size;
	t_path		*path;
	int			total_len;
	size_t		index;

	sum_size = 0;
	total_len = FT_INTMAX;
	index = -1;
	while (ft_array_get(paths, ++index, (void **)&path) == 0)
	{
		sum_size += ((int)ft_array_size(path) - 1);
		if (((count + sum_size + (int)index) / ((int)index + 1) - 1)
			>= total_len)
			break ;
		total_len = (count + sum_size + (int)index) / ((int)index + 1) - 1;
	}
	return (total_len);
}
