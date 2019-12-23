/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_given_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:57:03 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/18 09:57:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_given_data(t_lemin *lem)
{
	size_t	index;
	char	*str;

	index = -1;
	while (ft_array_get(&lem->strarr, ++index, (void **)&str) == 0)
	{
		if (str)
			ft_putendl(str);
	}
	ft_putchar('\n');
	print_solution(lem);
}
